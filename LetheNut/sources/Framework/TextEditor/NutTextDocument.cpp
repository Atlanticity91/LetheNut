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

#include <LetheNut/Framework/Editors/Text/NutTextDocument.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument::NutTextDocument( const std::string& name, const std::string& path )
	: is_open( true ),
	is_saved( false ),
	name( name ),
	path( path ),
	cursor( ),
	lines( ) 
{  
	this->hash = nHelper::Hash( this->name.c_str( ) );
}

void NutTextDocument::SetPath( const std::string& path ) { this->path = path; }

void NutTextDocument::SetCursor( const NutTextCursor& cursor ) { this->cursor = cursor; }

void NutTextDocument::Append( char character ) {
	if ( character != '\n' ) {
		auto tmp = std::string( 1, character );

		this->Append( tmp );
	} else
		this->NewLine( );
}

void NutTextDocument::Append( const std::string& text ) {
	this->lines.emplace_back( text );
}

void NutTextDocument::AppendTo( char character, nUInt line ) {
	auto tmp = std::string( 1, character );

	this->AppendTo( tmp, line );
}

void NutTextDocument::AppendTo( const std::string& text, nUInt line ) {
	if ( line < this->GetLineCount( ) )
		this->lines[ line ] += text;
	else
		this->Append( text );
}

void NutTextDocument::Insert( char character, nUInt line, nUInt position ) {
	auto tmp = std::string( 1, character );

	this->Insert( tmp, line, position );
}

void NutTextDocument::Insert( const std::string& text, nUInt line, nUInt position ) {
	// TODO : IF FOUND \n BREAK INTO MULTIPLE STRING

	if ( !text.empty( ) && line < this->GetLineCount( ) ) {
		if ( text != "\n" && position < this->lines[ line ].size( ) )
			this->lines[ line ].insert( position, text );
		else if ( text == "\n" ) {
			auto size = this->lines[ line ].size( ) - position;
			auto text = this->lines[ line ].substr( position, size );

			this->lines.insert( this->lines.begin( ) + line + 1, text );
			this->lines[ line ].erase( position, size );
		} else
			this->AppendTo( text, line );
	}
}

void NutTextDocument::Merge( nUInt start_line, nUInt stop_line ) {
	if ( start_line < stop_line && stop_line < this->GetLineCount( ) ) {
		this->lines[ start_line ] += this->lines[ stop_line ];
		this->DeleteLine( stop_line );
	}
}

void NutTextDocument::NewLine( ) { this->lines.emplace_back( "" ); }

void NutTextDocument::Delete( nUInt line, nUInt position ) {
	if ( line < this->GetLineCount( ) && position < this->lines[ line ].size( ) )
		this->lines[ line ].erase( position, 1 );
}

void NutTextDocument::Erase( nUInt line, nUInt position, nUInt size ) {
	auto line_size = this->GetLineSize( line );
	auto target_size = line_size - position;

	if ( position < line_size ) {
		if ( size > target_size )
			size = target_size;

		if ( size != line_size )
			this->lines[ line ].erase( position, size );
		else
			this->DeleteLine( line );
	}
}

void NutTextDocument::Erase( nUInt from_line, nUInt from_position, nUInt to_line, nUInt to_position ) {
	auto size = this->GetLineCount( ) - 1;

	nHelper::Clamp<nUInt>( from_line, 0, size );
	nHelper::Clamp<nUInt>( to_line, 0, size );

	if ( from_line != to_line ) {
		auto from_size = (nUInt)this->lines[ from_line ].size( );
		auto to_size = (nUInt)this->lines[ to_line ].size( );

		nHelper::Clamp<nUInt>( from_position, 0, from_size );
		nHelper::Clamp<nUInt>( to_position, 0, to_size );

		this->lines[ to_line ] = this->lines[ to_line ].substr( to_position );
		this->Erase( from_line, from_position, from_size - from_position );
		this->Merge( from_line, to_line );

		for ( nUInt idx = 0; idx < ( to_line - 1 ) - from_line; idx++ )
			this->DeleteLine( from_line + 1 );
	}
}

void NutTextDocument::DeleteLine( nUInt line_id ) {
	if ( line_id < this->GetLineCount( ) )
		this->lines.erase( this->lines.begin( ) + line_id );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutHash NutTextDocument::GetHash( ) const { return this->hash; }

const bool NutTextDocument::GetIsOpen( ) const { return this->is_open; }

bool* NutTextDocument::GetState( ) const { return &this->is_open; }

const bool NutTextDocument::GetIsSaved( ) const { return this->is_saved; }

const std::string& NutTextDocument::GetName( ) const { return this->name; }

const std::string& NutTextDocument::GetPath( ) const { return this->path; }

const NutTextCursor& NutTextDocument::GetCursor( ) const { return this->cursor; }

const nUInt NutTextDocument::GetLineCount( ) const { return (nUInt)this->lines.size( ); }

const NutTextDocument::Lines& NutTextDocument::GetLines( ) const { return this->lines; }

const nUInt NutTextDocument::GetLineSize( nUInt line_id ) const {
	if ( line_id < this->GetLineCount( ) )
		return (nUInt)this->lines[ line_id ].size( );

	return 0;
}

const std::string& NutTextDocument::GetLine( nUInt line_id ) const {
	if ( line_id < this->GetLineCount( ) )
		return this->lines[ line_id ];

	return "";
}

const char NutTextDocument::At( nUInt line, nUInt position ) {
	if ( line < this->lines.size( ) && position < this->lines[ line ].size( ) )
		return this->lines[ line ][ position ];

	return '\0';
}

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATORS
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument& NutTextDocument::operator=( const NutTextCursor& cursor ) {
	this->cursor = cursor;

	return *this;
}

NutTextDocument& NutTextDocument::operator+=( const std::string& text ) {
	this->Append( text );

	return *this;
}

NutTextDocument& NutTextDocument::operator+=( const std::string&& text ) {
	this->Append( text );

	return *this;
}
