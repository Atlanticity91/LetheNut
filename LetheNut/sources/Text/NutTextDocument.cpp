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

#include <LetheNut/Editors/Text/NutTextDocument.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument::NutTextDocument( nString name )
	: NutTextDocument( std::string( name ) )
{ }

NutTextDocument::NutTextDocument( const std::string& name ) 
	: name( name ),
	cursor{ 0, 0 },
	lines( )
{ 
	this->lines.emplace_back( std::string( ) );
}

NutTextDocument::~NutTextDocument( ) { }

void NutTextDocument::SetCursor( const NutTextCursor& cursor ) { this->cursor = cursor; }

void NutTextDocument::Append( char character, nUInt line ) {
	auto str = std::string( );
	str += character;

	this->Append( str, line );
}

void NutTextDocument::Append( const std::string& string, nUInt line ) {
	if ( line < this->lines.size( ) ) {
		if ( !string.empty( ) )
			this->lines[ line ] += string;
		else
			this->lines.insert( this->lines.begin( ) + line, "" );
	} else 
		this->CreateLine( string, line );
}

void NutTextDocument::Insert( char character, NutTextCursor& cursor ) {
	if ( character != '\n' ) {
		this->Insert( character, cursor.line, cursor.position );

		if ( character != '\t' )
			cursor.position += 1;
		else
			cursor.position += 4;
	} else if ( cursor.line < this->lines.size( ) ) {
		std::string content;

		this->lines.insert( this->lines.begin( ) + cursor.line, content );
		this->lines[ cursor.line ].erase( cursor.position, this->lines[ cursor.line ].size( ) - cursor.position );

		cursor.line += 1;
	} 
}

void NutTextDocument::Insert( const std::string& string, NutTextCursor& cursor ) {
	this->Insert( string, cursor.line, cursor.position );
}

void NutTextDocument::Insert( char character, nUInt line, nUInt position ) {
	auto str = std::string( );
	str += character;

	this->Insert( str, line, position );
}

void NutTextDocument::Insert( const std::string& string, nUInt line, nUInt position ) {
	if ( line < this->lines.size( ) ) {
		if ( !string.empty( ) && position < this->lines.size( ) ) {
			auto insert_pos = this->lines[ line ].begin( ) + position;

			for ( auto idx = 0; idx < string.size( ); idx++ )
				this->lines[ line ].insert( insert_pos + idx, string[ idx ] );
		} else
			this->lines.insert( this->lines.begin( ) + line, "" );
	} else
		this->CreateLine( string, line );
}

void NutTextDocument::Delete( nUInt line, nUInt position ) {
	this->Delete( line, position, 1 );
}

void NutTextDocument::Delete( nUInt line, nUInt position, nUInt length ) {
	if ( line < this->lines.size( ) && position < this->lines[ line ].size( ) ) {
		auto size = this->lines[ line ].size( ) - position;
		auto idx = ( length < size ) ? length : size;

		while ( idx > 0 ) {
			idx -= 1;

			this->lines[ line ].erase( this->lines[ line ].begin( ) + position );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument& NutTextDocument::CreateLine( const std::string& string, nUInt line ) {
	auto query = line - this->lines.size( );

	while ( query > 0 ) {
		query -= 1;

		this->lines.emplace_back( "" );
	}

	this->lines.emplace_back( string );

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const std::string& NutTextDocument::GetName( ) const { return this->name; }

const nUInt NutTextDocument::GetSize( ) const { return (nUInt)this->lines.size( ); }

const NutTextCursor& NutTextDocument::GetCursor( ) const { return this->cursor; }

NutTextDocument::Line& NutTextDocument::GetLine( nUInt query_id ) const {
	if ( query_id < this->lines.size( ) )
		return this->lines[ query_id ];

	return this->lines[ this->lines.size( ) - 1 ];
}

const NutTextDocument::Lines& NutTextDocument::GetLines( ) const { return this->lines; }

const nUInt NutTextDocument::GetLineSize( nUInt query_id ) const {
	return (nUInt)this->GetLine( query_id ).size( );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATORS
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument::operator nString( ) const { return this->name.c_str( ); }

NutTextDocument::operator const NutTextCursor& ( ) const { return this->cursor; }

NutTextDocument::operator const nUInt( ) const { return this->GetSize( ); }

NutTextDocument::operator const NutTextDocument::Lines&( ) const {  return this->lines; }

NutTextDocument::Line& NutTextDocument::operator[]( nUInt query_id ) const {
	return this->GetLine( query_id );
}

NutTextDocument& NutTextDocument::operator+=( nString string ) {
	return this->CreateLine( string, (nUInt)this->lines.size( ) );
}

NutTextDocument& NutTextDocument::operator+=( const std::string& string ) {
	return this->CreateLine( string, (nUInt)this->lines.size( ) );
}
