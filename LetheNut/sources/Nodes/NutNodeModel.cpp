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

#include <LetheNut/Editors/Nodes/NutNodeModel.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeModel::NutNodeModel( )
	: NutBasic( "" )
{ }

NutNodeModel::NutNodeModel( const NutNodeModel& other ) 
	: NutBasic( other.GetName( ) ),
	type( other.GetType( ) ),
	description( other.GetDescription( ) ),
	inputs( other.GetInPins( ) ),
	outputs( other.GetOutPins( ) )
{ 
	for ( auto idx = 0; idx < this->inputs.size( ); idx++ ) {
		if ( this->inputs[ idx ].type == ENutPinTypes::EPT_STRING ) {
			this->inputs[ idx ].data.string.length = 128;
			this->inputs[ idx ].data.string.value = nHelper::Alloc<char>( this->inputs[ idx ].data.string.length );

			nHelper::Copy( "Edit me !", this->inputs[ idx ].data.string.value, this->inputs[ idx ].data.string.length );
		}
	}
}

NutNodeModel::NutNodeModel( ENutNodeTypes type, nString name, nString description )
	: NutBasic( name ),
	type( type ),
	description( description ),
	inputs( ),
	outputs( ) 
{ }

NutNodeModel::~NutNodeModel( ) { 
	for ( auto pin : this->inputs ) {
		if ( pin.type == ENutPinTypes::EPT_STRING && pin.data.string.value )
			free( pin.data.string.value );
	}

	for ( auto pin : this->outputs ) {
		if ( pin.type == ENutPinTypes::EPT_STRING && pin.data.string.value )
			free( pin.data.string.value );
	}
}

void NutNodeModel::AddIn( const NutNodePin& pin ) { this->inputs.emplace_back( pin ); }

void NutNodeModel::AddIn( const NutNodePin&& pin ) { this->AddIn( pin ); }

void NutNodeModel::AddIn( bool is_array, ENutPinTypes type, nString name, nString description ) {
	auto pin = NutNodePin{ is_array, false, type, name, description };

	this->AddIn( pin );
}

void NutNodeModel::ConnectIn( nUInt query_id ) {
	if ( this->HasInPin( query_id ) )
		this->inputs[ query_id ].is_connected = true;
}

void NutNodeModel::DisConnectIn( nUInt query_id ) {
	if ( this->HasInPin( query_id ) )
		this->inputs[ query_id ].is_connected = false;
}

void NutNodeModel::ToggleIn( nUInt query_id ) {
	if ( this->HasInPin( query_id ) )
		this->inputs[ query_id ].is_connected = !this->inputs[ query_id ].is_connected;
}

void NutNodeModel::AddOut( const NutNodePin& pin ) { this->outputs.emplace_back( pin ); }

void NutNodeModel::AddOut( const NutNodePin&& pin ) { this->AddOut( pin ); }

void NutNodeModel::AddOut( bool is_array, ENutPinTypes type, nString name, nString description ) {
	auto pin = NutNodePin{ is_array, false, type, name, description };
	pin.data.string.value = nullptr;

	this->AddOut( pin );
}

void NutNodeModel::ConnectOut( nUInt query_id ) {
	if ( this->HasOutPin( query_id ) )
		this->outputs[ query_id ].is_connected = true;
}

void NutNodeModel::DisConnectOut( nUInt query_id ) {
	if ( this->HasOutPin( query_id ) )
		this->outputs[ query_id ].is_connected = false;
}

void NutNodeModel::ToggleOut( nUInt query_id ) {
	if ( this->HasOutPin( query_id ) )
		this->outputs[ query_id ].is_connected = !this->outputs[ query_id ].is_connected;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
ENutNodeTypes NutNodeModel::GetType( ) const { return this->type; }

nString NutNodeModel::GetDescription( ) const { return this->description; }

bool NutNodeModel::HasInPin( nUInt query_id ) const {
	return query_id < this->inputs.size( );
}

const NutNodePin& NutNodeModel::GetInPin( nUInt query_id ) const {
	return this->inputs[ query_id ];
}

const NutNodeModel::PinList& NutNodeModel::GetInPins( ) const { return this->inputs; }

bool NutNodeModel::HasOutPin( nUInt query_id ) const {
	return query_id < this->outputs.size( );
}

const NutNodePin& NutNodeModel::GetOutPin( nUInt query_id ) const {
	return this->outputs[ query_id ];
}

const NutNodeModel::PinList& NutNodeModel::GetOutPins( ) const { return this->outputs; }
