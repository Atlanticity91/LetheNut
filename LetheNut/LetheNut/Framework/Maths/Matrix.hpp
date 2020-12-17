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

#ifndef _IGS_NUT_MATRIX_HPP_
#define _IGS_NUT_MATRIX_HPP_

	#include <LetheNut/Core.hpp>

	enum ENutAxis : nUByte {

		ENA_AXE_X = 0,
		ENA_AXE_Y,
		ENA_AXE_Z

	};

	class NutProjection;

	struct NutVec2 {

		float x;
		float y;

	};

	struct NutVec3 {

		float x;
		float y;
		float z;

	};

	struct NutVec4 {

		float x;
		float y;
		float z;
		float w;

	};

	class NutMatrix {

	private:
		union { 
			NutVec4 columns[ 4 ];
			float data[ 16 ];
		};

	public:
		NutMatrix( );

		~NutMatrix( ) = default;

		NutMatrix& ToIdentity( );

		void LookAt( const NutVec3& eye, const NutVec3& at, const NutVec3& up );

		void LookAt( const NutVec3&& eye, const NutVec3&& at, const NutVec3&& up );

		void Frustum( float left, float right, float bottom, float top, float z_near, float z_far );

		void Perspective( float fov_y, float aspect_ratio, float z_near, float z_far );

		void Ortho( float aspect_ratio, float z_near, float z_far, float zoom );

		void Ortho( const NutProjection& projection );

		NutMatrix& Set( const NutMatrix& other );

		NutMatrix& Set( const NutVec2& transform, const float rotation, const NutVec2& scale );

		NutMatrix& Set( const NutVec2&& transform, const float rotation, const NutVec2&& scale );

		NutMatrix& Set( const NutVec3& transform, const NutVec3& rotation, const NutVec3& scale );

		NutMatrix& Set( const NutVec3&& transform, const NutVec3&& rotation, const NutVec3&& scale );

		NutMatrix& RotateX( float degree );

		NutMatrix& RotateY( float degree );

		NutMatrix& RotateZ( float degree );

		NutMatrix& Rotate( const NutVec3& value );

		NutMatrix& Rotate( const NutVec3&& value );

		NutMatrix& Transform( const NutVec2& value );

		NutMatrix& Transform( const NutVec2&& value );

		NutMatrix& Transform( const NutVec3& value );

		NutMatrix& Transform( const NutVec3&& value );

		NutMatrix& Scale( float value );

		NutMatrix& Scale( const NutVec2& value );

		NutMatrix& Scale( const NutVec2&& value );

		NutMatrix& Scale( const NutVec3& value );

		NutMatrix& Scale( const NutVec3&& value );

	public:
		static NutMatrix RotationX( float degree );

		static NutMatrix RotationY( float degree );

		static NutMatrix RotationZ( float degree );

		static NutMatrix Multiply( const NutMatrix& one, const NutMatrix& two );

	public:
		float& operator[]( nInt index );

		float operator[]( nInt index ) const;

		NutMatrix& operator( )( );

		NutMatrix operator*( const NutMatrix& other );

		NutMatrix& operator=( const NutMatrix& other );

	};

#endif
