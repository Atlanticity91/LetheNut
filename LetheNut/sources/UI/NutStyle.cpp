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

#include <LetheNut/UI/NutStyle.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutStyle::NutStyle( nString name )
	: NutElement( name ),
	has_changed( true ),
	colors( ),
	rules( ) 
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutStyle::SetColor( ImGuiCol_ query, const ImVec4& value ) {
	auto color = this->GetColor( query );

	if ( color.has_value( ) )
		color->get( ).value = value;
	else
		this->colors.emplace_back( NutStyleColor{ query, value } );

	this->has_changed = true;
}

void NutStyle::SetColor( ImGuiCol_ query, const ImVec4&& value ) {
	this->SetColor( query, value );
}

void NutStyle::SetColor( ImGuiCol_ query, const float red, const float green, const float blue, const float alpha ) {
	this->SetColor( query, ImVec4{ red, green, blue, alpha } );
}

void NutStyle::SetRule( ImGuiStyleVar_ query, float x, float y ) {
	auto rule = this->GetRule( query );

	if ( rule.has_value( ) )
		rule->get( ).value = ImVec2{ x, y };
	else
		this->rules.emplace_back( NutStyleRule{ query, ImVec2{ x, y } } );

	this->has_changed = true;
}

void NutStyle::AddFont( nString path, float size ) {
	if ( nHelper::GetIsValid( path ) ) {
		size = fabs( size );

		if ( size > 0.f ) {
			this->fonts.emplace_back( NutStyleFont{ path, size } );

			this->has_changed = true;
		}
	}
}

void NutStyle::AddFont( const std::string& path, float size ) {
	this->AddFont( path.c_str( ), size );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET 
///////////////////////////////////////////////////////////////////////////////////////////
bool NutStyle::GetHasChanged( ) const { return this->has_changed; }

std::vector<NutStyleColor>& NutStyle::GetColors( ) const { return this->colors; }

std::vector<NutStyleRule>& NutStyle::GetRules( ) const { return this->rules; }

std::vector<NutStyleFont>& NutStyle::GetFonts( ) const { return this->fonts; }

NutStyle::ColorRef NutStyle::GetColor( ImGuiCol_ query ) const {
	for ( auto& color : this->colors ) {
		if ( color.target != query )
			continue;
		else
			return NutStyle::ColorRef{ color };
	}

	return std::nullopt;
}

NutStyle::RuleRef NutStyle::GetRule( ImGuiStyleVar_ query ) const {
	for ( auto& rule : this->rules ) {
		if ( rule.target != query )
			continue;
		else
			return NutStyle::RuleRef{ rule };
	}

	return std::nullopt;
}
