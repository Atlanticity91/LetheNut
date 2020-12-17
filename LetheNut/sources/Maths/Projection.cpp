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

#include <LetheNut/Framework/Maths/Projection.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutProjection::NutProjection( float min_zoom, float max_zoom )
	: aspect_ratio( 16 / 9 ),
	zoom( min_zoom ),
	z_far( 100.f ),
	z_near( -1.f ),
	min_zoom( min_zoom ),
	max_zoom( max_zoom )
{ }

NutProjection& NutProjection::Zoom( float level ) {
	this->zoom += level;

	nHelper::Clamp( this->zoom, this->min_zoom, this->max_zoom );

	return *this;
}

NutProjection& NutProjection::SetZoom( float level ) {
	this->zoom = level;

	nHelper::Clamp( this->zoom, this->min_zoom, this->max_zoom );

	return *this;
}

NutProjection& NutProjection::SetAspectRatio( float value ) {
	this->aspect_ratio = value;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
float NutProjection::GetAspectRatio( ) const { return this->aspect_ratio; }

float NutProjection::GetZoom( ) const { return this->zoom; }

float NutProjection::GetZFar( ) const { return this->z_far; }

float NutProjection::GetZNear( ) const { return this->z_near; }
