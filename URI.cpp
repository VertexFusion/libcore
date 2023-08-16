//
//  URI.cpp
//  jameo
//
//  Created by Uwe Runtemund on 01.04.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;


URI::URI(const jm::String &uri)
{
	mUri = uri;
}

URI::URI(const jm::String &scheme,
         const jm::String &userInformation,
         const jm::String &host,
         const int port,
         const jm::String &path,
         const jm::String &query,
         const jm::String &fragment)
{

}