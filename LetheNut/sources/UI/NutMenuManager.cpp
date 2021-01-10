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

#include <LetheNut/UI/Menus/NutMenuManager.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC  
///////////////////////////////////////////////////////////////////////////////////////////
NutMenuManager::NutMenuManager( )
	: has_menu( false ), 
	menus( )
{ }

void NutMenuManager::Lock( nString label ) {
	auto* menu = this->menus[ label ];

	if ( menu )
		menu->Lock( );
}

void NutMenuManager::UnLock( nString label ) {
	auto* menu = this->menus[ label ];

	if ( menu )
		menu->UnLock( );
}

void NutMenuManager::Lock( nString menu, nString item ) {
	auto* query = this->menus[ menu ];

	if ( query )
		query->Lock( item );
}

void NutMenuManager::UnLock( nString menu, nString item ) {
	auto* query = this->menus[ menu ];

	if ( query )
		query->UnLock( item );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED  
///////////////////////////////////////////////////////////////////////////////////////////
NutMenu* NutMenuManager::CreateMenu( nString label, bool is_visible ) {
	if ( !this->menus[ label ] ) {
		auto* menu = this->menus.Append( label, is_visible );

		if ( menu && !this->has_menu )
			this->has_menu = true;

		return menu;
	}

	return nullptr;
}

void NutMenuManager::OnRenderMenu( NutEditor* editor, NutWindow* window, NutPanel* panel ) {
	if ( ImGui::BeginMenuBar( ) ) {
		this->menus.Foreach(
			[]( auto& menu, NutEditor* editor, NutWindow* window, NutPanel* panel ) {
				if ( menu.GetIsVisible( ) && ImGui::BeginMenu( menu.GetLabel( ) ) ) { 
					menu.OnRender( editor, window, panel );
					
					ImGui::EndMenu( );
				}
			},
			editor, window, panel
		);

		ImGui::EndMenuBar( );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutMenuManager::GetHasMenu( ) const { return this->has_menu; }

NutList<NutMenu>& NutMenuManager::GetMenus( ) const { return this->menus; }

NutMenu* NutMenuManager::GetMenu( nString label ) const { return this->menus[ label ]; }
