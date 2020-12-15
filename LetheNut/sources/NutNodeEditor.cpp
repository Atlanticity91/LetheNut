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

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
const ImColor Internal_PinColor( ENutPinTypes type ) {
    switch ( type ) {
        case ENutPinTypes::EPT_FLOW     : return ImColor( 208, 208, 208 );
        case ENutPinTypes::EPT_STRING   : return ImColor( 124,  21, 153 );
        case ENutPinTypes::EPT_BOOL     : return ImColor( 220,  48,  48 );
        case ENutPinTypes::EPT_INT8     : return ImColor(  68, 201, 156 );
        case ENutPinTypes::EPT_INT16    : return ImColor(  68, 201, 156 );
        case ENutPinTypes::EPT_INT32    : return ImColor(  68, 201, 156 );
        case ENutPinTypes::EPT_INT64    : return ImColor(  68, 201, 156 );
        case ENutPinTypes::EPT_FLOAT32  : return ImColor( 147, 226,  74 );
        case ENutPinTypes::EPT_FLOAT64  : return ImColor( 147, 226,  74 );

        default : break;
    }

    return ImColor( 255, 255, 255 );
}

const ImColor Internal_NodeColor( ENutNodeTypes type ) {
    switch ( type ) {
        case ENutNodeTypes::ENT_BRANCH   : return ImColor( 220,  48,  48 );
        case ENutNodeTypes::ENT_CONSTANT : return ImColor(  68, 201, 156 );
        case ENutNodeTypes::ENT_EVENT    : return ImColor( 220,  48,  48 );
        case ENutNodeTypes::ENT_FUNCTION : return ImColor(  22,  38,  38 );
        case ENutNodeTypes::ENT_SWITCH   : return ImColor( 124,  21, 153 );
        case ENutNodeTypes::ENT_VARIABLE : return ImColor(  22,  38,  38 );

        default : break;
    }

    return ImColor( 22, 38, 38 );
}

class def_parser : public NutNodeParser {

public:
    def_parser( ) : NutNodeParser( "Test" ) { }

    ~def_parser( ) { }

    virtual void Initialize( ) override {
        auto* model = this->Create( ENutNodeTypes::ENT_EVENT, "Base Event", "Main event test" );
        model->AddOut( false, ENutPinTypes::EPT_BOOL, "Is Active", "" );

        model = this->Create( ENutNodeTypes::ENT_FUNCTION, "Base Function", "Function test" );
        model->AddIn( false, ENutPinTypes::EPT_FLOW, "", "" );
        model->AddIn( false, ENutPinTypes::EPT_BOOL, "Boolean", "Test pin" );
        model->AddIn( true, ENutPinTypes::EPT_INT32, "Int32", "Test pin" );
        model->AddIn( false, ENutPinTypes::EPT_FLOAT64, "Float64", "Test pin" );
        model->AddIn( false, ENutPinTypes::EPT_STRING, "String", "Test pin" );
        model->AddOut( false, ENutPinTypes::EPT_FLOW, "", "" );
        model->AddOut( false, ENutPinTypes::EPT_BOOL, "Is Active", "" );
    }

};

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeEditor::NutNodeEditor( )
	: NutTool( "NodeEditor" ),
    canvas( .3f, 3.f ),
	nodes( ),
    links( )
{ 
    this->SetParser<def_parser>( );
}

NutNodeEditor::~NutNodeEditor( ) { 
    for ( auto node : this->nodes )
        delete node;
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

        auto* model = this->parser->GetModel( 1 );
        if ( model ) {
            auto* n = new NutNode( pos, *model );
            this->nodes.emplace_back( n );

            
            if ( this->nodes.size( ) > 1 ) {
                for ( int i = 0; i < this->nodes[ this->nodes.size( ) - 2 ]->GetOutPins( ).size( ); i++ ) {
                    auto lnk = NutNodeLink( );
                    auto size = (nUInt)this->nodes.size( );

                    lnk.source.node_id = size - 2;
                    lnk.source.pin_id = i;
                    lnk.destination.node_id = size - 1;
                    lnk.destination.pin_id = i;

                    this->nodes[ lnk.destination.node_id ]->ConnectIn( i );
                    this->nodes[ lnk.source.node_id ]->ConnectOut( i );

                    this->links.emplace_back( lnk );
                }
            }
        }
    }
}

void NutNodeEditor::OnEditorRender( NutEditor* editor ) {
    ImGUI::BeginCanvas( this->canvas );

    for ( auto& node : this->nodes )
        this->InternalDraw( node, false );

    for ( auto& link : this->links )
        this->InternalDraw( link );

    ImGUI::EndCanvas( );
}

void NutNodeEditor::InternalDraw( const NutNode* node, bool is_selected ) {
    ImGUI::BeginNode( this->canvas, node->GetName( ), node->GetPosition( ) );

        this->InternalDraw( node->GetInPins( ), false );
        ImGui::SameLine( ImGui::GetItemRectSize( ).x + ImGUI::GetTextSize( "####" ).x );
        this->InternalDraw( node->GetOutPins( ), true );

    ImGUI::EndNode( this->canvas, node->GetName( ), node->GetPosition( ), Internal_NodeColor( node->GetType( ) ), true );
}

void NutNodeEditor::InternalDraw( const NutNode::PinList& pins, bool is_out ) {
    ImGui::BeginGroup( );

    for ( auto& pin : pins ) 
        this->InternalDraw( pin, is_out );

    ImGui::EndGroup( );
}

void NutNodeEditor::InternalDraw( const NutNodePin& pin, bool is_out ) {
    auto cursor = ImGui::GetCursorScreenPos( );
    auto color = Internal_PinColor( pin.type );

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

    ImGUI::Text( color, pin.name );

    if ( is_out ) {
        ImGui::SetCursorScreenPos( ImVec2{ cursor.x + ImGUI::GetTextSize( pin.name ).x, cursor.y } );
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
//      PROTETED GET 
///////////////////////////////////////////////////////////////////////////////////////////
const ImVec2 NutNodeEditor::GetPinPosition( bool is_output, nUInt node_id, nUInt pin_id ) const {
    auto node_offset = ImVec2{ 
        (!is_output ) ? 7.f : 13.f + ImGui::GetItemRectSize( ).x,
        ( ImGUI::NODE_PIN_SIZE - 4.f ) * pin_id + ImGUI::GetTextSize( "#" ).y + ImGui::GetTextLineHeightWithSpacing( )
    };
    auto node_position = this->nodes[ node_id ]->GetPosition( ) + node_offset;

    return ImGui::GetWindowPos( ) + node_position * canvas.zoom + canvas.offset;
}

const ImColor NutNodeEditor::GetPinColor( nUInt node_id, nUInt pin_id ) const {
    return Internal_PinColor( this->nodes[ node_id ]->GetInPin( pin_id ).type );
}
