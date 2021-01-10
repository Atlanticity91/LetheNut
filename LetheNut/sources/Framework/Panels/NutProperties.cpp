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

#include "__pch.hpp"

#include <LetheNut/Framework/Panels/NutProperties.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutProperty::NutProperty( bool need_context, nString label, nString description, NutPropertyCondition condition, NutPropertyContent content )
	: need_context( need_context ),
	label( label ),
	description( description ),
	condition( condition ),
	content( content )
{ 
	this->hash = nHelper::Hash( label );
}

NutHash NutProperty::GetHash( ) const { return this->hash; }

NutProperties::NutProperties( )
	: NutPanel( "Properties", ImVec2{ 0.f, 1.f } ),
	properties( )
{ }

void NutProperties::Register( nString label, NutPropertyContent content ) {
	this->Register( label, "", nullptr, content );
}

void NutProperties::Register( nString label, NutPropertyCondition condition, NutPropertyContent content ) {
	this->Register( label, "", condition, content );
}

void NutProperties::Register( nString label, nString description, NutPropertyContent content ) {
	this->Register( label, description, nullptr, content );
}

void NutProperties::Register( nString label, nString description, NutPropertyCondition condition, NutPropertyContent content ) {
	if ( content ) {
		if ( !this->properties[ label ] )
			this->properties.Append( condition, label, description, condition, content );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutProperties::OnCreate( NutEditor* editor, NutWindow* parent ) { }

void NutProperties::OnProcess( NutEditor* editor, NutWindow* parent ) { }

void NutProperties::OnRender( NutEditor* editor, NutWindow* parent ) { 
	this->properties.Foreach( 
		[ this ]( auto& property, NutEditor* editor, NutWindow* parent ) {
			if ( !property.need_context )
				this->OnRenderCategory( property, editor, parent );
			else if ( property.condition && property.condition( editor, parent, this, this->GetContext( ) ) )
				this->OnRenderCategory( property, editor, parent );
		},
		editor, parent
	);
}

void NutProperties::OnRenderCategory( NutProperty& property, NutEditor* editor, NutWindow* parent ) {
	if ( ImGUI::Category( property.label, property.description ) )
		property.content( editor, parent, this, this->GetContext( ) );

	ImGUI::EndCategory( );
}
