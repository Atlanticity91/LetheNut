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

#include <LetheNut/Framework/Editors/Text/NutTextEditor.hpp>
#include <LetheNut/Framework/Editors/Text/NutTextScheme.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutTextEditor::NutTextEditor( )
	: NutPanel( "Text Editor" ),
	document_id( 0 ),
	parser( nullptr ),
	style( nullptr ),
	documents( ),
	styles( )
{ }

void NutTextEditor::SetStyle( nString name ) {
	auto* new_style = this->styles[ name ];

	if ( new_style )
		this->style = *new_style;
}

void NutTextEditor::SetStyle( const std::string& name ) {
	this->SetStyle( name.c_str( ) );
}

void NutTextEditor::Create( const std::string& name ) {
	if ( !this->documents[ name ] ) {
		this->documents.Append( name, "" );

		this->document_id = this->documents.GetSize( ) - 1;
	}
}

void NutTextEditor::Open( NutEditor* editor, const std::string& path ) {
	if ( !path.empty( ) ) {
		// TODO : NutTextEditor::Open
	}
}

void NutTextEditor::Save( NutEditor* editor, NutTextDocument* document ) {
	if ( document )
		this->Save( editor, *document );
}

void NutTextEditor::Save( NutEditor* editor, NutTextDocument& document ) {
	if ( !document.GetIsSaved( ) ) {
		// TODO : NutTextEditor::Save
	}
}

void NutTextEditor::Close( NutEditor* editor, const std::string& name ) {
	auto* document = this->documents[ name ];

	if ( document && document->GetIsOpen( ) )
		*document->GetState( ) = false;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextEditor::OnCreateMenus( ) { }

void NutTextEditor::OnCreateModals( ) {
	auto* save = this->CreateModal( "Save ?" );

	if ( save ) {
		save->SetContent(
			[ ]( NutEditor*, NutWindow*, NutPanel* parent ) {
				auto* text_editor = NUT_CAST( parent, NutTextEditor );

				ImGui::Text( "Save change to the following document ?" );
				ImGui::Separator( );

				if ( text_editor->GetCurrent( ) )
					ImGui::BulletText( text_editor->GetCurrent( )->GetName( ).c_str( ) );

				ImGui::Separator( );
			}
		);

		save->Create(
			"Yes", false,
			[ ]( NutEditor* editor, NutWindow*, NutPanel* parent ) {
				auto* text_editor = NUT_CAST( parent, NutTextEditor );

				text_editor->Save( editor, text_editor->GetCurrent( ) );

				return true;
			}
		);
		save->Create(
			"No", false,
			[ ]( NutEditor*, NutWindow*, NutPanel* ) { return true; }
		);
		save->Create(
			"Cancel", true,
			[ ]( NutEditor* editor, NutWindow*, NutPanel* parent ) {
				*NUT_CAST( parent, NutTextEditor )->GetCurrent( )->GetState( ) = true;

				return true;
			}
		);
	}

	auto* save_all = this->CreateModal( "Save all ?" );

	if ( save_all ) {
		save_all->SetContent(
			[ ]( NutEditor*, NutWindow*, NutPanel* parent ) {
				auto* text_editor = NUT_CAST( parent, NutTextEditor );

				ImGui::Text( "Save change of the following documents ?" );
				ImGui::Separator( );

				text_editor->GetDocuments( ).Foreach(
					[ ]( auto& document ) {
						if ( !document.GetIsSaved( ) )
							ImGui::BulletText( document.GetName( ).c_str( ) );
					}
				);
				ImGui::Separator( );
			}
		);
		save_all->Create(
			"Yes", false,
			[ ]( NutEditor* editor, NutWindow*, NutPanel* parent ) {
				auto* text_editor = NUT_CAST( parent, NutTextEditor );

				text_editor->GetDocuments( ).Foreach(
					[ & ]( auto& document ) { text_editor->Save( editor, document ); }
				);

				return true;
			}
		);
		save_all->Create(
			"No", false,
			[ ]( NutEditor*, NutWindow*, NutPanel* ) { return true; }
		);
		save_all->Create(
			"Cancel", true,
			[ ]( NutEditor* editor, NutWindow*, NutPanel* parent ) {
				parent->Reset( );

				return true;
			}
		);
	}
}

void NutTextEditor::OnCreate( NutEditor* editor, NutWindow* parent ) { 
	for ( int i = 0; i < 3; i++ ) {
		std::string n = "Test " + std::to_string( i );
		this->Create( n );
	}
}

bool NutTextEditor::OnDestroy( NutEditor* editor, NutWindow* parent ) { 
	auto no_save = true;

	this->documents.Foreach( 
		no_save,
		[ ]( bool& condition, auto& document ) {
			if ( condition && !document.GetIsSaved( ) )
				condition = false;
		}
	);

	return ( no_save ) ? true : this->OnRenderModal( editor, nullptr, this, "Save all ?" );
}

void NutTextEditor::OnProcess( NutEditor* editor, NutWindow* parent ) { }

void NutTextEditor::OnRender( NutEditor* editor, NutWindow* parent ) {
	if ( this->documents ) {
		if ( ImGui::BeginTabBar( "##TextEditorTabs", ImGuiTabBarFlags_Reorderable ) ) {
			this->documents.Foreach(
				[ this ]( auto& document, NutEditor* editor, NutWindow* window ) {
					if ( ImGUI::Tab( document ) ) {
						this->OnKeyPressed( );
						this->OnMousePressed( );
						this->OnRender( document );

						ImGui::EndTabItem( );
					}

					if ( !document.GetIsOpen( ) ) {
						if ( document.GetIsSaved( ) || this->OnRenderModal( editor, nullptr, this, "Save ?" ) ) {
							if ( !document.GetIsOpen( ) )
								this->documents.Erase( document.GetName( ) );
						}
					}
				}, 
				editor, parent
			);
		}

		ImGui::EndTabBar( );
	}
}

void NutTextEditor::OnKeyPressed( ) { }

void NutTextEditor::OnMousePressed( ) { }

void NutTextEditor::OnRender( NutTextDocument& document ) {
	if ( !this->style )
		this->SetStyle<NutTextScheme>( );

	ImGui::PushStyleColor( ImGuiCol_Text, this->style->GetText( ) );
	ImGui::PushStyleColor( ImGuiCol_WindowBg, this->style->GetBackground( ) );
	
	if ( !this->parser ) {
		for ( auto& line : this->GetCurrent( )->GetLines( ) )
			ImGui::Text( line.c_str( ) );
	} else {
		NutTextParser::TextPair pair;

		while ( this->parser->Parse( this->GetCurrent( )->GetLines( ), pair ) ) {
			auto& scheme = this->style->GetVar( pair.second );

			ImGUI::Text( scheme.foreground, scheme.background, pair.first );
		}
	}
	
	ImGui::PopStyleColor( 2 );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutList<NutTextStyle*>& NutTextEditor::GetStyles( ) const { return this->styles; }

NutTextStyle* NutTextEditor::GetStyle( ) const { return this->style; }

NutList<NutTextDocument>& NutTextEditor::GetDocuments( ) const { return this->documents; }

NutTextDocument* NutTextEditor::GetDocument( const std::string& name ) const {
	return this->documents.Get( name );
}

NutTextDocument* NutTextEditor::GetCurrent( ) const { 
	return this->documents.At( this->document_id ); 
}
