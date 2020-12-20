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

#include <LetheNut/Editors/Text/NutTextParser.hpp>
#include <LetheNut/Vendor/JSON.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutTextParser::NutTextParser( nString name )
	: NutBasic( name ),
	last_char( 0 ),
	tables( )
{ this->Validate( ); }

NutTextParser::~NutTextParser( ) { }

void NutTextParser::Parse( const std::string& input ) {
	this->last_char = 0;
	this->result[ 0 ] = '\0';
	this->result[ 1 ] = '\0';

	if ( !input.empty( ) ) {
		for ( auto size = 0; size < input.size( ); size++ ) {
			if ( input[ size ] != ' ' )
				this->result[ size ] = input[ size ];
			else
				this->result[ size ] = '\0';
		}

		this->result[ input.size( ) ] = '\0';
		this->result[ input.size( ) + 1 ] = '\0';
	}

	auto d = std::vector<int>{ 10, 10, 1, 0 };
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextParser::Validate( ) {
	this->Register( ENutTextStyleVars::ETSV_PONCTUATION, ",", ";", ".", ":", "!", "?", ":" );
	this->Register( ENutTextStyleVars::ETSV_CONTROL, "if", "else", "for", "while", "do", "break", "continue", "return" );
	this->Register( ENutTextStyleVars::ETSV_KEYWORD, "func", "end", "var", "const", "import", "export" );
	this->Register(
		ENutTextStyleVars::ETSV_TYPE,
		"string",
		"bool", "byte", "short", "int", "long", "ubyte", "uint", "uint", "ulong", 
		"float", "double", "mat2", "mat3", "mat4"
	);
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutTextParser::GetNext( ENutTextStyleVars& style, nString& text ) {
	if ( this->result[ 0 ] != '\0' ) {
		if ( ( this->last_char == 0 || this->result[ this->last_char++ ] == '\0' ) && this->result[ this->last_char ] != '\0' ) {
			text = &this->result[ this->last_char ];

			while ( this->result[ this->last_char ] != '\0' )
				this->last_char += 1;
			
			style = this->FindSyntax( text );

			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE GET
///////////////////////////////////////////////////////////////////////////////////////////
ENutTextStyleVars NutTextParser::FindSyntax( nString text ) {
	for ( auto pair : this->tables ) {
		for ( auto string : pair.second ) {
			if ( !strstr( text, string.c_str( ) ) )
				continue;

			return pair.first;
		}
	}

	return ENutTextStyleVars::ETSV_DEFAULT;
}
