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

#ifndef _IGS_NUT_GLM_HPP_
#define _IGS_NUT_GLM_HPP_

	#include <LetheNut/NutCore.hpp>
	#include <Thirdparty/GLM/vec2.hpp>
	#include <Thirdparty/GLM/vec3.hpp>
	#include <Thirdparty/GLM/vec4.hpp>
	#include <Thirdparty/GLM/mat3x3.hpp>
	#include <Thirdparty/GLM/mat4x4.hpp>
	#include <Thirdparty/GLM/ext/matrix_transform.hpp>
	#include <Thirdparty/GLM/ext/matrix_clip_space.hpp>
	#include <Thirdparty/GLM/ext/scalar_constants.hpp>

	/**
	 * GLM namespace
	 * @author : ALVES Quentin
	 * @node : Wrapper for GLM.
	 **/
	namespace GLM {

		const float PI_f = glm::pi<float>( );
		const double PI_d = glm::pi<double>( );
		const float RAD2DEG_f = ( 180.f / PI_f );
		const double RAD2DEG_d = ( 180.f / PI_d );
		const float DEG2RAD_f = ( PI_f / 180.f );
		const double DEG2RAD_d = ( PI_d / 180.f );

		/**
		 * ToDeg static method
		 * @author : ALVES Quentin
		 * @note : Conert radians angle to degrees.
		 * @param radians : Reference to radians angle.
		 **/
		NUT_API void ToDeg( float& radians );

		/**
		 * ToDeg static method
		 * @author : ALVES Quentin
		 * @note : Conert radians angle to degrees.
		 * @param radians : Reference to radians angle.
		 **/
		NUT_API void ToDeg( double& radians );

		/**
		 * ToRad static method
		 * @author : ALVES Quentin
		 * @note : Conert degrees angle to radians.
		 * @param degree : Reference to degree angle.
		 **/
		NUT_API void ToRad( float& degree );

		/**
		 * ToRad static method
		 * @author : ALVES Quentin
		 * @note : Conert degrees angle to radians.
		 * @param degree : Reference to degree angle.
		 **/
		NUT_API void ToRad( double& degree );

	};

#endif
