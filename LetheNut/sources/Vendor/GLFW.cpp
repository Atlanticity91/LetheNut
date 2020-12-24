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

#include <LetheNut/Vendor/GLFW.hpp>
#include <LetheNut/Vendor/STB.hpp>
#include <Thirdparty/GLFW/glfw3.h>

bool GLFW::Initialize( nPointer& window ) {
	if ( !window ) {
		if ( glfwInit( ) ) {
			glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );
			glfwWindowHint( GLFW_STEREO, GLFW_FALSE );
			glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );
			glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
			glfwWindowHint( GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API );
			glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
			glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
			glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
			glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
			glfwSwapInterval( GLFW_TRUE );

			auto* handle = glfwCreateWindow( 1280, 720, "Lethe Engine", nullptr, nullptr );

			if ( handle )
				glfwMakeContextCurrent( handle );

			window = (nPointer)handle;

			return handle;
		}
	}

	return false;
}

bool GLFW::ShouldRun( const nPointer window ) {
	if ( window ) {
		auto* handle = (struct GLFWwindow*)window;

		if ( !glfwWindowShouldClose( handle ) ) {
			glfwMakeContextCurrent( handle );
			glfwSwapBuffers( handle );
			glfwPollEvents( );

			return true;
		}
	}

	return false;
}

void GLFW::Destroy( nPointer& window ) {
	if ( window ) {
		auto* handle = (struct GLFWwindow*)window;

		glfwDestroyWindow( handle );

		window = nullptr;
	}
}

void GLFW::Cleanup( ) { glfwTerminate( ); }
