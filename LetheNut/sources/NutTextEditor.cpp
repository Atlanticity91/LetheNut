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

#include <LetheNut/Editors/Text/NutTextEditor.hpp>

#define FLAGS ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NoMove

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC 
///////////////////////////////////////////////////////////////////////////////////////////
NutTextEditor::NutTextEditor( )
	: NutTool( "TextEditor" ),
	document_id( 0 ),
	renderer( ),
	documents( )
{ 
	this->style = new NutTextStyle( "Default" );
	this->parser = new NutTextParser( "Default" );

	this->renderer.Record = nHelper::GetTime( );

	this->Create( "I'm a test" );
	this->Get( ).Append( "I'm a symbolic test !", 10 );
}

NutTextEditor::~NutTextEditor( ) {
	if ( this->style )
		delete this->style;

	if ( this->parser )
		delete this->parser;
}

void NutTextEditor::Create( const std::string& name ) {
	if ( !name.empty( ) ) {
		for ( auto& doc : this->documents ) {
			if ( doc.GetName( ) != name )
				continue;

			return;
		}

		auto document = NutTextDocument( name );
		
		this->renderer.Cursor = document;
		this->documents.emplace_back( document );
	}
}

void NutTextEditor::Prev( ) {
	if ( this->documents.size( ) > 1 ) {
		this->Get( ).SetCursor( this->renderer.Cursor );

		if ( this->document_id > 0 )
			this->document_id -= 1;
		else
			this->document_id = (nUInt)this->documents.size( ) - 1;

		this->renderer.Cursor = this->Get( );
	}
}

void NutTextEditor::Next( ) {
	if ( this->documents.size( ) > 1 ) {
		this->Get( ).SetCursor( this->renderer.Cursor );

		if ( this->document_id < this->documents.size( ) )
			this->document_id += 1;
		else
			this->document_id = 0;

		this->renderer.Cursor = this->Get( );
	}
}

void NutTextEditor::MoveUp( ) {
	if ( this->renderer.Cursor.line > 0 ) {
		this->renderer.Cursor.line -= 1;

		this->Replace( );
	}
}

void NutTextEditor::MoveDown( ) {
	if ( this->renderer.Cursor.line < this->Get( ) ) {
		this->renderer.Cursor.line += 1;

		this->Replace( );
	}
}

void NutTextEditor::MoveLeft( ) {
	if ( this->renderer.Cursor.position > 0 )
		this->renderer.Cursor.position -= 1;
}

void NutTextEditor::MoveRight( ) {
	auto max = this->Get( ).GetLineSize( this->renderer.Cursor.line );

	if ( this->renderer.Cursor.position < max )
		this->renderer.Cursor.position += 1;
}

void NutTextEditor::MoveTop( ) { 
	this->renderer.Cursor.line = 0; 
	this->renderer.Cursor.position = this->Get( ).GetLineSize( 0 ) - 1;
}

void NutTextEditor::MoveBottom( ) { 
	this->renderer.Cursor.line = this->Get( ) - 1; 
	this->renderer.Cursor.position = this->Get( ).GetLineSize( this->Get( ) - 1 ) - 1;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED 
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextEditor::OnEditorProcess( class NutEditor* editor ) {
	this->InternalInputKeyboard( );
	this->InternalInputMouse( );
}

void NutTextEditor::InternalInputKeyboard( ) {
	if ( !ImGUI::GetIsCtrltDown( ) && !ImGUI::GetIsAltDown( ) && !ImGUI::GetIsShiftDown( ) ) {
		if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_UpArrow ) ) )
			this->MoveUp( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_DownArrow ) ) )
			this->MoveDown( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_LeftArrow ) ) )
			this->MoveLeft( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_RightArrow ) ) )
			this->MoveRight( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_Enter ) ) )
			this->Get( ).Insert( '\n', this->renderer.Cursor );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_Tab ) ) )
			this->Get( ).Insert( '\t', this->renderer.Cursor );
		else {
			ImGUI::DequeueCharacters(
				[ & ]( char character ) {
					this->Get( ).Insert( character, this->renderer.Cursor );
				}
			);
		}
	} else if ( ImGUI::GetIsAltDown( ) ) {
		if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_UpArrow ) ) )
			this->MoveTop( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_DownArrow ) ) )
			this->MoveBottom( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_LeftArrow ) ) )
			this->Prev( );
		else if ( ImGui::IsKeyPressed( ImGui::GetKeyIndex( ImGuiKey_RightArrow ) ) )
			this->Next( );
	}
}

void NutTextEditor::InternalInputMouse( ) {
	if ( ImGui::IsMouseClicked( ImGuiMouseButton_::ImGuiMouseButton_Left ) ) {
	}
}

void NutTextEditor::OnEditorRender( class NutEditor* editor ) {
	ImGui::PushStyleColor( ImGuiCol_ChildBg, this->style->GetBackground( ).Value );

	if ( this->documents.size( ) > 0 ) {
		ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImGUI::NO_PADDING );

		this->InternalPrepare( );

		auto document = this->Get( );
		auto line_id = 0;

		ImGui::BeginChild( (nString)document, ImVec2( ), false, FLAGS );
			
			auto renderer = ImGui::GetWindowDrawList( );
			auto cursor = ImGui::GetCursorScreenPos( );

			this->InternalDraw( renderer, cursor );

			if ( document > 0 ) {
				for ( auto line : document.GetLines( ) ) {
					this->InternalDraw( renderer, cursor, line_id++ );

					if ( !line.empty( ) )
						this->InternalDraw( renderer, cursor, line );

					ImGui::NewLine( );

					cursor = ImGui::GetCursorScreenPos( );
				}
			} else 
				this->InternalDraw( renderer, cursor, line_id );

		ImGui::EndChild( );

		ImGui::PopStyleVar( );
	}

	ImGui::PopStyleColor( );
}

void NutTextEditor::InternalPrepare( ) {
	snprintf( this->renderer.LineNumbers, 16, " %d ", (nUInt)this->Get( ) );

	this->renderer.LeftPadding = ImGUI::GetTextSize( this->renderer.LineNumbers ).x + .5f;
	this->renderer.Region = ImGui::GetWindowContentRegionMax( );
	this->renderer.FontSize = ImGUI::GetTextSize( "#" );
	this->renderer.CharAdvance = ImVec2{ 
		this->renderer.FontSize.x, 
		ImGui::GetTextLineHeightWithSpacing( ) * this->style->GetLineSpacing( ) 
	};
	this->renderer.SpaceAdvance = ImGUI::GetTextSize( " " );
}

void NutTextEditor::InternalDraw( ImDrawList* renderer, ImVec2 position ) {
	auto style = this->style->Get( ENutTextStyleVars::ETSV_LINE );

	auto line_srt = ImVec2{ position.x, position.y + this->renderer.Cursor.line * this->renderer.CharAdvance.y };
	auto line_stp = ImVec2{ line_srt.x + this->renderer.Region.x, line_srt.y + this->renderer.CharAdvance.y };

	auto cursor_srt = ImVec2{
		position.x + this->renderer.LeftPadding + this->renderer.Cursor.position * this->renderer.CharAdvance.x,
		position.y + this->renderer.Cursor.line * this->renderer.CharAdvance.y
	};
	auto cursor_stp = ImVec2{ cursor_srt.x + 1.f, cursor_srt.y + this->renderer.CharAdvance.y };

	if ( style.background != this->style->GetBackground( ) )
		renderer->AddRectFilled( line_srt, line_stp, style.background );

	renderer->AddRect( line_srt, line_stp, style.foreground, 0.f, 15, 1.25f );

	nHelper::Blink(
		this->renderer.Record, 400, 
		[ & ]( ) { renderer->AddRectFilled( cursor_srt, cursor_stp, ImColor{ 255, 255, 255, 204 } ); }
	);
}

void NutTextEditor::InternalDraw( ImDrawList* renderer, ImVec2 position, ENutTextStyleVars query_var, nString text ) {
	auto style = this->style->Get( query_var );

	if ( style.background != this->style->GetBackground( ) )
		ImGUI::Text( renderer, position, text, style.background, style.foreground );
	else
		renderer->AddText( position, style.foreground, text );
}

void NutTextEditor::InternalDraw( ImDrawList* renderer, ImVec2 position, nUInt line_id ) {
	snprintf( this->renderer.LineNumbers, 16, " %d ", line_id + 1 );

	auto lineNoWidth = ImGUI::GetTextSize( this->renderer.LineNumbers ).x;
	auto pos = ImVec2{ position.x + this->renderer.LeftPadding - lineNoWidth, position.y };
	
	this->InternalDraw( renderer, pos, ENutTextStyleVars::ETSV_LINECOUNT, this->renderer.LineNumbers );
}

void NutTextEditor::InternalDraw( ImDrawList* renderer, ImVec2 cursor, const std::string& text ) {
	cursor.x += this->renderer.LeftPadding;

	auto style = ENutTextStyleVars::ETSV_DEFAULT;
	auto string = text.c_str( );
	auto offset = cursor;

	this->parser->Parse( text );

	while ( this->parser->GetNext( style, string ) ) {
		this->InternalDraw( renderer, offset, style, string );

		offset.x += ImGUI::GetTextSize( string ).x + this->renderer.SpaceAdvance.x;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE 
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextEditor::Replace( ) {
	auto size = (nUInt)this->Get( )[ this->renderer.Cursor.line ].size( );

	if ( this->renderer.Cursor.position >= size )
		this->renderer.Cursor.position = ( size > 0 ) ? size - 1 : 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const NutTextStyle* NutTextEditor::GetStyle( ) const { return this->style; }

const NutTextParser* NutTextEditor::GetParser( ) const { return this->parser; }

bool NutTextEditor::Get( NutTextDocument& document, nUInt query_id ) const {
	if ( query_id < this->documents.size( ) ) {
		document = this->documents[ query_id ];

		return true;
	}

	return false;
}

bool NutTextEditor::Get( NutTextDocument& document, const std::string& query_name ) const {
	if ( this->documents.size( ) > 0 && !query_name.empty( ) ) {
		for ( auto& doc : this->documents ) {
			if ( doc.GetName( ) != query_name )
				continue;

			document = doc;

			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE GET
///////////////////////////////////////////////////////////////////////////////////////////
NutTextDocument& NutTextEditor::Get( ) const {  return this->documents[ this->document_id ];  }

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////
NutTextEditor& NutTextEditor::operator++( ) {
	this->Next( );

	return *this;
}

NutTextEditor& NutTextEditor::operator--( ) {
	this->Prev( );

	return *this;
}
