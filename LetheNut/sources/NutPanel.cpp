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

#include <LetheNut/UI/NutPanel.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutPanel::NutPanel( nString name, bool is_active, const ImVec2& padding )
	: NutBasic( name ),
	is_active( is_active ),
	padding( padding ),
	menus( ) 
{ }

NutPanel::NutPanel( nString name, bool is_active, const ImVec2&& padding )
	: NutPanel( name, is_active, padding )
{ }

class NutPanel* NutPanel::Enable( ) {
	this->is_active = true;

	return this;
}

class NutPanel* NutPanel::Disable( ) {
	this->is_active = false;

	return this;
}

class NutMenu* NutPanel::CreateMenu( nString name ) {
	if ( nHelper::GetIsValid( name ) ) {
		class NutMenu menu = NutMenu( name );

		this->menus.emplace_back( menu );

		return &this->menus[ this->menus.size( ) - 1 ];
	}

	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutPanel::OnCreate( NutEditor* editor ) { }

void NutPanel::OnEditorRender( NutEditor* editor ) {
	for ( auto& menu : this->menus )
		menu.OnRender( editor, *this );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutPanel::GetIsActive( ) const { return this->is_active; }

const ImVec2& NutPanel::GetPadding( ) const { return this->padding; }

class NutMenu* NutPanel::GetMenu( nString name ) const {
	if ( nHelper::GetIsValid( name ) ) {
		auto hash = nHelper::Hash_MD5( name );

		for ( auto& menu : this->menus ) {
			if ( hash != menu.GetHash( ) )
				continue;
			else
				return &menu;
		}
	}

	return nullptr;
}
