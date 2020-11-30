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
	nodes( )
{ }

NutNodeEditor::~NutNodeEditor( ) { }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTETED
///////////////////////////////////////////////////////////////////////////////////////////
void NutNodeEditor::OnEditorRender( NutEditor* editor ) {
    auto alpha = ImGui::GetStyle( ).Alpha;

    auto* n = new NutNode( ENutNodeTypes::ENT_FUNCTION, "", "" );
    this->nodes.emplace_back( n );

	for ( auto& node : this->nodes ) {
		//builder.Begin(node.ID);
			//builder.Header(node.Color);
                ImGUI::Spring( );
				ImGui::TextUnformatted( node->GetName( ) );
                ImGUI::Spring( 1 );
				ImGUI::Spacer( 0, 28 );
                ImGUI::Spring( );
			//builder.EndHeader();

			for ( auto& input : node->GetInPins( ) ) {
                /*
				if ( newLinkPin && !CanCreateLink( newLinkPin, &input ) && &input != newLinkPin )
                    alpha = alpha * ( 48.0f / 255.0f );
                */

                //builder.Input( input.ID );
                    ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
                    this->InternalDrawPinIcon( input.type, false, alpha );
                    //DrawPinIcon( input, IsPinLinked( input.ID ), (int)( alpha * 255 ) );
                    ImGUI::Spring( );
                    
                    if ( strcmp( input.name, "" ) != 0 ) {
                        ImGui::TextUnformatted( input.name );
                        ImGUI::Spring( );
                    }

                    ImGui::PopStyleVar( );
                //builder.EndInput( );
			}

			for ( auto& output : node->GetOutPins( ) ) {
                /*
                if ( newLinkPin && !CanCreateLink( newLinkPin, &output ) && &output != newLinkPin )
                    alpha = alpha * ( 48.0f / 255.0f );
                    */

                ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
                //builder.Output( output.ID );
                    if ( output.type == ENutPinTypes::EPT_STRING ) {
                        static char buffer[ 128 ] = "Edit Me\nMultiline!";
                        static bool wasActive = false;

                        ImGui::PushItemWidth( 100.0f );
                        ImGui::InputText( "##edit", buffer, 127 );
                        ImGui::PopItemWidth( );
                        
                        if ( ImGui::IsItemActive( ) && !wasActive ) {
                            //ed::EnableShortcuts( false );
                            wasActive = true;
                        } else if ( !ImGui::IsItemActive( ) && wasActive ) {
                            //ed::EnableShortcuts( true );
                            wasActive = false;
                        }
                        
                        ImGUI::Spring( );
                    }

                    if ( strcmp( output.name, "" ) != 0 ) {
                        ImGUI::Spring( );
                        ImGui::TextUnformatted( output.name );
                    }
                    
                    ImGUI::Spring( );
                    this->InternalDrawPinIcon( output.type, false, alpha );
                    //DrawPinIcon( output, IsPinLinked( output.ID ), (int)( alpha * 255 ) );
                    ImGui::PopStyleVar( );
                //builder.EndOutput( );
			}
        //builder.End();
	}

    delete this->nodes[ 0 ];
    this->nodes.erase( this->nodes.begin( ) );
}

void NutNodeEditor::InternalDrawPinIcon( ENutPinTypes type, bool connected, float alpha ) {
    /*
    IconType iconType;
    ImColor  color = GetIconColor( pin.Type );
    color.Value.w = alpha / 255.0f;
    switch ( pin.Type ) {
        case PinType::Flow:     iconType = IconType::Flow;   break;
        case PinType::Bool:     iconType = IconType::Circle; break;
        case PinType::Int:      iconType = IconType::Circle; break;
        case PinType::Float:    iconType = IconType::Circle; break;
        case PinType::String:   iconType = IconType::Circle; break;
        case PinType::Object:   iconType = IconType::Circle; break;
        case PinType::Function: iconType = IconType::Circle; break;
        case PinType::Delegate: iconType = IconType::Square; break;
        default:
            return;
    }

    ax::Widgets::Icon( ImVec2( s_PinIconSize, s_PinIconSize ), iconType, connected, color, ImColor( 32, 32, 32, alpha ) );
    */
    ImColor color;

    switch ( type ) {
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

    // ImGUI::Icon( 32.f, color, ImColor( 32, 32, 32, alpha ) );
}
