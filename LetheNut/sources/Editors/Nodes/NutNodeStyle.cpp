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

#include <LetheNut/Editors/Nodes/NutNodeStyle.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeStyle::NutNodeStyle( )
	: NutNodeStyle( "Default" )
{ }

NutNodeStyle::NutNodeStyle( nString name )
    : NutBasic( name ),
    node_colors( ),
    pin_colors( ) 
{ this->Validate( ); }

void NutNodeStyle::Validate( ) {
    this->RegisterNode( ENT_BRANCH,     ImColor{ 220,  48,  48 } );
    this->RegisterNode( ENT_CONSTANT,   ImColor{  68, 201, 156 } );
    this->RegisterNode( ENT_EVENT,      ImColor{ 220,  48,  48 } );
    this->RegisterNode( ENT_FUNCTION,   ImColor{  22,  38,  38 } );
    this->RegisterNode( ENT_SWITCH,     ImColor{ 124,  21, 153 } );
    this->RegisterNode( ENT_VARIABLE,   ImColor{  22,  38,  38 } );
    this->RegisterNode( ENT_OPERATION,  ImColor{ .95f, .7f, .053f } );

    this->RegisterPin( EPT_FLOW,        ImColor( 208, 208, 208 ) );
    this->RegisterPin( EPT_STRING,      ImColor( 124,  21, 153 ) );
    this->RegisterPin( EPT_BOOL,        ImColor( 220,  48,  48 ) );
    this->RegisterPin( EPT_INT8,        ImColor(  68, 201, 156 ) );
    this->RegisterPin( EPT_INT16,       ImColor(  68, 201, 156 ) );
    this->RegisterPin( EPT_INT32,       ImColor(  68, 201, 156 ) );
    this->RegisterPin( EPT_INT64,       ImColor(  68, 201, 156 ) );
    this->RegisterPin( EPT_FLOAT32,     ImColor( 147, 226,  74 ) );
    this->RegisterPin( EPT_FLOAT64,     ImColor( 147, 226,  74 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutNodeStyle::RegisterNode( nUInt query, ImColor color ) {
    if ( this->node_colors.find( query ) == this->node_colors.end( ) ) {
        auto pair = std::make_pair( query, color );

        this->node_colors.emplace( pair );
    }
}

void NutNodeStyle::RegisterPin( nUInt query, ImColor color ) {
    if ( this->pin_colors.find( query ) == this->pin_colors.end( ) ) {
        auto pair = std::make_pair( query, color );

        this->pin_colors.emplace( pair );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const ImColor& NutNodeStyle::GetNode( nUInt query ) const {
    auto iterator = this->node_colors.find( query );

    if ( iterator != this->node_colors.end( ) )
        return ( *iterator ).second;

	return ImGUI::NODE_COMMENT_COLOR;
}

const ImColor& NutNodeStyle::GetPin( nUInt query ) const {
    auto iterator = this->pin_colors.find( query );

    if ( iterator != this->pin_colors.end( ) )
        return ( *iterator ).second;

    return ImGUI::NODE_COMMENT_COLOR;
}
