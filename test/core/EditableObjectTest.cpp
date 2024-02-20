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

      VxfErrorStatus InitNewDocument(Preferences* props) override
      {
         return eOK;// Needs to be overriden
      }

      bool SaveDocument() override
      {
         return true;// Needs to be overriden
      };

      bool LoadDocument() override
      {
         return true;// Needs to be overriden
      };

      void AddAddress(Address* adr);

      Integer GetAddressCount() const;

   private:

      LinkedList mEntries;
};

enum Country
{
   kUnknown = 0,
   kGermany = 1,
   kSwitzerland = 2,
   kUnitedKindom = 3
};

class Address : public EditableObject
{
   public:

      Address(AddressBook* book) : EditableObject(book)
      {
         mHouseNumber = 0;
         mCountry = kUnknown;
         mPartner = NULL;
      };

      VxfErrorStatus SetName(const String& name)
      {
         return SetMember(&mName, name);
      };

      const String& GetName() const
      {
         return mName;
      };

      VxfErrorStatus SetStreetAddress(const String& street, Integer housenumber)
      {
         OpenTransaction();
         SetMember(&mStreetName, street);
         SetMember(&mHouseNumber, housenumber, 0);
         return CloseTransaction();
      }

      const String& GetStreet()const
      {
         return mStreetName;
      }

      Integer GetHouseNumber()const
      {
         return mHouseNumber;
      }

   private:

      String mName;
      String mStreetName;
      Integer mHouseNumber;
      String mLocation;
      Country mCountry;
      Date mBirthdate;
      Address* mPartner;
};

void AddressBook::AddAddress(Address* adr)
{
   mEntries.Add(adr, GetUndoManager());
}

Integer AddressBook::GetAddressCount() const
{
   return mEntries.Size();
}


EditableObjectTest::EditableObjectTest() : Test()
{
   SetName("Test Document & Editable Object");
}

void EditableObjectTest::DoTest()
{

   AddressBook* book = new AddressBook();
   book->InitNewDocument(NULL); // From API side, this shall be called first, though we have not implementation hier. Just as reminder

   UndoManager* um = book->GetUndoManager();//Get reference for later

   // Add first address
   Address* adr = new Address(book);

   // Check simple member changing
   // Set "wrong" name, test undo and correct.
   adr->SetName("UweRuntemund");
   um->Close();
   TestEquals(adr->GetName(), "UweRuntemund", "Name wrong (1)");

   um->Undo();

   adr->SetName("Uwe Runtemund");
   um->Close();
   TestEquals(adr->GetName(), "Uwe Runtemund", "Name wrong (2)");

   TestEquals(book->GetAddressCount(), 0, "Size of AdressBook wrong (3)");
   book->AddAddress(adr);
   um->Close();
   TestEquals(book->GetAddressCount(), 1, "Size of AdressBook wrong (4)");
   um->Undo();
   TestEquals(book->GetAddressCount(), 0, "Size of AdressBook wrong (5)");
   um->Redo();
   TestEquals(book->GetAddressCount(), 1, "Size of AdressBook wrong (6)");

   // Check simple Transaction
   TestEquals(adr->GetStreet(), kEmptyString, "Street name wrong (7)");
   TestEquals(adr->GetHouseNumber(), 0, "House number wrong (8)");
   adr->SetStreetAddress("Waldstraße", 51);
   um->Close();
   TestEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (9)");
   TestEquals(adr->GetHouseNumber(), 51, "House number wrong (10)");
   um->Undo();
   TestEquals(adr->GetStreet(), kEmptyString, "Street name wrong (11)");
   TestEquals(adr->GetHouseNumber(), 0, "House number wrong (12)");
   um->Redo();
   TestEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (13)");
   TestEquals(adr->GetHouseNumber(), 51, "House number wrong (14)");

   // Check transaction with expected data failure. As result, we expect no data changes.
   VxfErrorStatus status = adr->SetStreetAddress("Teststraße", -19);
   TestEquals(status, eInvalidInput, "VxfErrorStatus wrong (15)");
   TestEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (16)");
   TestEquals(adr->GetHouseNumber(), 51, "House number wrong (17)");
   TestFalse(um->HasOpenTransaction(), "Transaction is open (18)");
   TestFalse(um->HasOpenUndoStep(), "Undo Step is open (19)");

   // Undo shall happen with previous data, as nothing should happened
   um->Undo();
   TestEquals(adr->GetStreet(), kEmptyString, "Street name wrong (20)");
   TestEquals(adr->GetHouseNumber(), 0, "House number wrong (21)");
   um->Redo();
   TestEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (22)");
   TestEquals(adr->GetHouseNumber(), 51, "House number wrong (23)");

   // Changing just the house number should not have any effect, though calling SetMember with
   // the street will return eNotChanged, which should not have any effect on the transaction
   status = adr->SetStreetAddress("Waldstraße", 7);
   TestEquals(status, eOK, "VxfErrorStatus wrong (24)");
   TestEquals(adr->GetStreet(), "Waldstraße", "Street name wrong (25)");
   TestEquals(adr->GetHouseNumber(), 7, "House number wrong (26)");
   TestFalse(um->HasOpenTransaction(), "Transaction is open (27)");
   TestTrue(um->HasOpenUndoStep(), "Undo Step is closed (28)");
   um->Close();
   TestFalse(um->HasOpenUndoStep(), "Undo Step is open (28)");

   delete book;
}
