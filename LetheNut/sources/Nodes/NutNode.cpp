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
NutNode::NutNode( ImVec2 position, const NutNodeModel& model ) 
	: context{ model.GetName( ), model.GetDescription( ), position, false },
	model( model ),
	out_length( 0.f )
{ 
	for ( auto& out : model.GetOutPins( ) ) {
		auto length = ImGUI::GetTextSize( out.name ).x;

		if ( this->out_length < length )
			this->out_length = length;
	}
}

NutNode::~NutNode( ) 
{ }

void NutNode::ConnectIn( nUInt query_id ) { this->model.ConnectIn( query_id ); }

void NutNode::DisConnectIn( nUInt query_id ) { this->model.DisConnectIn( query_id ); }

void NutNode::ToggleIn( nUInt query_id ) { this->model.ToggleIn( query_id ); }

void NutNode::ConnectOut( nUInt query_id ) { this->model.ConnectOut( query_id ); }

void NutNode::DisConnectOut( nUInt query_id ) { this->model.DisConnectOut( query_id ); }

void NutNode::ToggleOut( nUInt query_id ) { this->model.ToggleOut( query_id ); }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
ImGUI::ImNodeContext& NutNode::GetContext( ) const { return this->context; }

ENutNodeTypes NutNode::GetType( ) const { return this->model.GetType( ); }

nString NutNode::GetName( ) const { return this->model.GetName( ); }

nString NutNode::GetDescription( ) const { return this->model.GetDescription( ); }

ImVec2& NutNode::GetPosition( ) const { return this->context.position; }

bool NutNode::HasInPin( nUInt query_id ) const { return this->model.HasInPin( query_id ); }

const NutNodePin& NutNode::GetInPin( nUInt query_id ) const { return this->model.GetInPin( query_id ); }

const NutNode::PinList& NutNode::GetInPins( ) const { return this->model.GetInPins( ); }

const float NutNode::GetOutLength( ) const { return this->out_length; }

bool NutNode::HasOutPin( nUInt query_id ) const { return this->model.HasOutPin( query_id ); }

const NutNodePin& NutNode::GetOutPin( nUInt query_id ) const { return this->model.GetOutPin( query_id ); }

const NutNode::PinList& NutNode::GetOutPins( ) const { return this->model.GetOutPins( ); }
