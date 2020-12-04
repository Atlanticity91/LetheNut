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
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeEditor::NutNodeEditor( )
	: NutTool( "NodeEditor" ),
	nodes( ),
    links( )
{ }

NutNodeEditor::~NutNodeEditor( ) { 
    for ( auto& node : this->nodes )
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
    this->links.emplace_back( 
        NutNodeLink{
            { source_node, source_pin },
            { destination_node, destination_pin },
            color
        }
    );
}

void NutNodeEditor::CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin, const ImVec4&& color ) {
    this->CreateLink( source_node, source_pin, destination_node, destination_pin, color );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTETED
///////////////////////////////////////////////////////////////////////////////////////////
void NutNodeEditor::Process( class NutEditor* editor ) {
    if ( this->nodes.size( ) < 1 ) {
        auto* n = new NutNode( ENutNodeTypes::ENT_FUNCTION, "Test", "I'm a test node." );
        n->AddIn( false, ENutPinTypes::EPT_BOOL, "Test", "Test pin" );
        n->AddIn( false, ENutPinTypes::EPT_INT32, "Test i", "Test pin" );
        n->AddIn( false, ENutPinTypes::EPT_FLOAT64, "Test f", "Test pin" );
        n->AddIn( false, ENutPinTypes::EPT_STRING, "Test s", "Test pin" );
        n->AddOut( false, ENutPinTypes::EPT_BOOL, "Test b", "Test pin" );
        this->nodes.emplace_back( n );
    }
}

void NutNodeEditor::OnEditorRender( NutEditor* editor ) {
    auto alpha = ImGui::GetStyle( ).Alpha;

	for ( auto& node : this->nodes ) {
        ImGUI::Spring( );
        ImGui::TextUnformatted( node->GetName( ) );
        ImGUI::Spring( 1 );
        ImGUI::Spacer( 0.f, 28.f );
        ImGUI::Spring( );
        
        ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
        for ( auto& input : node->GetInPins( ) ) {
            this->InternalDrawPin( input, false, alpha );
        }
        
        for ( auto& output : node->GetOutPins( ) ) {
            this->InternalDrawPin( output, true, alpha );
        }

        ImGui::PopStyleVar( );
	}

    for ( auto& link : this->links ) 
        this->InternalDrawLink( link );
}

void NutNodeEditor::InternalDrawPin( const NutNodePin& pin, bool is_out, float alpha ) {
    if ( !is_out ) {
        this->InternalDrawPin( pin, alpha );
        ImGUI::Spring( );
    }

    if ( pin.type == ENutPinTypes::EPT_STRING && pin.string.value && pin.string.length > 0 ) {
        static bool wasActive = false;

        ImGui::PushItemWidth( 100.0f );
        ImGui::InputText( "##edit", pin.string.value, pin.string.length );
        ImGui::PopItemWidth( );

        if ( ImGui::IsItemActive( ) && !wasActive ) 
            wasActive = true;
        else if ( !ImGui::IsItemActive( ) && wasActive ) 
            wasActive = false;

        ImGUI::Spring( );
    }

    ImGUI::Spring( );

    if ( strcmp( pin.name, "" ) != 0 ) {
        ImGui::TextUnformatted( pin.name );
        ImGUI::Spring( );
    }

    if ( is_out ) {
        ImGUI::Spring( );
        this->InternalDrawPin( pin, alpha );
    }
}

void NutNodeEditor::InternalDrawPin( const NutNodePin& pin, float alpha ) {
    ImColor color;

    switch ( pin.type ) {
        case ENutPinTypes::EPT_STRING  : color = ImColor( 124,  21, 153 ); break;
        case ENutPinTypes::EPT_BOOL    : color = ImColor( 220,  48,  48 ); break;
        case ENutPinTypes::EPT_INT8    : color = ImColor(  68, 201, 156 ); break;
        case ENutPinTypes::EPT_INT16   : color = ImColor(  68, 201, 156 ); break;
        case ENutPinTypes::EPT_INT32   : color = ImColor(  68, 201, 156 ); break;
        case ENutPinTypes::EPT_INT64   : color = ImColor(  68, 201, 156 ); break;
        case ENutPinTypes::EPT_FLOAT32 : color = ImColor( 147, 226,  74 ); break;
        case ENutPinTypes::EPT_FLOAT64 : color = ImColor( 147, 226,  74 ); break;

        default : color = ImColor( 255, 255, 255 ); break;
    }
    
    if ( !pin.is_array )
        ImGUI::CircleIcon( 24.f, pin.is_connected, ImColor( color ), ImColor( 32, 32, 32, (int)alpha * 255 ) );
    else
        ImGUI::GridIcon( 24.f, pin.is_connected, ImColor( color ), ImColor( 32, 32, 32, (int)alpha * 255 ) );
}

void NutNodeEditor::InternalDrawLink( const NutNodeLink& link ) {
    ImVec2 source = ImVec2{ };
    ImVec2 destination = ImVec2{ };

    ImGUI::Link( source, destination, link.color, 2.f );
}
