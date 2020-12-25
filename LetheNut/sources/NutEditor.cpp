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
#include <LetheNut/Tools/NutTool.hpp>
#include <LetheNut/Vendor/STB.hpp>
#include <LetheNut/Vendor/GLFW.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutEditor::NutEditor( )
    : NutWindow( "Editor", 0, 0 ),
    images( ),
    libraries( ),
    modules( ),
    windows( ),
    modules_libs( )
{ }

NutEditor::~NutEditor( ) {
    for ( auto& image : this->images )
        OpenGL::Destroy( image.GetTexture( ) );

    for ( auto& module_lib : this->modules_libs )
        module_lib.Close( );

    for ( auto& library : this->libraries )
        delete library;

    auto idx = this->modules.size( );
    while ( idx-- > 0 )
        delete this->modules[ idx ];

    for ( auto& popup : this->popups )
        delete popup;

    for ( auto& window : this->windows ) 
        delete window;

    NutPopup::~NutPopup( );
    NutWindow::~NutWindow( );
    ImGUI::Destroy( );
    GLFW::Cleanup( );
}

bool NutEditor::LoadLibrary( nString path ) {
    if ( nHelper::GetIsValid( path ) ) {
        auto* library = new NutLibrary( path );

        if ( library->GetIsValid( ) ) {
            this->libraries.emplace_back( library );

            return true;
        } else
            delete library;
    }

    return false;
}

bool NutEditor::LoadLibrary( const std::string& path ) {
    return this->LoadLibrary( path.c_str( ) );
}

bool NutEditor::LoadModule( nString path ) {
    if ( nHelper::GetIsValid( path ) ) {
        typedef void ( *NutLoadModule )( NutEditor*, ImGuiContext* );

        auto module_lib = NutPlatformLib( path );

        if ( module_lib.GetIsValid( ) ) {
            NutLoadModule module_load = module_lib[ "NutLoadModuleLib" ];

            if ( module_load ) {
                module_load( this, ImGui::GetCurrentContext( ) );

                this->modules_libs.emplace_back( module_lib );

                return true;
            } else
                module_lib.Close( );
        }
    }

    return false;
}

bool NutEditor::LoadModule( const std::string& path ) {
    return this->LoadModule( path.c_str( ) );
}

bool NutEditor::LoadImageAs( nString alias, nString path ) {
    return this->LoadImageAs( alias, path, 1, 1 );
}

bool NutEditor::LoadImageAs( const std::string& alias, const std::string& path ) {
    return this->LoadImageAs( alias.c_str( ), path.c_str( ), 1, 1 );
}

bool NutEditor::LoadImageAs( nString alias, nString path, nUShort columns, nUShort rows ) {
   if ( nHelper::GetIsValid( alias ) && nHelper::GetIsValid( path ) && !this->GetImage( alias ) ) {
       auto hash = nHelper::Hash_MD5( alias );
       auto texture = OpenGL::Texture( );
       auto file = STB::Image( );

       if ( STB::Load( file, path ) && OpenGL::Create( texture, file.width, file.height, file.data ) ) {
           STB::Destroy( file );

           this->images.emplace_back( NutImage( hash, texture, columns, rows ) );

           return true;
       }
   }

   return false;
}

bool NutEditor::LoadImageAs( const std::string& alias, const std::string& path, nUShort columns, nUShort rows ) {
    return this->LoadImageAs( alias.c_str( ), path.c_str( ), columns, rows );
}

bool NutEditor::LoadImageAs( OpenGL::Texture& texture, nString alias, nString path ) {
    return this->LoadImageAs( texture, alias, path, 1, 1 );
}

bool NutEditor::LoadImageAs( OpenGL::Texture& texture, const std::string& alias, const std::string& path ) {
    return this->LoadImageAs( texture, alias.c_str( ), path.c_str( ), 1, 1 );
}

bool NutEditor::LoadImageAs( OpenGL::Texture& texture, nString alias, nString path, nUShort columns, nUShort rows ) {
    if ( this->LoadImageAs( alias, path, columns, rows ) ) {
        texture = this->GetImage( alias )->GetTexture( );

        return true;
    }

    return false;
}

bool NutEditor::LoadImageAs( OpenGL::Texture& texture, const std::string& alias, const std::string& path, nUShort columns, nUShort rows ) {
    return this->LoadImageAs( texture, alias.c_str( ), path.c_str( ), columns, rows );
}

void NutEditor::EnableModule( nString name ) {
    auto* module = this->GetModule<NutModule>( name );

    if ( module )
        module->Enable( );
}

void NutEditor::DisableModule( nString name ) {
    auto* module = this->GetModule<NutModule>( name );

    if ( module )
        module->Disable( );
}

void NutEditor::Destroy( nString name ) {
    if ( nHelper::GetIsValid( name ) ) {
        auto hash = nHelper::Hash_MD5( name );
        auto idx = this->modules.size( );

        while ( idx > 0 ) {
            idx -= 1;

            auto* module = this->modules[ idx ];

            if ( hash != module->GetHash( ) )
                continue;
            else if ( !dynamic_cast<NutKernel*>( module ) ) {
                delete module;

                this->modules.erase( this->modules.begin( ) + idx );

                return;
            }
        }
    }
}

void NutEditor::Exit( ) { this->is_open = false; }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutEditor::OnCreate( class NutEditor* editor ) {
    NutWindow::OnCreate( editor );

    editor->Register< NutKernel >( );
}

bool NutEditor::Start( int argc, char** argv ) {
    return GLFW::Initialize( this->GetHandle( ) ) && OpenGL::Initialize( this->GetHandle( ) );
}

void NutEditor::Run( ) {
    this->OnCreate( this );

    while ( this->is_open && GLFW::ShouldRun( this->GetHandle( ) ) ) {
        for ( auto& module : this->modules ) {
            if ( module->GetIsActive( ) )
                module->Process( this );
        }
        
        this->OnEditorRender( this );

        auto idx = this->windows.size( );
        while ( idx > 0 ) {
            idx -= 1;

            if ( GLFW::ShouldRun( this->GetHandle( ) ) )
                this->windows[ idx ]->OnEditorRender( this );
            else {
                delete this->windows[ idx ];

                this->windows.erase( this->windows.begin( ) + idx );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutImage* NutEditor::GetImage( nString alias ) const {
    if ( nHelper::GetIsValid( alias ) ) {
        auto hash = nHelper::Hash_MD5( alias );

        auto size = this->images.size( );

        while ( size-- > 0 ) {
            if ( this->images[ size ].GetHash( ) != hash )
                continue;
            else
                return &this->images[ size ];
        }
    }

    return nullptr;
}

NutKernel* NutEditor::GetKernel( ) const { return (NutKernel*)this->modules[ 0 ]; }

NutLibrary* NutEditor::GetLibrary( nString name ) const {
    if ( nHelper::GetIsValid( name ) ) {
        auto hash = nHelper::Hash_MD5( name );

        for ( auto& library : this->libraries ) {
            if ( library->GetHash( ) != hash )
                continue;
            else
                return library;
        }
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE GET
///////////////////////////////////////////////////////////////////////////////////////////
std::vector< NutModule* >& NutEditor::GetModules( ) const { return this->modules; }
