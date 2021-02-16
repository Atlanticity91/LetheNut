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

#include <LetheNut/UI/NutWindow.hpp>
#include <LetheNut/Vendor/ImGUI.hpp>
#include <LetheNut/Vendor/OpenGL.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutWindow::NutWindow( nString name, const nInt width, const nInt height )
	: NutUIElement( name ),
	window{ nullptr, name, width, height },
	context( nullptr ),
	panels( )
{ }

NutWindow::~NutWindow( ) {
	ImGUI::Cleanup( );
	GLFW::Destroy( this->window );
}

void NutWindow::Enable( NutEditor* editor, nString panel ) {
	auto query = this->panels[ panel ];

	if ( query )
		(*query)->Enable( editor, this );
}

void NutWindow::Disable( NutEditor* editor, nString panel ) {
	auto query = this->panels[ panel ];

	if ( query )
		(*query)->Disable( editor, this );
}

void NutWindow::Destroy( NutEditor* editor, nString panel ) {
	auto* query = this->panels[ panel ];

	if ( query ) {
		(*query)->OnDestroy( editor, this );

		this->panels.Erase( panel );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
bool NutWindow::Open( const nPointer ressources ) {
	auto state = GLFW::Create( this->window, ressources );

	if ( state )
		ImGUI::Setup( this->window, this->context );

	return state;
}

bool NutWindow::OnDestroy( NutEditor* editor ) { return true; }

void NutWindow::OnRender( NutEditor* editor ) { 
	GLFW::SetContext( this->window );
	ImGUI::Start( this->context );

	if ( ImGUI::Window( this ) ) {
		ImGUI::DockSpace( );

		if ( this->GetHasMenu( ) )
			this->OnRenderMenu( editor, this, nullptr );

		bool t = true;
		ImGui::ShowDemoWindow( &t );

		this->panels.Foreach(
			[ this ]( auto& panel, NutEditor* editor ) {
				if ( panel->GetIsActive( ) ) {
					if ( ImGUI::Panel( panel ) ) {
						if ( !ImGui::IsWindowCollapsed( ) && !ImGUI::GetIsSkiped( ) ) {
							if ( ImGui::IsWindowFocused( ) )
								panel->OnProcess( editor, this );

							panel->OnRenderMenu( editor, this, panel );
							panel->OnRender( editor, this );
						}
					}

					ImGui::End( );
				}

				if ( !panel->GetIsOpen( ) ) {
					if ( panel->OnDestroy( editor, this ) && !panel->GetIsOpen( ) )
						this->panels.Erase( panel->GetLabel( ) );
				}
			},
			editor
		);
	}

	ImGui::End( );
	ImGUI::Stop( );
	GLFW::Process( this->window );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
GLFW::Window& NutWindow::GetHandle( ) const { return this->window; }

const ImGuiContext* NutWindow::GetContext( ) const { return this->context; }

bool NutWindow::ShouldRun( ) const { return GLFW::ShouldRun( this->window ); }

NutList<NutPanel*>& NutWindow::GetPanels( ) const { return this->panels; }

NutPanel* NutWindow::GetPanel( nString name ) const { return *this->panels[ name ]; }
