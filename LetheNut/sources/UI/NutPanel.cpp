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

#include <LetheNut/UI/NutPanel.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutPanel::NutPanel( nString label )
	: NutPanel( label, ImVec2{ } )
{ }

NutPanel::NutPanel( nString label, ImGuiWindowFlags flags )
	: NutPanel( label, ImVec2{ }, flags )
{ }

NutPanel::NutPanel( nString label, const ImVec2& padding )
	: NutPanel( label, padding, 0 )
{ }

NutPanel::NutPanel( nString label, const ImVec2& padding, ImGuiWindowFlags flags )
	: NutUIElement( label ),
	is_active( true ),
	padding( padding ),
	flags( flags )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED 
///////////////////////////////////////////////////////////////////////////////////////////
void NutPanel::Enable( NutEditor* editor, NutWindow* parent ) {
	if ( !this->is_active ) {
		this->is_active = true;

		this->OnEnable( editor, parent );
	}
}

void NutPanel::Disable( NutEditor* editor, NutWindow* parent ) {
	if ( this->is_active ) {
		this->is_active = false;

		this->OnDisable( editor, parent );
	}
}

void NutPanel::OnEnable( NutEditor* editor, NutWindow* parent ) { }

void NutPanel::OnDisable( NutEditor* editor, NutWindow* parent ) { }

bool NutPanel::OnDestroy( NutEditor* editor, NutWindow* parent ) { return true; }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutPanel::GetIsActive( ) const { return this->is_active; }

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE GET
///////////////////////////////////////////////////////////////////////////////////////////
ImGuiWindowFlags NutPanel::GetFlags( ) const { return this->flags; }

ImVec2& NutPanel::GetPadding( ) const { return this->padding; }

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR 
///////////////////////////////////////////////////////////////////////////////////////////
NutMenu* NutPanel::operator[]( nString label ) const { return this->GetMenu( label ); }
