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

#include <LetheNut/Editors/Nodes/NutNodeParser.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeParser::NutNodeParser( )
	: NutBasic( "Default" ),
	models( ) 
{ }

NutNodeParser::NutNodeParser( nString name )
	: NutBasic( name ),
	models( )
{ }

NutNodeParser::~NutNodeParser( ) { }

void NutNodeParser::Initialize( ) { 
	auto* branch = this->Create( ENutNodeTypes::ENT_BRANCH, "Branch", "" );
	branch->AddIn( false, ENutPinTypes::EPT_FLOW, "", "" );
	branch->AddOut( false, ENutPinTypes::EPT_FLOW, "True", "" );
	branch->AddOut( false, ENutPinTypes::EPT_FLOW, "False", "" );

	this->CreateOperation( ENutPinTypes::EPT_INT8, "Add (int8)", "Add two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT16, "Add (int16)", "Add two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT32, "Add (int32)", "Add two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT64, "Add (int64)", "Add two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT32, "Add (float32)", "Add two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT64, "Add (float64)", "Add two value." );

	this->CreateOperation( ENutPinTypes::EPT_INT8, "Subtract (int8)", "Subtract two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT16, "Subtract (int16)", "Subtract two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT32, "Subtract (int32)", "Subtract two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT64, "Subtract (int64)", "Subtract two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT32, "Subtract (float32)", "Subtract two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT64, "Subtract (float64)", "Subtract two value." );

	this->CreateOperation( ENutPinTypes::EPT_INT8, "Multiply (int8)", "Multiply two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT16, "Multiply (int16)", "Multiply two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT32, "Multiply (int32)", "Multiply two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT64, "Multiply (int64)", "Multiply two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT32, "Multiply (float32)", "Multiply two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT64, "Multiply (float64)", "Multiply two value." );

	this->CreateOperation( ENutPinTypes::EPT_INT8, "Divide (int8)", "Divide two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT16, "Divide (int16)", "Divide two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT32, "Divide (int32)", "Divide two value." );
	this->CreateOperation( ENutPinTypes::EPT_INT64, "Divide (int64)", "Divide two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT32, "Divide (float32)", "Divide two value." );
	this->CreateOperation( ENutPinTypes::EPT_FLOAT64, "Divide (float64)", "Divide two value." );

	this->CreateClamp( ENutPinTypes::EPT_INT8, "Clamp (int8)" );
	this->CreateClamp( ENutPinTypes::EPT_INT16, "Clamp (int16)" );
	this->CreateClamp( ENutPinTypes::EPT_INT32, "Clamp (int32)" );
	this->CreateClamp( ENutPinTypes::EPT_INT64, "Clamp (int64)" );
	this->CreateClamp( ENutPinTypes::EPT_FLOAT32, "Clamp (float32)" );
	this->CreateClamp( ENutPinTypes::EPT_FLOAT64, "Clamp (float64)" );

	this->CreateLerp( ENutPinTypes::EPT_INT8, "Lerp (int8)" );
	this->CreateLerp( ENutPinTypes::EPT_INT16, "Lerp (int16)" );
	this->CreateLerp( ENutPinTypes::EPT_INT32, "Lerp (int32)" );
	this->CreateLerp( ENutPinTypes::EPT_INT64, "Lerp (int64)" );

	this->CreateForeach( ENutPinTypes::EPT_INT8, "Foreach (int8)" );
	this->CreateForeach( ENutPinTypes::EPT_INT16, "Foreach (int16)" );
	this->CreateForeach( ENutPinTypes::EPT_INT32, "Foreach (int32)" );
	this->CreateForeach( ENutPinTypes::EPT_INT64, "Foreach (int64)" );
	this->CreateForeach( ENutPinTypes::EPT_FLOAT32, "Foreach (float32)" );
	this->CreateForeach( ENutPinTypes::EPT_FLOAT64, "Foreach (float64)" );

	this->CreateVar( ENutPinTypes::EPT_BOOL, false, "_TEST_0_" );
}

void NutNodeParser::CreateVar( ENutPinTypes type, bool is_array, nString name ) {
	auto var = this->Create( ENutNodeTypes::ENT_VARIABLE, name, "" );

	var->AddIn( is_array, type, "", "" );
	var->AddOut( is_array, type, "", "" );
}

void NutNodeParser::Parse( const NutNodeParser::NodeList& nodes ) {
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
NutNodeModel* NutNodeParser::Create( ENutNodeTypes type, nString name, nString description ) {
	auto model = NutNodeModel( type, name, description );

	this->models.emplace_back( model );

	return &this->models[ this->models.size( ) - 1 ];
}

NutNodeModel* NutNodeParser::Create( nString name, nString description ) {
	auto node = this->Create( ENutNodeTypes::ENT_FUNCTION, name, description );

	node->AddIn( false, ENutPinTypes::EPT_FLOW, "", "" );
	node->AddOut( false, ENutPinTypes::EPT_FLOW, "", "" );

	return node;
}

void NutNodeParser::CreateOperation( ENutPinTypes type, nString name, nString description ) {
	auto* operation = this->Create( ENutNodeTypes::ENT_OPERATION, name, description );
	operation->AddIn( false, type, "Value A", "" );
	operation->AddIn( false, type, "Value B", "" );
	operation->AddOut( false, type, "Return", "" );
}

void NutNodeParser::CreateClamp( ENutPinTypes type, nString name ) {
	auto* clamp = this->Create( name, "Clamp a value between minimum and maximum." );
	clamp->AddIn( false, type, "Mimimum", "" );
	clamp->AddIn( false, type, "Maximum", "" );
	clamp->AddIn( false, type, "Value", "" );
	clamp->AddOut( false, type, "Return", "" );
}

void NutNodeParser::CreateLerp( ENutPinTypes type, nString name ) {
	auto* lerp = this->Create( name, "Linear interpolation between A and B." );
	lerp->AddIn( false, type, "Value A", "" );
	lerp->AddIn( false, type, "Value B", "" );
	lerp->AddIn( false, ENutPinTypes::EPT_FLOAT32, "Scalar", "" );
	lerp->AddOut( false, type, "Return", "" );
}

void NutNodeParser::CreateForeach( ENutPinTypes type, nString name ) {
	auto* foreach = this->Create( ENutNodeTypes::ENT_FUNCTION, name, "" );
	foreach->AddIn( false, ENutPinTypes::EPT_FLOW, "", "" );
	foreach->AddIn( true, type, "Elements", "" );
	foreach->AddOut( false, ENutPinTypes::EPT_FLOW, "", "" );
	foreach->AddOut( false, ENutPinTypes::EPT_FLOW, "Loop", "" );
	foreach->AddOut( false, type, "Element", "" );
	foreach->AddOut( false, ENutPinTypes::EPT_INT32, "Element ID", "" );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const ETypeMatches NutNodeParser::TypeMatch( ENutPinTypes left, ENutPinTypes right ) const {
	if ( left != ENutPinTypes::EPT_FLOW && right != ENutPinTypes::EPT_FLOW ) {
		if ( left == right )
			return ETypeMatches::ETM_MATCH;
		else if ( left != ENutPinTypes::EPT_STRING && right != ENutPinTypes::EPT_STRING ) {
			if ( left < right )
				return ETypeMatches::ETM_DOWNCAST;
			else if ( left > right )
				return ETypeMatches::ETM_UPCAST;
		}
	}

	return ETypeMatches::ETM_NONE;
}

const nUInt NutNodeParser::GetModelCount( ) const { return (nUInt)this->models.size( ); }

const NutNodeModel* NutNodeParser::GetModel( nUInt query_id ) const {
	if ( query_id < this->models.size( ) ) 
		return  &this->models[ query_id ];

	return nullptr;
}
