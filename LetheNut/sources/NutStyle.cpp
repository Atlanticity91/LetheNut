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

#include <LetheNut/UI/NutStyle.hpp>

const ImVec4 ORANGE = ImVec4{ .76f, .31f, .0f, 1.f };
const ImVec4 DARK_ORANGE = ImVec4{ .76f, .31f, .0f, .65f };
const ImVec4 GRAY = ImVec4{ .15f, .1505f, .151f, 1.f };
const ImVec4 DARK_GRAY = ImVec4{ .2f, .205f, .21f, 1.f };

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutStyle::NutStyle( nString name )
	: NutBasic( name ),
	colors( ),
	rules( ) 
{
	this->OnStyleInit( );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutStyle::SetColor( ImGuiCol_ query, const ImVec4& value ) {
	auto color = this->GetColor( query );

	if ( color.has_value( ) )
		color->get( ).value = value;
	else
		this->colors.emplace_back( NutStyleColor{ query, value } );
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
}

void NutStyle::OnStyleInit( ) {
	this->SetColor( ImGuiCol_WindowBg,				ImVec4{ .1f, .105f, .11f, 1.f } );
	this->SetColor( ImGuiCol_PopupBg,				ImVec4{ .1f, .105f, .11f, 1.f } );
	this->SetColor( ImGuiCol_TextDisabled,			ImVec4{ .3f, .305f, .31f, 1.f } );
	this->SetColor( ImGuiCol_MenuBarBg,				ImVec4{ .094f, .094f, .094f, 1.f } );
	this->SetColor( ImGuiCol_Header,				DARK_GRAY );
	this->SetColor( ImGuiCol_HeaderHovered,			ImVec4{ .86f, .41f, .1f, 1.f } );
	this->SetColor( ImGuiCol_HeaderActive,			ORANGE );
	this->SetColor( ImGuiCol_Button,				DARK_GRAY );
	this->SetColor( ImGuiCol_ButtonHovered,			ImVec4{ .3f, .305f, .31f, 1.f } );
	this->SetColor( ImGuiCol_ButtonActive,			GRAY );
	this->SetColor( ImGuiCol_FrameBg,				DARK_GRAY );
	this->SetColor( ImGuiCol_FrameBgHovered,		ImVec4{ .3f, .305f, .31f, 1.f } );
	this->SetColor( ImGuiCol_FrameBgActive,			GRAY );
	this->SetColor( ImGuiCol_Tab,					GRAY );
	this->SetColor( ImGuiCol_TabHovered,			DARK_ORANGE );
	this->SetColor( ImGuiCol_TabActive,				ORANGE );
	this->SetColor( ImGuiCol_TabUnfocused,			GRAY );
	this->SetColor( ImGuiCol_TabUnfocusedActive,	DARK_GRAY );
	this->SetColor( ImGuiCol_TitleBg,				GRAY );
	this->SetColor( ImGuiCol_TitleBgActive,			GRAY );
	this->SetColor( ImGuiCol_TitleBgCollapsed,		GRAY );
	this->SetColor( ImGuiCol_DockingPreview,		ORANGE );
	this->SetColor( ImGuiCol_SeparatorHovered,		ORANGE );
	this->SetColor( ImGuiCol_SeparatorActive,		ORANGE );
	this->SetColor( ImGuiCol_CheckMark,				ORANGE );
	this->SetColor( ImGuiCol_SliderGrab,			ORANGE );
	this->SetColor( ImGuiCol_SliderGrabActive,		ImVec4{ .86f, .41f, .1f, 1.f } );
	this->SetColor( ImGuiCol_ScrollbarBg,			ImVec4{ .117f, .117f, .117f, .8f } );
	this->SetColor( ImGuiCol_ScrollbarGrab,			DARK_ORANGE );
	this->SetColor( ImGuiCol_ScrollbarGrabHovered,	ORANGE );
	this->SetColor( ImGuiCol_ScrollbarGrabActive,	ORANGE );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET 
///////////////////////////////////////////////////////////////////////////////////////////
std::vector< NutStyleColor >& NutStyle::GetColors( ) const { return this->colors; }

std::vector< NutStyleRule >& NutStyle::GetRules( ) const { return this->rules; }

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
