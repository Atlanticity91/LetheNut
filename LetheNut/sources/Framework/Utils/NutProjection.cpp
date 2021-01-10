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

#include <LetheNut/Framework/Utils/NutProjection.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutProjection::NutProjection( )
	: is_ortho( true ),
	matrix( )
{
	this->data.ortho.width = 640.f;
	this->data.ortho.height = 480.f;
}

NutProjection::NutProjection( float aspect_ratio, float z_near, float z_far ) 
	: is_ortho( false ),
	matrix( )
{
	this->aspect_ratio = aspect_ratio;
	this->data.projection.z_far = z_far;
	this->data.projection.z_near = z_near;
}

NutProjection& NutProjection::SetAspectRatio( float value ) {
	this->aspect_ratio = value;

	return *this;
}

NutProjection& NutProjection::SetAspectRatio( float width, float height ) {
	this->aspect_ratio = width / height;

	return *this;
}

NutProjection& NutProjection::SetZNear( float value ) {
	this->data.projection.z_near = value;

	return *this;
}

NutProjection& NutProjection::SetZFar( float value ) {
	this->data.projection.z_far = value;

	return *this;
}

NutProjection& NutProjection::SetSize( const ImVec2& size ) {
	return this->SetSize( size.x, size.y );
}

NutProjection& NutProjection::SetSize( const glm::vec2& size ) {
	return this->SetSize( size.x, size.y );
}

NutProjection& NutProjection::SetSize( float width, float height ) {
	this->aspect_ratio = width / height;
	this->data.ortho.width = width * this->aspect_ratio * .5f;
	this->data.ortho.height = height * .5f;

	return *this;
}

void NutProjection::Calculate( ) {
	if ( !this->is_ortho )
		this->matrix = glm::perspective( glm::pi<float>( ) * 0.25f, this->aspect_ratio, this->data.projection.z_near, this->data.projection.z_far );
	else 
		this->matrix = glm::ortho( -this->data.ortho.width, this->data.ortho.width, -this->data.ortho.height, this->data.ortho.height );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
float NutProjection::GetAspectRatio( ) const { return this->aspect_ratio; }

float NutProjection::GetZFar( ) const { return this->data.projection.z_far; }

float NutProjection::GetZNear( ) const { return this->data.projection.z_near; }

float NutProjection::GetWidth( ) const { return this->data.ortho.width; }

float NutProjection::GetHeight( ) const { return this->data.ortho.height; }
