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

#include "__pch.hpp"

#include <LetheNut/Utils/NutLibrary.hpp>

#define NCALL( NAME ) return ( this->##NAME ) ? this->##NAME( ) : "";

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE
///////////////////////////////////////////////////////////////////////////////////////////
NutLibrary::NutLibrary( nString path ) 
	: handle( path )
{ 
	this->name = this->handle[ "GetName" ];
	this->description = this->handle[ "GetDescription" ];
	this->author = this->handle[ "GetAuthor" ];
	this->version = this->handle[ "GetVersion" ];
	this->license = this->handle[ "GetLicense" ];

	if ( this->name )
		this->hash = nHelper::Hash( this->name( ) );
}

NutLibrary::NutLibrary( const std::string& path )
	: NutLibrary( path.c_str( ) )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutLibrary::GetIsValid( ) const { return this->handle.GetIsValid( ) && this->name; }

nString NutLibrary::GetName( ) const { NCALL( name ); }

nString NutLibrary::GetDescription( ) const { NCALL( description ); }

nString NutLibrary::GetAuthor( ) const { NCALL( author ); }

nString NutLibrary::GetVersion( ) const { NCALL( version ); }

nString NutLibrary::GetLicense( ) const { NCALL( license ); }

NutProcedure NutLibrary::Get( nString name ) const { return this->handle.Get( name ); }

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR 
///////////////////////////////////////////////////////////////////////////////////////////
NutHash NutLibrary::GetHash( ) const { return this->hash; }

NutProcedure NutLibrary::operator[]( nString name ) const { return this->Get( name ); }
