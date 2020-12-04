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

#include <LetheNut/Tools/NutTool.hpp>
#include <LetheNut/UI/NutPopup.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutPopup::NutPopup( nString name, ImGuiWindowFlags flags )
    : NutPanel( name, true, ImGUI::NO_PADDING ),
    panels( ),
    is_open( true ),
    size( 0.f, 0.f ),
    flags( flags ) 
{ }

NutPopup::NutPopup( nString name, nUInt width, nUInt height, ImGuiWindowFlags flags )
    : NutPanel( name, true, ImGUI::NO_PADDING ),
    panels( ),
    is_open( true ),
    size( (float)width, (float)height ),
    flags( flags ) 
{ }

NutPopup::~NutPopup( ) {
    for ( auto& panel : this->panels )
        delete panel;
}

class NutPanel* NutPopup::Enable( ) { return this; }

class NutPanel* NutPopup::Disable( ) { return this; }

class NutPopup* NutPopup::EnablePanel( nString name ) {
    auto* panel = this->GetPanel( name );

    if ( panel )
        panel->Enable( );

    return this;
}

class NutPopup* NutPopup::DisabePanel( nString name ) {
    auto* panel = this->GetPanel( name );

    if ( panel )
        panel->Disable( );

    return this;
}

void NutPopup::ClosePanel( nString name ) {
    auto idx = this->panels.size( );

    while ( idx > 0 ) {
        idx -= 1;

        auto* panel = this->panels[ idx ];

        if ( std::strcmp( name, panel->GetName( ) ) != 0 )
            continue;
        else {
            delete panel;

            this->panels.erase( this->panels.begin( ) + idx );

            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutPopup::OnEditorRender( class NutEditor* editor ) {
    this->OnToolProcess( editor );

    ImGUI::BeginPopup( this->GetName( ), this->flags, this->size, 1.25f, &this->is_open );

    this->OnPanelRender( editor );

    ImGUI::EndPopup( );
}

void NutPopup::OnToolProcess( class NutEditor* editor ) {
    for ( auto& panel : this->panels ) {
        if ( dynamic_cast<NutTool*>( panel ) ) {
            auto* tool = reinterpret_cast<NutTool*>( panel );

            if ( tool->GetIsRunning( ) )
                tool->Process( editor );
        }
    }
}

void NutPopup::OnPanelRender( class NutEditor* editor ) {
    NutPanel::OnEditorRender( editor );

    for ( auto& panel : this->panels ) {
        if ( panel->GetIsActive( ) ) {
            ImGUI::BeginPanel( panel->GetName( ), panel->GetPadding( ) );
                if ( !ImGui::IsWindowCollapsed( ) ) {
                    if ( ImGui::IsWindowFocused( ) && dynamic_cast<NutTool*>( panel ) ) {
                        auto* tool = reinterpret_cast<NutTool*>( panel );

                        tool->OnEditorProcess( editor );
                    }

                    panel->OnEditorRender( editor );
                }
            ImGUI::EndPanel( );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutPopup::GetIsOpen( ) const { return this->is_open; }

ImGuiWindowFlags NutPopup::GetFlags( ) const { return this->flags; }
