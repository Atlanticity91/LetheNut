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

#ifndef _IGS_NUT_OPENGL_HPP_
#define _IGS_NUT_OPENGL_HPP_

	#include <LetheNut/NutCore.hpp>

	class NutEditor;

	/**
	 * OpenGL namespace
	 * @author : ALVES Quentin
	 * @node : Wrapper for OpenGL.
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
		struct NUT_API Context {

			nInt FrameBuffer;
			nInt Width;
			nInt Height;
			nInt Material;

			Context( );

		};

		struct NUT_API Frame {

			nUInt ID;
			nUInt Width;
			nUInt Height;
			nUInt color;
			nUInt render;

			Frame( );

		};

		struct NUT_API Texture {

			nUInt ID;
			nInt Width;
			nInt Height;

			Texture( );

			Texture( const Texture& texture );

		};

		struct NUT_API Material {

			nUInt ID;
			nUInt Buffer;
			nUInt Fragment;
			nUInt Geometry;
			nUInt* Locations;

			Material( );

		};

		struct NUT_API Buffer {

			nUInt ID;
			nUInt type;
			nUInt size;

			Buffer( );

		};

		struct NUT_API Mesh {

			nUInt ID;
			nUInt stride;
			Buffer ibo;
			Buffer vbo;

			Mesh( );

		};

		NUT_API bool Initialize( NutEditor* editor );

		NUT_API void Create( Context& context, const Frame& frame );

		NUT_API bool Create( Frame& frame, const ImVec2& size );

		NUT_API bool Create( Frame& frame, nUInt width, nUInt height );

		NUT_API bool Create( Texture& texture, const ImVec2& size );

		NUT_API bool Create( Texture& texture, nUInt width, nUInt height );

		NUT_API bool Create( Texture& texture, nUInt width, nUInt height, nUByte* pixels );

		NUT_API bool Create( Material& material, nString vertex, nString fragment );

		NUT_API bool Create( Material& material, nString vertex, nString fragment, nUInt size, nString* parameters );

		NUT_API bool Create( Material& material, nString vertex, nString fragment, nString geometry );

		NUT_API bool Create( Material& material, nString vertex, nString fragment, nString geometry, nUInt size, nString* parameters );

		NUT_API bool Create( Buffer& vertex, EBufferTypes type, nUInt size );

		NUT_API bool Create( Mesh& mesh, nUInt stride );

		NUT_API bool IsValid( const Frame& frame );

		NUT_API bool IsValid( const Texture& texture );

		NUT_API bool IsValid( const Material& material );

		NUT_API bool IsValid( const Buffer& vertex );

		NUT_API bool IsValid( const Mesh& mesh );

		NUT_API void Resize( Frame& frame, const ImVec2& size );

		NUT_API void Resize( Frame& frame, nUInt width, nUInt height );

		NUT_API void Refresh( const ImVec4& color );

		NUT_API void Refresh( const ImColor& color );

		NUT_API void Refresh( const Frame& frame, const ImVec4& color );

		NUT_API void Refresh( const Frame& frame, const ImColor& color );

		NUT_API void Fill( const Texture& texture, const void* pixels );

		NUT_API void Fill( const Texture& texture, nUInt level, nUInt offset_x, nUInt offset_y, nUInt width, nUInt height, const void* pixels );

		NUT_API void Fill( const Buffer& vertex, const nUInt size, const void* data );

		NUT_API void Fill( const Buffer& vertex, const nUInt offset, const nUInt size, const void* data );

		NUT_API void Attribute( const Mesh& mesh, const nUInt index, const nUInt size, EAttributeTypes type, const nULong offset );

		NUT_API void Upload( const Material& material, nString parameter, EParameterTypes type, const void* data );

		NUT_API void Bind( const Texture& texture, nUInt slot );

		NUT_API void Bind( const Material& material );

		NUT_API void Clear( );

		NUT_API void Clear( const Frame& frame );

		NUT_API void Display( const Material& material, const Mesh& mesh );

		NUT_API void Display( const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		NUT_API void Display( const Frame& frame, const Material& material, const Mesh& mesh );

		NUT_API void Display( const Frame& frame, const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		NUT_API void Destroy( Mesh& mesh );

		NUT_API void Destroy( Buffer& vertex );

		NUT_API void Destroy( Material& material );

		NUT_API void Destroy( Texture& texture );

		NUT_API void Destroy( Frame& frame );

		NUT_API void Restore( const Context& context );

	};

#endif
