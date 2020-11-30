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

#ifndef _IGS_NUT_VENDOR_OPENGL_HPP_
#define _IGS_NUT_VENDOR_OPENGL_HPP_

	#include <LetheNut/Core.hpp>
	#include <Thirdparty/ImGUI/imgui.h>

	/**
	 * Graphics namspace
	 * @author : ALVES Quentin
	 * @note : Contain Graphics code wrapper.
	 **/
	namespace OpenGL {

		enum EParameterTypes : nUByte {

			EPT_INTEGER = 0,
			EPT_FLOATING,
			EPT_VECTOR2,
			EPT_VECTOR3,
			EPT_VECTOR4,
			EPT_MATRIX3,
			EPT_MATRIX4

		};

		enum EBufferTypes : nUByte {

			EBT_INDEX = 0,
			EBT_BUFFER,
			EBT_STORAGE,
			EBT_UNIFORM

		};

		enum EAttributeTypes : nUByte {

			EAT_BYTE = 0,
			EAT_INT,
			EAT_UNSIGNED_BYTE,
			EAT_UNSIGNED_INT,
			EAT_FLOAT

		};

		/**
		 * Context struct
		 * @author : ALVES Quentin
		 * @note : Graphic context representation.
		 **/
		struct Context {

			nInt FrameBuffer;
			nInt Width;
			nInt Height;
			nInt Material;

			Context( );

		};

		struct Frame { 
			
			nUInt ID;
			nUInt Width;
			nUInt Height;
			nUInt color;
			nUInt render;

			Frame( );

		};

		struct Texture {

			nUInt ID;
			nUInt Width;
			nUInt Height;

			Texture( );

		};

		struct Material {

			nUInt ID;
			nUInt Buffer;
			nUInt Fragment;
			nUInt Geometry;
			nUInt* Locations;

			Material( );

		};

		struct Buffer {

			nUInt ID;
			nUInt type;
			nUInt size;

			Buffer( );

		};

		struct Mesh {

			nUInt ID;
			nUInt stride;
			Buffer ibo;
			Buffer vbo;

			Mesh( );

		};

		bool Initialize( const nPointer& window );

		void Create( Context& context, const Frame& frame );

		bool Create( Frame& frame, const ImVec2& size );

		bool Create( Frame& frame, const ImVec2&& size );

		bool Create( Frame& frame, nUInt width, nUInt height );

		bool Create( Texture& texture, const ImVec2& size );
		
		bool Create( Texture& texture, const ImVec2&& size );

		bool Create( Texture& texture, nUInt width, nUInt height );
		
		bool Create( Material& material, nString vertex, nString fragment );

		bool Create( Material& material, nString vertex, nString fragment, nUInt size, nString* parameters );

		bool Create( Material& material, nString vertex, nString fragment, nString geometry );

		bool Create( Material& material, nString vertex, nString fragment, nString geometry, nUInt size, nString* parameters );

		bool Create( Buffer& vertex, EBufferTypes type, nUInt size );

		bool Create( Mesh& mesh, nUInt stride );

		bool IsValid( const Frame& frame );

		bool IsValid( const Texture& texture );

		bool IsValid( const Material& material );

		bool IsValid( const Buffer& vertex );

		bool IsValid( const Mesh& mesh );

		void Resize( Frame& frame, const ImVec2& size );

		void Resize( Frame& frame, const ImVec2&& size );

		void Resize( Frame& frame, nUInt width, nUInt height );

		void Refresh( const ImVec4& color );

		void Refresh( const ImVec4&& color );

		void Refresh( const Frame& frame, const ImVec4& color );

		void Refresh( const Frame& frame, const ImVec4&& color );

		void Fill( const Buffer& vertex, const nUInt size, const void* data );

		void Fill( const Buffer& vertex, const nUInt offset, const nUInt size, const void* data );

		void Attribute( const Mesh& mesh, const nUInt index, const nUInt size, EAttributeTypes type, const nULong offset );

		void Upload( const Material& material, nString parameter, EParameterTypes type, const void* data );

		void Bind( const Texture& texture, nUInt slot );

		void Bind( const Material& material );

		void Clear( );

		void Clear( const Frame& frame );

		void Display( const Material& material, const Mesh& mesh );

		void Display( const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		void Display( const Frame& frame, const Material& material, const Mesh& mesh );

		void Display( const Frame& frame, const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		void Destroy( Mesh& mesh );

		void Destroy( Buffer& vertex );

		void Destroy( Material& material );

		void Destroy( Texture& texture );

		void Destroy( Frame& frame );

		void Restore( const Context& context );

	};

#endif