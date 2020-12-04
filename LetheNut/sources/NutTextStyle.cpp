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

#include <LetheNut/Editors/Text/NutTextStyle.hpp>

#define FIND( QUERY ) this->variables.find( QUERY ) != this->variables.end( )
#define NFIND( QUERY ) !( FIND( QUERY ) )
#define BACKGROUND ImColor{ 30, 30, 30, 255 }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutTextStyle::NutTextStyle( nString name )
	: NutBasic( name ),
	line_space( 1.f ),
	variables( )
{ this->Validate( ); }

NutTextStyle::~NutTextStyle( ) { }

void NutTextStyle::Set( ENutTextStyleVars query_var, const ImColor& background, const ImColor& foreground ) {
	if ( NFIND( query_var ) ) {
		auto style_var = NutTextStyleVar{ foreground, background };
		auto var = std::make_pair( query_var, style_var );

		this->variables.emplace( var );
	}
}

void NutTextStyle::Set( ENutTextStyleVars query_var, const ImColor&& background, const ImColor&& foreground ) {
	this->Set( query_var, background, foreground );
}

void NutTextStyle::Set( ENutTextStyleVars query_var, const ColorBuilder& builder ) {
	if ( builder.size( ) == 8 ) {
		auto color_bg = ImColor{ builder[ 0 ], builder[ 1 ], builder[ 2 ], builder[ 3 ] };
		auto color_fg = ImColor{ builder[ 4 ], builder[ 5 ], builder[ 6 ], builder[ 7 ] };

		this->Set( query_var, color_bg, color_fg );
	}
}

void NutTextStyle::Set( const std::string& query_var, const ColorBuilder& builder ) {
	auto var = this->Convert( query_var );

	this->Set( var, builder );
}

void NutTextStyle::SetLineSpacing( float spacing ) { this->line_space = fabs( spacing ); }

ENutTextStyleVars NutTextStyle::Convert( const std::string& query_var ) {
	auto var_name = query_var;
	std::transform(
		var_name.begin( ), var_name.end( ), var_name.begin( ),
		[ ]( unsigned char c ) { return std::tolower( c ); }
	);

	if ( var_name == "linecount" || var_name == "line count" )
		return ENutTextStyleVars::ETSV_LINECOUNT;
	if ( var_name == "line" )
		return ENutTextStyleVars::ETSV_LINE;
	else if ( var_name == "selection" )
		return ENutTextStyleVars::ETSV_SELECTION;
	else if ( var_name == "error" )
		return ENutTextStyleVars::ETSV_ERROR;
	else if ( var_name == "comment" )
		return ENutTextStyleVars::ETSV_COMMENT;
	else if ( var_name == "preprocessor" || var_name == "pre processor" || var_name == "pre-processor" )
		return ENutTextStyleVars::ETSV_PREPROCESSOR;
	else if ( var_name == "ponctuation" )
		return ENutTextStyleVars::ETSV_PONCTUATION;
	else if ( var_name == "litteral" )
		return ENutTextStyleVars::ETSV_LITTERAL;
	else if ( var_name == "keyword" )
		return ENutTextStyleVars::ETSV_KEYWORD;
	else if ( var_name == "control" )
		return ENutTextStyleVars::ETSV_CONTROL;
	else if ( var_name == "type" )
		return ENutTextStyleVars::ETSV_TYPE;
	else if ( var_name == "member" )
		return ENutTextStyleVars::ETSV_MEMBER;

	return ENutTextStyleVars::ETSV_DEFAULT;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextStyle::Validate( ) {
	this->Set( ENutTextStyleVars::ETSV_DEFAULT, BACKGROUND, ImColor{ 200, 200, 200, 255 } );
	this->Set( ENutTextStyleVars::ETSV_LINECOUNT, BACKGROUND, ImColor{ 38, 143, 175, 255 } );
	this->Set( ENutTextStyleVars::ETSV_LINE, BACKGROUND, ImColor{ 70,  70,  70, 255 } );
	this->Set( ENutTextStyleVars::ETSV_SELECTION, ImColor{ 38,  79, 120, 255 }, ImColor{ 52,  52,  52, 255 } );
	this->Set( ENutTextStyleVars::ETSV_ERROR, ImColor{ 245,  61,  53, 255 }, ImColor{ 245, 229,  53, 255 } );
	this->Set( ENutTextStyleVars::ETSV_COMMENT, BACKGROUND, ImColor{ 87, 166,  74, 255 } );
	this->Set( ENutTextStyleVars::ETSV_PREPROCESSOR, BACKGROUND, ImColor{ 155, 155, 155, 255 } );
	this->Set( ENutTextStyleVars::ETSV_PONCTUATION, BACKGROUND, ImColor{ 255, 255,   0, 255 } );
	this->Set( ENutTextStyleVars::ETSV_KEYWORD, BACKGROUND, ImColor{ 86, 156, 210, 255 } );
	this->Set( ENutTextStyleVars::ETSV_CONTROL, BACKGROUND, ImColor{ 216, 160, 223, 255 } );
	this->Set( ENutTextStyleVars::ETSV_TYPE, BACKGROUND, ImColor{ 78, 201, 176, 255 } );
	this->Set( ENutTextStyleVars::ETSV_MEMBER, ImColor{ 154, 154, 154, 255 }, ImColor{ 155, 219, 252, 255 } );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const ImColor& NutTextStyle::GetBackground( ) const {
	return this->variables.at( ENutTextStyleVars::ETSV_DEFAULT ).background;
}

const ImColor& NutTextStyle::GetDefault( ) const {
	return this->variables.at( ENutTextStyleVars::ETSV_DEFAULT ).foreground;
}

const float NutTextStyle::GetLineSpacing( ) const { return this->line_space; }

const NutTextStyleVar& NutTextStyle::Get( ENutTextStyleVars query_var ) const {
	if ( FIND( query_var ) )
		return this->variables.at( query_var );

	return this->variables.at( ENutTextStyleVars::ETSV_DEFAULT );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////
const NutTextStyleVar& NutTextStyle::operator[ ]( ENutTextStyleVars query_var ) const {
	return this->Get( query_var );
}
