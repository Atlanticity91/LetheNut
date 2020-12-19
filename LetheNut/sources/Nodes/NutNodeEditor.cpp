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

#include <LetheNut/Editors/Nodes/NutNodeEditor.hpp>
#include <LetheNut/Vendor/ImGUI.hpp>
#include <LetheNut/Framework/Nodes/NutGLSL.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeEditor::NutNodeEditor( )
	: NutTool( "NodeEditor" ),
    canvas( .3f, 3.f ),
	nodes( ),
    links( )
{ 
    this->SetStyle<NutNodeStyle>( );
    this->SetParser<NutGLSL>( );
}

NutNodeEditor::~NutNodeEditor( ) { 
    if ( this->style )
        delete this->style;

    if ( this->parser )
        delete this->parser;

    for ( auto node : this->nodes )
        delete node;
}

void NutNodeEditor::CreateVar( ImVec2 position, ENutNodeTypes type, bool is_array, nString name ) {
    this->CreateVar( position, (nUInt)type, is_array, name );
}

void NutNodeEditor::CreateVar( ImVec2 position, nUInt type, bool is_array, nString name ) {
    if ( strlen( name ) > 0 ) {
        auto model = NutNodeModel( ENutNodeTypes::ENT_CONSTANT, name );
        model.AddIn( is_array, type );
        model.AddOut( is_array, type );

        auto* node = new NutNode( position, model );

        if ( node )
            this->nodes.emplace_back( node );
    }
}

void NutNodeEditor::CreateLink( const NutNodeLink& link ) { 
    this->links.emplace_back( link ); 
}

void NutNodeEditor::CreateLink( const NutNodeLink&& link ) { this->CreateLink( link ); }

void NutNodeEditor::CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin ) {
    this->CreateLink( source_node, source_pin, destination_node, destination_pin, ImColor{ 255, 255, 255 } );
}

void NutNodeEditor::CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin, const ImVec4& color ) {
    auto link = NutNodeLink{
            { source_node, source_pin },
            { destination_node, destination_pin },
            color
    };

    this->CreateLink( link );
}

void NutNodeEditor::CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin, const ImVec4&& color ) {
    this->CreateLink( source_node, source_pin, destination_node, destination_pin, color );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTETED
///////////////////////////////////////////////////////////////////////////////////////////
void NutNodeEditor::OnEditorProcess( class NutEditor* editor ) {
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
                float prevZoom = this->canvas.zoom;

                this->canvas.zoom = ImClamp( this->canvas.zoom + ImGUI::GetScrollWheel( ) * this->canvas.zoom / 16.f, this->canvas.zoom_min, this->canvas.zoom_max );
                float zoomFactor = ( prevZoom - this->canvas.zoom ) / prevZoom;
                this->canvas.offset += ( mouseRel - this->canvas.offset ) * zoomFactor;
            }
        }
    }

    if ( ImGui::IsMouseClicked( ImGuiMouseButton_Right ) ) {
        auto pos = ImGUI::GetMouseRelPos( ) - this->canvas.offset;
        
        //auto idx = /*rand( ) %*/ this->parser->GetModelCount( ) - 1;
        auto idx = rand( ) % this->parser->GetModelCount( );
        auto* model = this->parser->GetModel( idx );
        if ( model ) {
            auto* n = new NutNode( pos, *model );
            this->nodes.emplace_back( n );
        }
    }
}

void NutNodeEditor::OnEditorRender( NutEditor* editor ) {
    ImGUI::BeginCanvas( this->canvas );

    if ( this->parser ) {
        for ( auto& node : this->nodes )
            this->InternalDraw( node, false );

        for ( auto& link : this->links )
            this->InternalDraw( link );
    }

    ImGUI::EndCanvas( );
}

void NutNodeEditor::InternalDraw( const NutNode* node, bool is_selected ) {
    ImGUI::BeginNode( this->canvas, node->GetContext( ) );

        this->InternalDraw( node->GetInPins( ), false, 0.f );
        ImGui::SameLine( ImGui::GetItemRectSize( ).x + ImGUI::GetTextSize( "#####" ).x );
        this->InternalDraw( node->GetOutPins( ), true, node->GetOutLength( ) );

    ImGUI::EndNode( this->canvas, node->GetContext( ), this->style->GetNode( node->GetType( ) ) );
}

void NutNodeEditor::InternalDraw( const NutNode::PinList& pins, bool is_out, const float out_length ) {
    ImGui::BeginGroup( );

    for ( auto& pin : pins ) 
        this->InternalDraw( pin, is_out, out_length );

    ImGui::EndGroup( );
}

void NutNodeEditor::InternalDraw( const NutNodePin& pin, bool is_out, const float out_length ) {
    auto cursor = ImGui::GetCursorScreenPos( );
    auto color = this->style->GetNode( pin.type );

    if ( !is_out ) {
        this->InternalDraw( pin, color );

        if ( pin.type == ENutPinTypes::EPT_STRING ) {
            ImGui::SetCursorScreenPos( ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + 5.f + ImGUI::NODE_PIN_SIZE } );
            ImGui::PushItemWidth( 100.0f );
            ImGui::InputText( "##edit", pin.data.string.value, pin.data.string.length );
        }

        ImGui::SetCursorScreenPos( ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + 5.f } );

    } else 
        ImGui::SetCursorScreenPos( ImVec2{ cursor.x, cursor.y + 5.f } );

    ImGui::Text( pin.name );

    if ( is_out ) {
        ImGui::SetCursorScreenPos( ImVec2{ cursor.x + out_length, cursor.y } );
        this->InternalDraw( pin, color );
    }

    cursor.y += ImGUI::NODE_PIN_SIZE - 4.f;
    ImGui::SetCursorScreenPos( cursor );
}

void NutNodeEditor::InternalDraw( const NutNodePin& pin, ImColor color ) {
    if ( pin.type != ENutPinTypes::EPT_FLOW ) {
        if ( !pin.is_array )
            ImGUI::NodeCirclePin( pin.is_connected, color );
        else
            ImGUI::NodeArrayPin( pin.is_connected, color );
    } else
        ImGUI::NodeTrianglePin( pin.is_connected, color );
}

void NutNodeEditor::InternalDraw( const NutNodeLink& link ) {
    auto source = this->GetPinPosition( true, link.source.node_id, link.source.pin_id );
    auto destination = this->GetPinPosition( false, link.destination.node_id, link.destination.pin_id );
    auto color = this->GetPinColor( link.source.node_id, link.source.pin_id );

    ImGUI::NodeLink( this->canvas, source, destination, color );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET 
///////////////////////////////////////////////////////////////////////////////////////////
const NutNodeStyle* NutNodeEditor::GetStyle( ) const { return this->style; }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTETED GET 
///////////////////////////////////////////////////////////////////////////////////////////
const ImVec2 NutNodeEditor::GetPinPosition( bool is_output, nUInt node_id, nUInt pin_id ) const {
    auto node_offset = ImVec2{ 
        ( !is_output ) ? 8.f : 16.f + ImGui::GetItemRectSize( ).x,
        ( ImGUI::NODE_PIN_SIZE - 4.f ) * pin_id + ImGUI::GetTextSize( "#" ).y + ImGui::GetTextLineHeightWithSpacing( )
    };
    auto node_position = this->nodes[ node_id ]->GetPosition( ) + node_offset;

    return ImGui::GetWindowPos( ) + node_position * canvas.zoom + canvas.offset;
}

const ImColor NutNodeEditor::GetPinColor( nUInt node_id, nUInt pin_id ) const {
    return this->style->GetNode( this->nodes[ node_id ]->GetInPin( pin_id ).type );
}
