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

#include <LetheNut/Framework/Maths/Matrix.hpp>
#include <LetheNut/Framework/Maths/Projection.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutMatrix::NutMatrix( )
{
	this->ToIdentity( );
}

NutMatrix& NutMatrix::ToIdentity( ) {
	for ( auto idx = 14; idx > 0; idx-- )
		this->data[ idx ] = 0;

	this->data[  0 ] = 1.f;
	this->data[  5 ] = 1.f;
	this->data[ 10 ] = 1.f;
	this->data[ 15 ] = 1.f;

	return *this;
}

void NutMatrix::LookAt( const NutVec3& eye, const NutVec3& at, const NutVec3& up ) {
	/*
	float X[ 3 ], Y[ 3 ], Z[ 3 ], tmp[ 3 ];

	tmp[ 0 ] = eye[ 0 ] - at[ 0 ];
	tmp[ 1 ] = eye[ 1 ] - at[ 1 ];
	tmp[ 2 ] = eye[ 2 ] - at[ 2 ];

	Normalize( tmp, Z );
	Normalize( up, Y );
	Cross( Y, Z, tmp );
	Normalize( tmp, X );
	Cross( Z, X, tmp );
	Normalize( tmp, Y );

	this->data[ 0 ] = X[ 0 ];
	this->data[ 1 ] = Y[ 0 ];
	this->data[ 2 ] = Z[ 0 ];
	this->data[ 3 ] = 0.f;
	this->data[ 4 ] = X[ 1 ];
	this->data[ 5 ] = Y[ 1 ];
	this->data[ 6 ] = Z[ 1 ];
	this->data[ 7 ] = 0.f;
	this->data[ 8 ] = X[ 2 ];
	this->data[ 9 ] = Y[ 2 ];
	this->data[ 10 ] = Z[ 2 ];
	this->data[ 11 ] = 0.f;
	this->data[ 12 ] = -Dot( X, eye );
	this->data[ 13 ] = -Dot( Y, eye );
	this->data[ 14 ] = -Dot( Z, eye );
	this->data[ 15 ] = 1.f;
	*/
}

void NutMatrix::LookAt( const NutVec3&& eye, const NutVec3&& at, const NutVec3&& up ) {
	this->LookAt( eye, at, up );
}

void NutMatrix::Frustum( float left, float right, float bottom, float top, float z_near, float z_far ) {
	this->ToIdentity( );

	float temp = 2.f * z_near;
	float temp2 = right - left;
	float temp3 = top - bottom;
	float temp4 = z_far - z_near;

	this->data[  0 ] = temp / temp2;
	this->data[  5 ] = temp / temp3;
	this->data[  8 ] = ( right + left ) / temp2;
	this->data[  9 ] = ( top + bottom ) / temp3;
	this->data[ 10 ] = ( -z_far - z_near ) / temp4;
	this->data[ 11 ] = -1.0f;
	this->data[ 14 ] = ( -temp * z_far ) / temp4;
}

void NutMatrix::Perspective( float fov_y, float aspect_ratio, float z_near, float z_far ) {
	nHelper::ToRad( fov_y );

	float y_max = z_near * tanf( fov_y );
	float x_max = y_max * aspect_ratio;

	this->Frustum( -x_max, x_max, -y_max, y_max, z_near, z_far );
}

void NutMatrix::Ortho( float aspect_ratio, float z_near, float z_far, float zoom ) {
	float ratio = aspect_ratio * zoom;
	float far_min_near = z_far - z_near;
	
	this->data[  0 ] = 1.f / ratio;
	this->data[  5 ] = 1.f / zoom;
	this->data[ 10 ] = ( -2.f ) / far_min_near;
	this->data[ 11 ] = -( z_far + z_near ) / far_min_near;
}

void NutMatrix::Ortho( const NutProjection& projection ) {
	this->Ortho( 
		projection.GetAspectRatio( ), 
		projection.GetZNear( ), 
		projection.GetZFar( ), 
		projection.GetZoom( ) 
	);
}

NutMatrix& NutMatrix::Set( const NutMatrix& other ) {
	nHelper::Copy( other, *this );

	return *this;
}

NutMatrix& NutMatrix::Set( const NutVec2& transform, const float rotation, const NutVec2& scale ) {
	this->ToIdentity( );
	this->RotateZ( rotation );
	this->Transform( transform );

	return this->Scale( scale );
}

NutMatrix& NutMatrix::Set( const NutVec2&& transform, const float rotation, const NutVec2&& scale ) {
	return this->Set( transform, rotation, scale );
}

NutMatrix& NutMatrix::Set( const NutVec3& transform, const NutVec3& rotation, const NutVec3& scale ) {
	this->ToIdentity( );
	this->Transform( transform );
	this->Rotate( rotation );

	return this->Scale( scale );
}

NutMatrix& NutMatrix::Set( const NutVec3&& transform, const NutVec3&& rotation, const NutVec3&& scale ) {
	return this->Set( transform, rotation, scale );
}

NutMatrix& NutMatrix::RotateX( float degree ) {
	auto result = NutMatrix::RotationX( degree );

	return this->Set( result );
}

NutMatrix& NutMatrix::RotateY( float degree ) {
	auto result = NutMatrix::RotationY( degree );

	return this->Set( result );
}

NutMatrix& NutMatrix::RotateZ( float degree ) {
	auto result = NutMatrix::RotationZ( degree );

	return this->Set( result );
}

NutMatrix& NutMatrix::Rotate( const NutVec3& value ) {
	auto rot_x = NutMatrix::RotateX( value.x );
	auto rot_y = NutMatrix::RotateX( value.y );
	auto rot_z = NutMatrix::RotateX( value.z );
	auto result = rot_z * rot_y * rot_x;

	return this->Set( result );
}

NutMatrix& NutMatrix::Rotate( const NutVec3&& value ) {
	return this->Rotate( value );
}

NutMatrix& NutMatrix::Transform( const NutVec2& value ) {
	this->columns[ 3 ].x = value.x;
	this->columns[ 3 ].y = value.y;

	return *this;
}

NutMatrix& NutMatrix::Transform( const NutVec2&& value ) {
	return this->Transform( value );
}

NutMatrix& NutMatrix::Transform( const NutVec3& value ) {
	this->columns[ 3 ].x = value.x;
	this->columns[ 3 ].y = value.y;
	this->columns[ 3 ].z = value.z;

	return *this;
}

NutMatrix& NutMatrix::Transform( const NutVec3&& value ) {
	return this->Transform( value );
}

NutMatrix& NutMatrix::Scale( float value ) {
	value = fabs( value );

	if ( value > 0.f ) {
		this->data[  0 ] *= value;
		this->data[  5 ] *= value;
		this->data[ 10 ] *= value;
	}

	return *this;
}

NutMatrix& NutMatrix::Scale( const NutVec2& value ) {
	this->data[ 0 ] *= value.x;
	this->data[ 5 ] *= value.y;

	return *this;
}

NutMatrix& NutMatrix::Scale( const NutVec2&& value ) {
	return this->Scale( value );
}

NutMatrix& NutMatrix::Scale( const NutVec3& value ) {
	this->data[  0 ] *= value.x;
	this->data[  5 ] *= value.y;
	this->data[ 10 ] *= value.z;

	return *this;
}

NutMatrix& NutMatrix::Scale( const NutVec3&& value ) {
	return this->Scale( value );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC STATIC
///////////////////////////////////////////////////////////////////////////////////////////
NutMatrix NutMatrix::RotationX( float degree ) {
	auto rot_x = NutMatrix( );

	nHelper::ToRad( degree );

	float cos = cosf( degree );
	float sin = sinf( degree );

	rot_x[ 1 ] = cos;
	rot_x[ 2 ] = -sin;
	rot_x[ 5 ] =  sin;
	rot_x[ 6 ] =  cos;

	return rot_x;
}

NutMatrix NutMatrix::RotationY( float degree ) {
	auto rot_y = NutMatrix( );

	nHelper::ToRad( degree );

	float cos = cosf( degree );
	float sin = sinf( degree );

	rot_y[ 0 ] = -sin;
	rot_y[ 2 ] =  cos;
	rot_y[ 4 ] =  cos;
	rot_y[ 6 ] =  sin;

	return rot_y;
}

NutMatrix NutMatrix::RotationZ( float degree ) {
	auto rot_y = NutMatrix( );

	nHelper::ToRad( degree );

	float cos = cosf( degree );
	float sin = sinf( degree );

	rot_y[ 0 ] =  cos;
	rot_y[ 1 ] = -sin;
	rot_y[ 4 ] =  sin;
	rot_y[ 5 ] =  cos;

	return rot_y;
}

NutMatrix NutMatrix::Multiply( const NutMatrix& one, const NutMatrix& two ) {
	NutMatrix tmp;

	tmp[  0 ] = one[  0 ] * two[  0 ] + one[  1 ] * two[  4 ] + one[  2 ] * two[  8 ] + one[  3 ] * two[ 12 ];
	tmp[  1 ] = one[  0 ] * two[  1 ] + one[  1 ] * two[  5 ] + one[  2 ] * two[  9 ] + one[  3 ] * two[ 13 ];
	tmp[  2 ] = one[  0 ] * two[  2 ] + one[  1 ] * two[  6 ] + one[  2 ] * two[ 10 ] + one[  3 ] * two[ 14 ];
	tmp[  3 ] = one[  0 ] * two[  3 ] + one[  1 ] * two[  7 ] + one[  2 ] * two[ 11 ] + one[  3 ] * two[ 15 ];

	tmp[  4 ] = one[  4 ] * two[  0 ] + one[  5 ] * two[  4 ] + one[  6 ] * two[  8 ] + one[  7 ] * two[ 12 ];
	tmp[  5 ] = one[  4 ] * two[  1 ] + one[  5 ] * two[  5 ] + one[  6 ] * two[  9 ] + one[  7 ] * two[ 13 ];
	tmp[  6 ] = one[  4 ] * two[  2 ] + one[  5 ] * two[  6 ] + one[  6 ] * two[ 10 ] + one[  7 ] * two[ 14 ];
	tmp[  7 ] = one[  4 ] * two[  3 ] + one[  5 ] * two[  7 ] + one[  6 ] * two[ 11 ] + one[  7 ] * two[ 15 ];

	tmp[  8 ] = one[  8 ] * two[  0 ] + one[  9 ] * two[  4 ] + one[ 10 ] * two[  8 ] + one[ 11 ] * two[ 12 ];
	tmp[  9 ] = one[  8 ] * two[  1 ] + one[  9 ] * two[  5 ] + one[ 10 ] * two[  9 ] + one[ 11 ] * two[ 13 ];
	tmp[ 10 ] = one[  8 ] * two[  2 ] + one[  9 ] * two[  6 ] + one[ 10 ] * two[ 10 ] + one[ 11 ] * two[ 14 ];
	tmp[ 11 ] = one[  8 ] * two[  3 ] + one[  9 ] * two[  7 ] + one[ 10 ] * two[ 11 ] + one[ 11 ] * two[ 15 ];

	tmp[ 12 ] = one[ 12 ] * two[  0 ] + one[ 13 ] * two[  4 ] + one[ 14 ] * two[  8 ] + one[ 15 ] * two[ 12 ];
	tmp[ 13 ] = one[ 12 ] * two[  1 ] + one[ 13 ] * two[  5 ] + one[ 14 ] * two[  9 ] + one[ 15 ] * two[ 13 ];
	tmp[ 14 ] = one[ 12 ] * two[  2 ] + one[ 13 ] * two[  6 ] + one[ 14 ] * two[ 10 ] + one[ 15 ] * two[ 14 ];
	tmp[ 15 ] = one[ 12 ] * two[  3 ] + one[ 13 ] * two[  7 ] + one[ 14 ] * two[ 11 ] + one[ 15 ] * two[ 15 ];

	return tmp;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
float& NutMatrix::operator[]( nInt index ) { return this->data[ index % 16 ]; }

float NutMatrix::operator[]( nInt index ) const { return this->data[ index % 16 ]; }

NutMatrix& NutMatrix::operator( )( ) { return this->ToIdentity( ); }

NutMatrix NutMatrix::operator*( const NutMatrix& other ) {
	return NutMatrix::Multiply( *this, other );
}

NutMatrix& NutMatrix::operator=( const NutMatrix& other ) { return this->Set( other ); }
