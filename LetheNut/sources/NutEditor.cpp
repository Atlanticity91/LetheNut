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

#include <LetheNut/NutEditor.hpp>
#include <LetheNut/Vendor/OpenGL.hpp>
#include <LetheNut/Vendor/GLFW.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutEditor::NutEditor( )
	: is_running( true ),
	logger( ),
	file_system( ),
	assets( ),
	style( nullptr ),
	libraries( ),
	modules( )
{ }

NutEditor::~NutEditor( ) { 
	if ( this->style )
		this->style.reset( );

	this->modules.Foreach( 
		[ this ]( auto& module ) {
			auto* importer = module->GetImporter( );;

			module->OnDestroy( this );
			delete module;
			module = nullptr;

			delete importer;
		}
	);

	this->Log( NutLoggerModes::NLM_INFO, "NutEditor Stop !" );
}

bool NutEditor::LoadLibrary( nString path ) {
	if ( nHelper::GetIsValid( path ) ) {
		auto* library = new NutLibrary( path );

		if ( library->GetIsValid( ) ) {
			this->libraries.Emplace( library );

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
		typedef void ( *NutLoadModule )( NutEditor*, NutPlatformLib* );

		auto* module_lib = new NutPlatformLib( path );

		if ( module_lib && module_lib->GetIsValid( ) ) {
			NutLoadModule module_load = (*module_lib)[ "RegisterModule" ];

			if ( module_load ) {
				module_load( this, module_lib );

				this->Log( NutLoggerModes::NLM_INFO, "Loaded module : %s", path );

				return true;
			} else {
				this->Log( NutLoggerModes::NLM_ERRR, "Unable to open the module : %s", path );
				
				delete module_lib;
			}
		} else
			this->Log( NutLoggerModes::NLM_ERRR, "Unable to load module at %s", path );
	}

	return false;
}

bool NutEditor::LoadModule( const std::string& path ) {
	return this->LoadModule( path.c_str( ) );
}

void NutEditor::UnLoadLibrary( nString name ) {
	this->libraries.Erase( name );
}

void NutEditor::UnLoadLibrary( const std::string& name ) {
	this->UnLoadLibrary( name.c_str( ) );
}

void NutEditor::UnLoadModule( nString name ) {
	auto* module = this->modules[ name ];
	
	if ( module ) {
		(*module)->OnDestroy( this );

		this->modules.Erase( name );
	}
}

void NutEditor::UnLoadModule( const std::string& name ) {
	this->UnLoadModule( name.c_str( ) );
}

void NutEditor::Close( nString name ) { 
	auto* window = this->windows[ name ];

	if ( window ) {
		(*window)->OnDestroy( this );

		this->windows.Erase( name );
	}
}

void NutEditor::Close( const std::string& name ) {
	this->Close( name.c_str( ) );
}

void NutEditor::Exit( ) { this->is_running = false; }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutEditor::LoadDependencies( ) {
	auto& nut_json = this->assets.GetJSON( "Config" )->Get( );
	nlohmann::json json = nut_json;
	for ( auto images : json[ "Images" ] ) 
		this->assets.LoadImageAs( this, images[ 0 ], images[ 1 ] );

	for ( auto path : nut_json.Get<JSON::StringArray>( "Libraries" ) ) {
		if ( !path.empty( ) ) 
			this->LoadLibrary( path ) ;
	}
	
	for ( auto path : nut_json.Get<JSON::StringArray>( "Modules" ) ) {
		if ( !path.empty( ) )
			this->LoadModule( path );
	}
}

bool NutEditor::Start( int argc, char** argv ) {
	this->Log( NutLoggerModes::NLM_INFO, "NutEditor Start !" );

	if ( this->assets.Initialize( ) ) {
		if ( this->assets.LoadJSONAs( this, "Config", "Assets/NutEditor.json" ) && OpenGL::Initialize( this ) ) {
			this->Log( NutLoggerModes::NLM_WARN, this->GetVersion( ) );
			this->Log( NutLoggerModes::NLM_WARN, this->GetLicense( ) );

			return true;
		} else
			this->Log( NutLoggerModes::NLM_ERRR, "Can't load configuration file : NutEditor.json !" );
	} else
		this->Log( NutLoggerModes::NLM_ERRR, "Can't initialize GLFW !" );

	return false;
}

void NutEditor::Run( ) {
	this->LoadDependencies( );

	while ( this->is_running && this->windows ) {
		this->modules.Foreach(
			[ this ]( auto& module ) {
				if ( module->GetState( ) )
					module->Process( this );
			}
		);

		if ( this->style && this->style->GetHasChanged( ) )
			ImGUI::SetStyle( this->style.get( ) );

		this->windows.Foreach(
			[ this ]( auto& window ) {
				if ( window->ShouldRun( ) )
					window->OnRender( this );
				else if ( window->OnDestroy( this ) )
					this->windows.Erase( window->GetName( ) );
			}
		);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const std::string NutEditor::GetVersion( ) const { 
	return this->assets.GetJSON( "Config" )->Get( ).Get<std::string>( "Version" );
}

const std::string NutEditor::GetLicense( ) const { 
	return this->assets.GetJSON( "Config" )->Get( ).Get<std::string>( "License" );
}

NutFileSystem* NutEditor::GetFileSystem( ) const { return &this->file_system; }

NutAssetManager* NutEditor::GetAssetManager( ) const { return &this->assets; }

NutMono* NutEditor::GetMono( ) const { return &this->mono; }

NutStyle* NutEditor::GetStyle( ) const { return this->style.get( ); }

NutLibrary* NutEditor::GetLibrary( nString name ) const { 
	return *this->libraries[ name ]; 
}

NutModule* NutEditor::GetModule( nString name ) const { return *this->modules[ name ]; }

NutWindow* NutEditor::GetWindow( nString name ) const { return *this->windows[ name ]; }
