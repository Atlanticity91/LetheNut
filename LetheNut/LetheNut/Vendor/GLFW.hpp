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

#ifndef _IGS_NUT_GLFW_HPP_
#define _IGS_NUT_GLFW_HPP_

	#include <LetheNut/NutCore.hpp>

	/**
	 * GLFW namespace
	 * @author : ALVES Quentin
	 * @node : Wrapper for GLFW.
	 **/
	namespace GLFW {

		/**
		 * Window struct
		 * @author : ALVES Quentin
		 * @node : Wrapper for GLFW.
		 **/
		struct NUT_API Window {

			nPointer handle;
			nString label;
			nInt width;
			nInt height;

		};

		/**
		 * Initialize function
		 * @author : ALVES Quentin
		 * @node : Initialize GLFW.
		 * @return : bool
		 **/
		bool Initialize( );

		/**
		 * CreateContext function
		 * @author : ALVES Quentin
		 * @node : Create GLFW window for OpenGL ressource loader context.
		 * @param window : Reference to GLFW window to hold the window.
		 * @return : bool
		 **/
		bool CreateWindowLess( nPointer& window );

		/**
		 * Create function
		 * @author : ALVES Quentin
		 * @node : Create a GLFW window.
		 * @param window : Reference to GLFW window to hold the window.
		 * @param ressources : Current OpenGL ressource loader context.
		 * @return : bool
		 **/
		NUT_API bool Create( Window& window, const nPointer ressources );

		/**
		 * SetContext method
		 * @author : ALVES Quentin
		 * @node : Set current GLFW context.
		 * @param window : Reference to query GLFW window.
		 **/
		NUT_API void SetContext( Window& window );

		/**
		 * ShouldRun function
		 * @author : ALVES Quentin
		 * @node : Return true if the query window should run.
		 * @param window : Reference to query GLFW window.
		 * @return : bool
		 **/
		NUT_API bool ShouldRun( Window& window );

		/**
		 * Process method
		 * @author : ALVES Quentin
		 * @node : Process a GLFW window.
		 * @param window : Reference to query GLFW window.
		 **/
		NUT_API void Process( Window& window );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @node : Destroy a GLFW window.
		 * @param window : Reference to query GLFW window.
		 **/
		NUT_API void Destroy( Window& window );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @node : Destroy a GLFW window.
		 * @param window : Reference to query GLFW window.
		 **/
		NUT_API void Destroy( nPointer& window );

		/**
		 * Cleanup method
		 * @author : ALVES Quentin
		 * @node : Cleanup GLFW.
		 **/
		NUT_API void Cleanup( );

	};

#endif
