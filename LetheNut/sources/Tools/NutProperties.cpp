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

#include <LetheNut/Framework/Context/NutPropertyContext.hpp>
#include <LetheNut/Tools/NutProperties.hpp>
#include <LetheNut/Vendor/ImGUI.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutProperties::NutProperties( )
	: NutTool( "Properties", ImGUI::DEFAULT_PADDING ),
	panes( )
{ }

void NutProperties::Register( nString name, nString description, NutPropertyContent content ) {
	this->Register( name, description, nullptr, content );
}

void NutProperties::Register( nString name, nString description, NutPropertyHas condition, NutPropertyContent content ) {
	if ( nHelper::GetIsValid( name ) && content ) {
		for ( auto& pane : this->panes ) {
			if ( strcmp( pane.name, name ) != 0 )
				continue;

			return;
		}

		auto pane = NutPropertyPane{ name ,description, condition, content };

		this->panes.emplace_back( pane );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED 
///////////////////////////////////////////////////////////////////////////////////////////
void NutProperties::OnEditorRender( NutEditor* editor ) { 
	for ( auto& pane : this->panes ) {
		if ( !pane.condition || ( pane.condition && pane.condition( editor, this->context ) ) )
			ImGUI::Tree( pane.name, pane.description, pane.content, editor, this->context );
	}
}
