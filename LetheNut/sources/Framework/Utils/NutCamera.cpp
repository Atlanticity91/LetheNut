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

#include <LetheNut/Framework/Utils/NutCamera.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutCamera::NutCamera( float zoom_min, float zoom_max )
	: translation( ),
	rotation( ),
	zoom( zoom_min, zoom_min, zoom_max ),
	matrix( )
{ }

void NutCamera::SetTranslation( const ImVec2& value ) {
	this->translation.x = value.x;
	this->translation.y = value.y;
}

void NutCamera::SetTranslation( const glm::vec2& value ) {
	this->translation.x = value.x;
	this->translation.y = value.y;
}

void NutCamera::SetTranslation( const glm::vec3& value ){
	this->translation = value;
}

void NutCamera::SetTranslation( float x, float y ) {
	this->translation.x = x;
	this->translation.y = y;
}

void NutCamera::SetTranslation( float x, float y, float z ) {
	this->translation.x = x;
	this->translation.y = y;
	this->translation.z = z;
}

void NutCamera::SetRotation( float z ) { this->rotation.z = z; }

void NutCamera::SetRotation( const glm::vec3& value ) { 
	this->rotation = value;
}

void NutCamera::SetRotation( float x, float y, float z ) {
	this->translation.x = x;
	this->translation.y = y;
	this->translation.z = z;
}

void NutCamera::SetZoom( float level ) {
	this->zoom.x = level;

	nHelper::Clamp( this->zoom.x, this->zoom.y, this->zoom.z );
}

void NutCamera::Calculate( ) {
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
glm::vec3& NutCamera::GetTranslation( ) const { return this->translation; }

glm::vec3& NutCamera::GetRotation( ) const { return this->rotation; }

float NutCamera::GetZoomLevel( ) const { return this->zoom.x; }

glm::vec3& NutCamera::GetZoom( ) const { return this->zoom; }

glm::mat4x4& NutCamera::GetMatrix( ) const { return this->matrix; }
