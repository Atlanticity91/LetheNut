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

#include <fstream>
#include <LetheNut/NutEditor.hpp>
#include <LetheNut/Modules/NutKernel.hpp>
#include <LetheNut/Tools/NutBrowser.hpp>
#include <LetheNut/Tools/NutProfiler.hpp>
#include <LetheNut/Tools/NutProperties.hpp>
#include <LetheNut/Tools/NutScene.hpp>
#include <LetheNut/Tools/NutViewport.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutKernel::NutKernel( )
	: NutModule( "Kernel" ),
    config( ),
    libraries( )
{ }

NutKernel::~NutKernel( ) { 
    for ( auto lib : this->libraries )
        delete lib;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutKernel::Initialize( class NutEditor* editor ) {
    if ( this->config.Load( "NutEditor.json" ) ) {
        for ( auto lib : this->config.Get<nJSON::StringArray>( "Libraries" ) ) {
            if ( !lib.empty( ) ) {
                NutLibrary* library = new NutLibrary( lib );

                if ( library->GetIsValid( ) )
                    this->libraries.emplace_back( library );
                else
                    delete library;
            }
        }

        for ( auto module_ : this->config.Get<nJSON::StringArray>( "Modules" ) ) {
            if ( !module_.empty( ) ) {
            }
        }
    }
}

#include <LetheNut/Editors/Nodes/NutNodeEditor.hpp>
#include <LetheNut/Editors/Text/NutTextEditor.hpp>
void NutKernel::OnCreate( class NutEditor* editor ) {
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

    editor->OpenPanel<NutBrowser>( editor );
    editor->OpenPanel<NutProfiler>( editor );
    editor->OpenPanel<NutProperties > ( editor );
    editor->OpenPanel<NutScene>( editor );
    editor->OpenPanel<NutViewport>( editor );

    editor->OpenPanel<NutTextEditor>( editor );
    editor->OpenPanel<NutNodeEditor>( editor );
}

void NutKernel::Process( class NutEditor* editor) { }

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE STATIC
///////////////////////////////////////////////////////////////////////////////////////////
void NutKernel::OnOpen( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) {
}

void NutKernel::OnOpenScene( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnLoad( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnSave( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { 
}

void NutKernel::OnImport( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnExport( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnExit( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) {
    // DISPLAY SAVE POPUP

    editor->Exit( );
}

void NutKernel::OnUndo( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnRedo( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnCopy( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnCut( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnPaste( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnTheme( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent ) { }

void NutKernel::OnAbout( class NutMenuItem& item, class NutEditor*, class NutPanel& parent ) { }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const std::string NutKernel::GetVersion( ) const { 
    return this->config.Get<std::string>( "Version" ); 
}

const std::string NutKernel::GetLicense( ) const {
    return this->config.Get<std::string>( "License" );
}

NutLibrary* NutKernel::GetLibrary( nString name ) const {
    for ( auto lib : this->libraries ) {
        if ( strcmp( name, lib->GetName( ) ) == 0 )
            return lib;
    }

    return nullptr;
}
