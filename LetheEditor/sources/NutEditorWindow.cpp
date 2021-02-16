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

#include <LetheEditor/NutEditorWindow.hpp>
#include <LetheNut/NutFramework.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutEditorWindow::NutEditorWindow( )
	: NutWindow( "LetheNut - Editor", 1280, 720 )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutEditorWindow::OnCreateMenus( ) {
	auto lambda = [ ]( const NutMenuItem&, NutEditor*, NutWindow*, NutPanel* ) { };
	auto* file_menu = this->CreateMenu( "File", true );

	file_menu->Append( "Open", "Ctrl+O", lambda );
	file_menu->Append( "Open Scene", "", lambda );
	file_menu->Append( "Save", "Ctrl+S", lambda );
	file_menu->Append( "Save As", "Ctrl+Maj+S", lambda );
	file_menu->Append( );
	file_menu->Append( "Import", "", lambda );
	file_menu->Append( "Export", "", lambda );
	file_menu->Append( );
	file_menu->Append( "Exit", "Ctrl+Q", lambda );

	auto* edit_menu = this->CreateMenu( "Edit", true );

	edit_menu->Append( "Undo", "Ctrl+Z", lambda );
	edit_menu->Append( "Redo", "Ctrl+Y", lambda );
	edit_menu->Append( );
	edit_menu->Append( "Copy", "Ctrl+C", lambda );
	edit_menu->Append( "Cut", "Ctrl+X", lambda );
	edit_menu->Append( "Paste", "Ctrl+V", lambda );

	auto* prefs_menu = this->CreateMenu( "Preferences", true );

	prefs_menu->Append( "Theme", "", lambda );
	prefs_menu->Append( );
	prefs_menu->Append( "About", "", lambda );
}

void NutEditorWindow::OnCreate( NutEditor* editor ) {
	this->Create<NutBrowser>( editor );
	this->Create<NutProfiler>( editor );
	this->Create<NutProperties>( editor );
	this->Create<NutScene>( editor );
	this->Create<NutViewport>( editor );

	this->Create<NutTextEditor>( editor );
	this->Create<NutNodeEditor>( editor );
}
