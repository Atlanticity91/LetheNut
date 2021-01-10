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

#include <LetheNut/UI/Menus/NutMenu.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC  
///////////////////////////////////////////////////////////////////////////////////////////
NutMenu::NutMenu( nString label, bool is_visible )
	: NutElement( label ),
	is_visible( is_visible ),
	is_locked( false ),
	items( ) 
{ }

void NutMenu::Append( ) { this->items.Append( ); }

void NutMenu::Append( nString label, NutMenu* menu ) {
	if ( nHelper::GetIsValid( label ) && !this->items[ label ] && menu )
		this->items.Append( label, menu );
}

void NutMenu::Append( nString label, nString shortcut, NutItemCallback on_click ) {
	if ( nHelper::GetIsValid( label ) && !this->items[ label ] && on_click )
		this->items.Append( label, shortcut, on_click );
}

void NutMenu::Append( nString label, bool state, NutItemCallback on_mark, NutItemCallback on_unmark ) {
	if ( nHelper::GetIsValid( label ) && !this->items[ label ] && on_mark )
		this->items.Append( label, state, on_mark, on_unmark );
}

void NutMenu::Lock( ) { this->is_locked = true; }

void NutMenu::UnLock( ) { this->is_locked = false; }

void NutMenu::Lock( nString label ) {
	auto* item = this->items[ label ];

	if ( item )
		item->is_active = false;
}

void NutMenu::UnLock( nString label ) {
	auto* item = this->items[ label ];

	if ( item )
		item->is_active = true;
}

void NutMenu::OnRender( NutEditor * editor, NutWindow* window, NutPanel* parent ) {
	this->items.Foreach( 
		[ this ]( auto& item, NutEditor* editor, NutWindow* window, NutPanel* parent ) {
			switch ( item.type ) {
				case EMenuItemTypes::EMIT_SUBMENU  : this->OnRenderSubMenu( item, editor, window, parent ); break;
				case EMenuItemTypes::EMIT_BUTTON   : this->OnRenderButton( item, editor, window, parent ); break;
				case EMenuItemTypes::EMIT_CHECKBOX : this->OnRenderCheckbox( item, editor, window, parent ); break;

				default: ImGui::Separator( ); break;
			}
		},
		editor, window, parent
	);
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE  
///////////////////////////////////////////////////////////////////////////////////////////
void NutMenu::OnRenderSubMenu( NutMenuItem& item, NutEditor* editor, NutWindow* window, NutPanel* parent ) {
	if ( ImGui::BeginMenu( item.label ) ) {
		item.sub_menu->OnRender( editor, window, parent );

		ImGui::EndMenu( );
	}
}

void NutMenu::OnRenderButton( NutMenuItem& item, NutEditor* editor, NutWindow* window, NutPanel* parent ) {
	if ( ImGui::MenuItem( item.label, item.shortcut, nullptr, !this->is_locked && item.is_active) )
		item.on_click( item, editor, window, parent );
}

void NutMenu::OnRenderCheckbox( NutMenuItem& item, NutEditor* editor, NutWindow* window, NutPanel* parent ) {
	if ( !this->is_locked && item.is_active ) {
		bool old = item.check_state;

		ImGui::Checkbox( item.label, &item.check_state );

		if ( old != item.check_state ) {
			if ( item.check_state )
				item.on_mark( item, editor, window, parent );
			else if ( item.on_unmark )
				item.on_unmark( item, editor, window, parent );
		}
	} else
		ImGui::Checkbox( item.label, nullptr );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutMenu::GetIsVisible( ) const { return this->is_visible && this->items; }
