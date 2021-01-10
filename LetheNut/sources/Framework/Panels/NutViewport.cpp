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

#include <LetheNut/Framework/Panels/NutViewport.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutViewport::NutViewport( )
	: NutPanel( "Viewport" ),
	projection( ),
	camera( -0.4f, 4.f ),
	renderer( )
{ 
	OpenGL::Create( this->renderer, 240, 160 );
	OpenGL::Refresh( this->renderer, ImVec4{ 204, 204, 204, 255 } );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutViewport::OnCreate( NutEditor* editor, NutWindow* parent ) { }

void NutViewport::OnProcess( NutEditor* editor, NutWindow* parent ) { }

void NutViewport::OnRender( NutEditor* editor, NutWindow* parent ) { 
	auto size = ImGui::GetContentRegionAvail( );

	if ( this->view_size.x != size.x || this->view_size.y != size.y ) {
		this->view_size = size;
		this->projection.SetSize( this->view_size );
		this->projection.Calculate( );

		OpenGL::Resize( this->renderer, this->view_size );
	}
	
	this->camera.Calculate( );

	OpenGL::Clear( this->renderer );
	ImGUI::Image( this->renderer );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutProjection& NutViewport::GetProjection( ) const { return this->projection; }

NutCamera& NutViewport::GetCamera( ) const { return this->camera; }

OpenGL::Frame& NutViewport::GetRenderer( ) const { return this->renderer; }
