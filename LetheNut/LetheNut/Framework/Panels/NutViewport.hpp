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

#ifndef _IGS_NUT_VIEWPORT_HPP_
#define _IGS_NUT_VIEWPORT_HPP_

	#include <LetheNut/UI/NutPanel.hpp>
	#include <LetheNut/Framework/Utils/NutCamera.hpp>

	NUT_PANEL( NutViewport ) {

	protected:
		ImVec2 view_size;
		mutable NutProjection projection;
		mutable NutCamera camera;
		mutable OpenGL::Frame renderer;

	public:
		NutViewport( );

		~NutViewport( ) = default;

	protected:
		virtual void OnCreate( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnProcess( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnRender( NutEditor* editor, NutWindow* parent ) override;

	public:
		/**
		 * GetProjection const function
		 * @author : ALVES Quentin
		 * @note : Get current viewport projection.
		 * @return : NutProjection&
		 **/
		NutProjection& GetProjection( ) const;

		NutCamera& GetCamera( ) const;

		OpenGL::Frame& GetRenderer( ) const;

	};

#endif
