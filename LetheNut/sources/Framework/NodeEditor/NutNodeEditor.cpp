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

#include <LetheNut/Framework/Editors/Nodes/NutNodeEditor.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeEditor::NutNodeEditor( )
	: NutPanel( "Blueprint" ),
	canvas( 4.f )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutNodeEditor::OnCreateMenus( ) { }

void NutNodeEditor::OnCreateModals( ) { }

void NutNodeEditor::OnCreate( NutEditor* editor, NutWindow* parent ) { }

bool NutNodeEditor::OnDestroy( NutEditor* editor, NutWindow* parent ) {
	return true;
}

void NutNodeEditor::OnProcess( NutEditor* editor, NutWindow* parent ) { 
    if ( !ImGui::IsMouseDown( ImGuiMouseButton_Left ) && ImGui::IsWindowHovered( ) ) {
        if ( ImGui::IsMouseDragging( ImGuiMouseButton_Middle ) )
            this->canvas.offset += ImGUI::GetMouseDelta( );

        if ( ImGUI::GetIsShiftDown( ) && !ImGUI::GetIsCtrltDown( ) )
            this->canvas.offset.x += ImGUI::GetScrollWheel( ) * 16.0f;

        if ( !ImGUI::GetIsShiftDown( ) && !ImGUI::GetIsCtrltDown( ) ) {
            this->canvas.offset.y += ImGUI::GetScrollWheel( ) * 16.0f;
            this->canvas.offset.x += ImGUI::GetScrollWheelH( ) * 16.0f;
        }

        if ( !ImGUI::GetIsShiftDown( ) && ImGUI::GetIsCtrltDown( ) ) {
            if ( ImGUI::GetScrollWheel( ) != 0.f ) {
                auto mouseRel = ImGUI::GetMouseRelPos( );
                float prevZoom = this->canvas.zoom_level;

                this->canvas.zoom_level = ImClamp( this->canvas.zoom_level + ImGUI::GetScrollWheel( ) * this->canvas.zoom_level / 16.f, 1.f, this->canvas.zoom_max );
                float zoomFactor = ( prevZoom - this->canvas.zoom_level ) / prevZoom;
                this->canvas.offset += ( mouseRel - this->canvas.offset ) * zoomFactor;
            }
        }
    }

    if ( ImGui::IsMouseClicked( ImGuiMouseButton_Right ) ) {
        auto pos = ImGUI::GetMouseRelPos( ) - this->canvas.offset;

    }
}

void NutNodeEditor::OnRender( NutEditor* editor, NutWindow* parent ) { 
	if ( ImGUI::Canvas( this->canvas ) ) {

		ImGUI::EndCanvas( this->canvas );
	}
}
