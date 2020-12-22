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

#include <LetheNut/UI/NutWindow.hpp>
#include <LetheNut/Vendor/GLFW.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutWindow::NutWindow( nString label, const nUInt width, const nUInt height )
	: NutPopup( 
        label, width, height, 
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus 
    ),
    style( "Default" ),
    popups( )
{ }

NutWindow::~NutWindow( ) { GLFW::Destroy( this->handle ); }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutWindow::OnCreate( NutEditor* editor ) {
    ImGUI::Initialize( this->GetHandle( ) );
    ImGUI::ApplyStyle( this->style );
}

void NutWindow::OnEditorRender( NutEditor* editor ) {
    NutPopup::OnToolProcess( editor );

    ImGUI::Begin( );
        ImGUI::BeginPopup( this->GetName( ), this->flags, this->size, 0.f, &this->is_open );
            ImGUI::BeginDockspace( );

            NutPopup::OnPanelRender( editor );

            this->OnPopupRender( editor );

        ImGUI::EndPopup( );
    ImGUI::End( );
}

void NutWindow::OnPopupRender( NutEditor* editor ) {
    auto idx = this->popups.size( );

    while ( idx > 0 ) {
        idx -= 1;

        auto* popup = this->popups[ idx ];

        if ( popup->GetIsOpen( ) )
            popup->OnEditorRender( editor );
        else {
            delete popup;

            this->popups.erase( this->popups.begin( ) + idx );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
class NutStyle& NutWindow::GetStyle( ) const { return this->style; }

nPointer& NutWindow::GetHandle( ) const { return this->handle; }
