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

#include <Thirdparty/GLFW/glfw3.h>
#include <Thirdparty/GLFW/glfw3native.h>
#include <LetheNut/Vendor/GLFW.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
bool GLFW::Initialize( ) { return glfwInit( ); }

bool GLFW::CreateWindowLess( nPointer& window ) {
	if ( glfwInit( ) ) {
		glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
		glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
		glfwWindowHint( GLFW_STEREO, GLFW_FALSE );
		glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_FALSE );
		glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
		glfwWindowHint( GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		glfwSwapInterval( GLFW_FALSE );

		auto* handle = glfwCreateWindow( 512, 512, "", nullptr, nullptr );

		if ( handle ) {
			glfwMakeContextCurrent( handle );

			window = (nPointer)handle;

			return true;
		}
	}

	return false;
}

bool GLFW::Create( Window& window, const nPointer ressources ) {
	glfwWindowHint( GLFW_VISIBLE, GLFW_TRUE );
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

	auto* handle = glfwCreateWindow( window.width, window.height, window.label, nullptr, (GLFWwindow*)ressources );

	if ( handle ) {
		glfwMakeContextCurrent( handle );

		window.handle = (nPointer)handle;
	}

	return handle;
}

void GLFW::SetContext( Window& window ) {
	glfwMakeContextCurrent( (GLFWwindow*)window.handle );
}

bool GLFW::ShouldRun( Window& window ) {
	return window.handle && !glfwWindowShouldClose( (GLFWwindow*)window.handle );
}

void GLFW::Process( Window& window ) {
	glfwSwapBuffers( (GLFWwindow*)window.handle );
	glfwPollEvents( );
}

void GLFW::Destroy( Window& window ) {
	if ( window.handle ) {
		glfwDestroyWindow( (GLFWwindow*)window.handle );
		window.handle = nullptr;
	}
}

void GLFW::Destroy( nPointer& window ) {
	if ( window ) {
		glfwDestroyWindow( (GLFWwindow*)window );
		window = nullptr;
	}
}

void GLFW::Cleanup( ) { glfwTerminate( ); }
