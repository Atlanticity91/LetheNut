/************************************************************************************
 *
 *	 _          _   _          _   _       _
 *	| |        | | | |        | \ | |     | |
 *	| |     ___| |_| |__   ___|  \| |_   _| |_
 *	| |    / _ \ __| '_ \ / _ \ . ` | | | | __|
 *	| |___|  __/ |_| | | |  __/ |\  | |_| | |_
 *	|______\___|\__|_| |_|\___|_| \_|\__,_|\__|
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2020 ALVES Quentin.
 *
 * This file is part of Lethe Nut project : https://github.com/Atlanticity91/LetheNut.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ************************************************************************************/

#include "__ui.hpp"

#include <LetheNut/NutLibrary.hpp>

#define NCALL( NAME ) return ( this->##NAME ) ? this->##NAME( ) : "";

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE
///////////////////////////////////////////////////////////////////////////////////////////
void NutLibrary::Initialize( ) {
	this->name = this->Get<NutLibImporter>( "GetName" );
	this->description = this->Get<NutLibImporter>( "GetDescription" );
	this->author = this->Get<NutLibImporter>( "GetAuthor" );
	this->version = this->Get<NutLibImporter>( "GetVersion" );
	this->license = this->Get<NutLibImporter>( "GetLicense" );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutLibrary::GetIsValid( ) const {
	if ( this->GetState( ) && this->name )
		return strcmp( "", this->name( ) ) != 0;

	return false;
}

nString NutLibrary::GetName( ) const { NCALL( name ); }

nString NutLibrary::GetDescription( ) const { NCALL( description ); }

nString NutLibrary::GetAuthor( ) const { NCALL( author ); }

nString NutLibrary::GetVersion( ) const { NCALL( version ); }

nString NutLibrary::GetLicense( ) const { NCALL( license ); }
