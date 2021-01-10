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

#include <LetheNut/Framework/Editors/Text/NutTextStyle.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutTextStyle::NutTextStyle( nString name, const ImVec4& foreground, const ImVec4& background )
	: NutElement( name ),
	default_var{ foreground, background },
	vars( )
{
	this->OnCreate( );
}

NutTextStyle::NutTextStyle( nString name, const ImColor& foreground, const ImColor& background )
	: NutElement( name ),
	default_var{ foreground, background },
	vars( )
{
	this->OnCreate( );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED 
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextStyle::OnCreate( ) { }

void NutTextStyle::SetText( const ImVec4& color ) {
	this->default_var.foreground = color; 
}

void NutTextStyle::SetText( const ImColor& color ) { 
	this->default_var.foreground = color; 
}

void NutTextStyle::SetBackground( const ImVec4& color ) { 
	this->default_var.background = color; 
}

void NutTextStyle::SetBackground( const ImColor& color ) { 
	this->default_var.background = color; 
}

void NutTextStyle::Set( nUInt query, const NutTextColor& color ) {
	if ( this->vars.find( query ) != this->vars.end( ) )
		this->vars[ query ] = color;
	else {
		auto pair = std::make_pair( query, color );

		this->vars.emplace( pair );
	}
}

void NutTextStyle::Set( nUInt query, const ImVec4& foreground, const ImVec4& background ) {
	this->Set( query, NutTextColor{ foreground, background } );
}

void NutTextStyle::Set( nUInt query, const ImColor& foreground, const ImColor& background ) {
	this->Set( query, NutTextColor{ foreground, background } );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
ImVec4& NutTextStyle::GetText( ) const { return this->default_var.foreground.Value; }

ImVec4& NutTextStyle::GetBackground( ) const { return this->default_var.background.Value; }

NutTextColor& NutTextStyle::Get( ) const { return this->default_var; }

NutTextColor& NutTextStyle::GetVar( nUInt query ) const {
	if ( this->vars.find( query ) != this->vars.end( ) )
		return this->vars[ query ];

	return this->default_var;
}
