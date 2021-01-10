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
 * Copyright (C) 2021 ALVES Quentin.
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

#include <LetheNut/Assets/NutAssetManager.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutAssetManager::NutAssetManager( )
	: images( ),
	sounds( ),
	jsons( ),
	binaries( )
{ }

NutAssetManager::~NutAssetManager( ) {
	this->images.Foreach( [ ]( auto& element ) { element.Cleanup( ); } );
	this->sounds.Foreach( [ ]( auto& element ) { element.Cleanup( ); } );
	this->binaries.Foreach( [ ]( auto& element ) { element.Cleanup( ); } );
}

bool NutAssetManager::LoadImageAs( NutEditor* editor, nString alias, nString path ) {
	if ( nHelper::GetIsValid( alias ) && path ) {
		auto* image = this->images.Append( alias );

		if ( image )
			return NUT_CAST( image, NutAsset )->Load( editor, path );
	}

	return false;
}

bool NutAssetManager::LoadImageAs( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->LoadImageAs( editor, alias.c_str( ), path.c_str( ) );
}

bool NutAssetManager::LoadSoundAs( NutEditor* editor, nString alias, nString path ) {
	if ( nHelper::GetIsValid( alias ) && path ) {
		auto* sound = this->sounds.Append( alias );

		if ( sound )
			return NUT_CAST( sound, NutAsset )->Load( editor, path );
	}

	return false;
}

bool NutAssetManager::LoadSoundAs( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->LoadSoundAs( editor, alias.c_str( ), path.c_str( ) );
}

bool NutAssetManager::LoadJSONAs( NutEditor* editor, nString alias, nString path ) {
	if ( nHelper::GetIsValid( alias ) && path ) {
		auto* json = this->jsons.Append( alias );

		if ( json )
			return NUT_CAST( json, NutAsset )->Load( editor, path );
	}

	return false;
}

bool NutAssetManager::LoadJSONAs( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->LoadJSONAs( editor, alias.c_str( ), path.c_str( ) );
}

bool NutAssetManager::LoadBinaryAs( NutEditor* editor, nString alias, nString path ) {
	if ( nHelper::GetIsValid( alias ) && path ) {
		auto* binary = this->binaries.Append( alias );

		if ( binary )
			return NUT_CAST( binary, NutAsset )->Load( editor, path );
	}

	return false;
}

bool NutAssetManager::LoadBinaryAs( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->LoadBinaryAs( editor, alias.c_str( ), path.c_str( ) );
}

bool NutAssetManager::WriteJSON( NutEditor* editor, nString alias, nString path ) {
	auto* json = this->jsons[ alias ];

	if ( json )
		return NUT_CAST( json, NutAsset )->Write( editor, path );

	return false;
}

bool NutAssetManager::WriteJSON( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->WriteJSON( editor, alias.c_str( ), path.c_str( ) );
}

bool NutAssetManager::WriteBinary( NutEditor* editor, nString alias, nString path ) {
	auto* binary = this->binaries[ alias ];

	if ( binary )
		return NUT_CAST( binary, NutAsset )->Write( editor, path );

	return false;
}

bool NutAssetManager::WriteBinary( NutEditor* editor, const std::string& alias, const std::string& path ) {
	return this->WriteBinary( editor, alias.c_str( ), path.c_str( ) );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutImage* NutAssetManager::GetImage( nString alias ) const { return this->images[ alias ]; }

NutSound* NutAssetManager::GetSound( nString alias ) const { return this->sounds[ alias ]; }

NutJSON* NutAssetManager::GetJSON( nString alias ) const { return this->jsons[ alias ]; }

NutBinary* NutAssetManager::GetBinary( nString alias ) const {
	return this->binaries[ alias ];
}
