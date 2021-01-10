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

#include <LetheNut/Utils/NutPlatformLib.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN64
NutProcedure::NutProcedure( FARPROC handle )
#else
NutProcedure::NutProcedure( void* handle )
#endif
	: handle( handle ) 
{ }

NutPlatformLib::NutPlatformLib( ) 
	: handle( nullptr )
{ }

NutPlatformLib::NutPlatformLib( nString path ) 
#ifdef _WIN64
	: handle( LoadLibraryA( path ) )
#else
	: handle( dlopen( path, RTLD_LAZY ) )
#endif
{ 
	printf( "[ %p ] %s\n", this->handle, path );
}

NutPlatformLib::NutPlatformLib( const std::string& path )
	: NutPlatformLib( path.c_str( ) )
{ }

NutPlatformLib::~NutPlatformLib( ) {
	printf( "[ %p ] ~\n", this->handle );

	if ( this->handle != nullptr ) {
#ifdef _WIN64
		FreeLibrary( this->handle );
#else
		dlclose( this->handle );
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutPlatformLib::GetIsValid( ) const { return this->handle != nullptr; }

bool NutPlatformLib::Has( nString query_name ) const { 
	if ( this->IsValid( query_name ) )
		return GetProcAddress( this->handle, query_name ) != nullptr;

	return false;
}

NutProcedure NutPlatformLib::Get( nString query_name ) const {
	if ( this->IsValid( query_name ) ) {
#ifdef _WIN64
		auto procedure = GetProcAddress( this->handle, query_name );
#else
		auto procedure = dlsym( this->handle, name );
#endif

		return NutProcedure( procedure );
	}

	return NutProcedure( nullptr );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutPlatformLib::IsValid( nString query_name ) const {
	return this->handle != nullptr && nHelper::GetIsValid( query_name );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////
NutProcedure NutPlatformLib::operator[]( nString query_name ) const { 
	return this->Get( query_name );
}
