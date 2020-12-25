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

#include <LetheNut/NutEditor.hpp>
#include <LetheNut/NutFramework.hpp>
#include <LetheNut/Modules/NutKernel.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutKernel::NutKernel( )
    : NutModule( "Kernel" ),
    config( )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutKernel::OnCreate(  NutEditor* editor ) {
    auto file_menu = editor->CreateMenu( "File" );

    file_menu->CreateButton( "Open", "Ctrl+O", NutKernel::OnOpen );
    file_menu->CreateButton( "Open Scene", NO_SHORTCUT, NutKernel::OnOpenScene );
    file_menu->CreateButton( "Load", "Ctrl+L", NutKernel::OnLoad );
    file_menu->CreateButton( "Save", "Ctrl+S", NutKernel::OnSave );
    file_menu->CreateSeparator( );
    file_menu->CreateButton( "Import", NO_SHORTCUT, NutKernel::OnImport );
    file_menu->CreateButton( "Export", NO_SHORTCUT, NutKernel::OnExport );
    file_menu->CreateSeparator( );
    file_menu->CreateButton( "Exit", "Ctrl+Q", NutKernel::OnExit );

    auto edit_menu = editor->CreateMenu( "Edit" );

    edit_menu->CreateButton( "Undo", "Ctrl+Z", NutKernel::OnUndo );
    edit_menu->CreateButton( "Redo", "Ctrl+Y", NutKernel::OnRedo );
    edit_menu->CreateSeparator( );
    edit_menu->CreateButton( "Copy", "Ctrl+C", NutKernel::OnCopy );
    edit_menu->CreateButton( "Cut", "Ctrl+X", NutKernel::OnCut );
    edit_menu->CreateButton( "Paste", "Ctrl+V", NutKernel::OnPaste );

    auto prefs_menu = editor->CreateMenu( "Preferences" );

    prefs_menu->CreateButton( "Theme", NO_SHORTCUT, NutKernel::OnTheme );
    prefs_menu->CreateSeparator( );
    prefs_menu->CreateButton( "About", NO_SHORTCUT, NutKernel::OnAbout );

    editor->OpenTool<NutBrowser>( editor );
    editor->OpenTool<NutProfiler>( editor );
    editor->OpenTool<NutProperties > ( editor );
    editor->OpenTool<NutScene>( editor );
    editor->OpenTool<NutViewport>( editor );

    editor->OpenEditor<NutTextEditor>( editor );
    editor->OpenEditor<NutNodeEditor>( editor );
}

void NutKernel::Initialize( NutEditor* editor ) {
    if ( this->config.Load( "Assets/NutEditor.json" ) ) {
        this->LoadLibraries( editor );
        this->LoadModules( editor );
    }
}

void NutKernel::Process(  NutEditor* editor ) { }

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE
///////////////////////////////////////////////////////////////////////////////////////////
void NutKernel::LoadLibraries( NutEditor* editor ) {
    for ( auto path : this->config.Get<nJSON::StringArray>( "Libraries" ) ) {
        if ( !path.empty( ) )
            editor->LoadLibrary( path );
    }
}

void NutKernel::LoadModules( NutEditor* editor ) {
    for ( auto path : this->config.Get<nJSON::StringArray>( "Modules" ) ) {
        if ( !path.empty( ) ) 
            editor->LoadModule( path );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE STATIC
///////////////////////////////////////////////////////////////////////////////////////////
void NutKernel::OnOpen(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) {
}

void NutKernel::OnOpenScene(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnLoad(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnSave(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { 
}

void NutKernel::OnImport(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnExport(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnExit(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) {
    // DISPLAY SAVE POPUP

    editor->Exit( );
}

void NutKernel::OnUndo(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnRedo(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnCopy(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnCut(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnPaste(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnTheme(  NutMenuItem& item,  NutEditor* editor,  NutPanel& parent ) { }

void NutKernel::OnAbout(  NutMenuItem& item,  NutEditor*,  NutPanel& parent ) { }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const std::string NutKernel::GetVersion( ) const { 
    return this->config.Get<std::string>( "Version" ); 
}

const std::string NutKernel::GetLicense( ) const {
    return this->config.Get<std::string>( "License" );
}
