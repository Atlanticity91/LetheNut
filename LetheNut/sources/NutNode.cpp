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

#include <LetheNut/Editors/Nodes/NutNode.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNode::NutNode( ENutNodeTypes type, nString name, nString description ) 
	: NutBasic( name ),
	type( type ),
	description( description ),
	inputs( ),
	outputs( )
{ }

NutNode::~NutNode( ) 
{ }

void NutNode::AddIn( const NutNodePin& pin ) { this->inputs.emplace_back( pin ); }

void NutNode::AddIn( const NutNodePin&& pin ) { this->AddIn( pin ); }

void NutNode::AddIn( bool is_array, ENutPinTypes type, nString name, nString description ) {
	this->AddIn( NutNodePin{ is_array, type, name, description } );
}

void NutNode::AddOut( const NutNodePin& pin ) { this->outputs.emplace_back( pin ); }

void NutNode::AddOut( const NutNodePin&& pin ) { this->AddOut( pin ); }

void NutNode::AddOut( bool is_array, ENutPinTypes type, nString name, nString description ) {
	this->AddOut( NutNodePin{ is_array, type, name, description } );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
ENutNodeTypes NutNode::GetType( ) const { return this->type; }

nString NutNode::GetDescription( ) const { return this->description; }

bool NutNode::HasInPin( nUInt query_id ) const { 
	return query_id < this->inputs.size( ); 
}

const NutNodePin& NutNode::GetInPin( nUInt query_id ) const { 
	return this->inputs[ query_id ]; 
}

const NutNode::PinList& NutNode::GetInPins( ) const { return this->inputs; }

bool NutNode::HasOutPin( nUInt query_id ) const { 
	return query_id < this->outputs.size( ); 
}

const NutNodePin& NutNode::GetOutPin( nUInt query_id ) const {
	return this->outputs[ query_id ];
}

const NutNode::PinList& NutNode::GetOutPins( ) const { return this->outputs; }
