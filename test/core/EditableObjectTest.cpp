////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        EditableObjectTest.cpp
// Library:     Jameo Core Library
// Purpose:     Unit Test
//
// Author:      Uwe Runtemund (2023-today)
// Modified by:
// Created:     01.11.2023
//
// Copyright:   (c) 2023 Jameo Software, Germany. https://jameo.de
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "core/Core.h"
#include "EditableObjectTest.h"

using namespace jm;

//! For testing we create a simple addressbook data model.
class Address;

class AddressBook : public Document
{
   public:

      AddressBook() : Document(),
         mEntries(this)
      {

      };

      Status initNewDocument(Preferences* /*props*/) override
      {
         return Status::eOK;// Needs to be overriden
      }

      bool saveDocument() override
      {
         return true;// Needs to be overriden
      };

      bool loadDocument() override
      {
         return true;// Needs to be overriden
      };

      void AddAddress(Address* adr);

      size_t GetAddressCount() const;

   private:

      LinkedList mEntries;
};

enum class Country
{
   kUnknown = 0,
   kGermany = 1,
   kSwitzerland = 2,
   kUnitedKindom = 3
};

class Address : public EditableObject
{
   public:

      explicit Address(AddressBook* book) : EditableObject(book)
      {
         mHouseNumber = 0;
         mCountry = Country::kUnknown;
         mPartner = nullptr;
      };

      Status SetName(const String& name)
      {
         return setMember(&mName, name);
      };

      const String& GetName() const
      {
         return mName;
      };

      Status SetStreetAddress(const String& street, int64 housenumber)
      {
         openTransaction();
         setMember(&mStreetName, street);
         setMember(&mHouseNumber, housenumber, 0);
         return closeTransaction();
      }

      const String& GetStreet()const
      {
         return mStreetName;
      }

      int64 GetHouseNumber()const
      {
         return mHouseNumber;
      }

   private:

      String mName;
      String mStreetName;
      int64 mHouseNumber;
      String mLocation;
      Country mCountry;
      Date mBirthdate;
      Address* mPartner;
};

void AddressBook::AddAddress(Address* adr)
{
   mEntries.add(adr, undoManager());
}

size_t AddressBook::GetAddressCount() const
{
   return mEntries.size();
}


EditableObjectTest::EditableObjectTest() : Test()
{
   setName("Test Document & Editable Object");
}

void EditableObjectTest::doTest()
{

   AddressBook* book = new AddressBook();
   // From API side, this shall be called first, though we have not implementation hier. Just as reminder
   book->initNewDocument(nullptr);

   UndoManager* um = book->undoManager();//Get reference for later

   // Add first address
   Address* adr = new Address(book);

   // Check simple member changing
   // Set "wrong" name, test undo and correct.
   adr->SetName("UweRuntemund");
   um->close();
   testEquals(adr->GetName(), "UweRuntemund", "Name wrong (1)");

   um->undo();

   adr->SetName("Uwe Runtemund");
   um->close();
   testEquals(adr->GetName(), "Uwe Runtemund", "Name wrong (2)");

   testTrue(book->GetAddressCount() == 0, "Size of AdressBook wrong (3)");
   book->AddAddress(adr);
   um->close();
   testTrue(book->GetAddressCount() == 1, "Size of AdressBook wrong (4)");
   um->undo();
   testTrue(book->GetAddressCount() == 0, "Size of AdressBook wrong (5)");
   um->redo();
   testTrue(book->GetAddressCount() == 1, "Size of AdressBook wrong (6)");

   // Check simple Transaction
   testEquals(adr->GetStreet(), kEmptyString, "Street name wrong (7)");
   testEquals(adr->GetHouseNumber(), 0, "House number wrong (8)");
   adr->SetStreetAddress("Waldstraße", 51);
   um->close();
   testEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (9)");
   testEquals(adr->GetHouseNumber(), 51, "House number wrong (10)");
   um->undo();
   testEquals(adr->GetStreet(), kEmptyString, "Street name wrong (11)");
   testEquals(adr->GetHouseNumber(), 0, "House number wrong (12)");
   um->redo();
   testEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (13)");
   testEquals(adr->GetHouseNumber(), 51, "House number wrong (14)");

   // Check transaction with expected data failure. As result, we expect no data changes.
   Status status = adr->SetStreetAddress("Teststraße", -19);
   testTrue(status == Status::eInvalidInput, "VxfErrorStatus wrong (15)");
   testEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (16)");
   testEquals(adr->GetHouseNumber(), 51, "House number wrong (17)");
   testFalse(um->hasOpenTransaction(), "Transaction is open (18)");
   testFalse(um->hasOpenUndoStep(), "Undo Step is open (19)");

   // Undo shall happen with previous data, as nothing should happened
   um->undo();
   testEquals(adr->GetStreet(), kEmptyString, "Street name wrong (20)");
   testEquals(adr->GetHouseNumber(), 0, "House number wrong (21)");
   um->redo();
   testEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (22)");
   testEquals(adr->GetHouseNumber(), 51, "House number wrong (23)");

   // Changing just the house number should not have any effect, though calling setMember with
   // the street will return Status::eOK, which should not have any effect on the transaction
   status = adr->SetStreetAddress("Waldstraße", 7);
   testTrue(status == Status::eOK, "VxfErrorStatus wrong (24)");
   testEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (25)");
   testEquals(adr->GetHouseNumber(), 7, "House number wrong (26)");
   testFalse(um->hasOpenTransaction(), "Transaction is open (27)");
   testTrue(um->hasOpenUndoStep(), "Undo Step is closed (28)");
   um->close();
   testFalse(um->hasOpenUndoStep(), "Undo Step is open (28)");

   // Regeneration status
   testTrue(adr->shouldRegenerate(), "Regeneration status wrong (29)");
   adr->regenerationDone();
   testFalse(adr->shouldRegenerate(), "Regeneration status wrong (30)");
   adr->regenerate();
   testTrue(adr->shouldRegenerate(), "Regeneration status wrong (31)");


   delete book;
   delete adr;
}
