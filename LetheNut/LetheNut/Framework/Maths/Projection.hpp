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

#ifndef _IGS_NUT_PROJECTION_HPP_
#define _IGS_NUT_MATRIX_HPP_

	#include <LetheNut/Core.hpp>

	/**
	 * NutProjection class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Projection core class.
	 **/
	class NUT_API NutProjection {

	private:
		float aspect_ratio;
		float zoom;
		float z_far;
		float z_near;
		float min_zoom;
		float max_zoom;

	public:
		/**
		 * Constructor 
		 * @author : ALVES Quentin
		 * @param min_zoom : Minimum zoom level.
		 * @param max_zoom : Maximum zoom level.
		 **/
		NutProjection( float min_zoom, float max_zoom );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutProjection( ) = default;

		/**
		 * Zoom function
		 * @author : ALVES Quentin
		 * @note : Extend the current zoom level of value level.
		 * @param level : Zooming value.
		 * @return : NutProjection&
		 **/
		NutProjection& Zoom( float level );

		/**
		 * SetZoom function
		 * @author : ALVES Quentin
		 * @note : Set the current zoom level.
		 * @param level : Zoom level.
		 * @return : NutProjection&
		 **/
		NutProjection& SetZoom( float level );

		/**
		 * SetAspectRatio function
		 * @author : ALVES Quentin
		 * @note : Set the current aspect ratio.
		 * @param value : New aspect ratio.
		 * @return : NutProjection&
		 **/
		NutProjection& SetAspectRatio( float value );

	public:
		/**
		 * GetAspectRatio const function
		 * @author : ALVES Quentin
		 * @note : Get current aspect ratio.
		 * @return : float
		 **/
		float GetAspectRatio( ) const;

		/**
		 * GetZoom const function
		 * @author : ALVES Quentin
		 * @note : Get current zoom level.
		 * @return : float
		 **/
		float GetZoom( ) const;

		/**
		 * GetZFar const function
		 * @author : ALVES Quentin
		 * @note : Get current Z-Far value.
		 * @return : float
		 **/
		float GetZFar( ) const;

		/**
		 * GetZNear const function
		 * @author : ALVES Quentin
		 * @note : Get current Z-Near value.
		 * @return : float
		 **/
		float GetZNear( ) const;

	};

#endif
