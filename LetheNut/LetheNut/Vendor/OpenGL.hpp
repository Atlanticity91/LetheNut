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

		/**
		 * EParameterTypes enum [ nUByte ]
		 * @author : ALVES Quentin
		 * @node : Defined all shader uploadable parameters types.
		 **/
		enum EParameterTypes : nUByte {

			EPT_INTEGER = 0,
			EPT_FLOATING,
			EPT_VECTOR2,
			EPT_VECTOR3,
			EPT_VECTOR4,
			EPT_MATRIX3,
			EPT_MATRIX4

		};

		/**
		 * EBufferTypes enum [ nUByte ]
		 * @author : ALVES Quentin
		 * @node : Defined all kind of buffer.
		 **/
		enum EBufferTypes : nUByte {

			EBT_INDEX = 0,
			EBT_BUFFER,
			EBT_STORAGE,
			EBT_UNIFORM

		};

		/**
		 * EAttributeTypes enum [ nUByte ]
		 * @author : ALVES Quentin
		 * @node : Defined all kind of attribute types.
		 **/
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

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Context( );

		};

		/**
		 * Frame struct
		 * @author : ALVES Quentin
		 * @note : Frame representation.
		 **/
		struct NUT_API Frame {

			nUInt ID;
			nUInt Width;
			nUInt Height;
			nUInt color;
			nUInt render;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Frame( );

		};

		/**
		 * Texture struct
		 * @author : ALVES Quentin
		 * @note : Texture representation.
		 **/
		struct NUT_API Texture {

			nUInt ID;
			nInt Width;
			nInt Height;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Texture( );

			/**
			 * Copy-Constructor
			 * @author : ALVES Quentin
			 * @param texture : Query texture to copy.
			 **/
			Texture( const Texture& texture );

		};

		/**
		 * Material struct
		 * @author : ALVES Quentin
		 * @note : Material representation.
		 **/
		struct NUT_API Material {

			nUInt ID;
			nUInt Buffer;
			nUInt Fragment;
			nUInt Geometry;
			nUInt* Locations;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Material( );

		};

		/**
		 * Buffer struct
		 * @author : ALVES Quentin
		 * @note : Buffer representation.
		 **/
		struct NUT_API Buffer {

			nUInt ID;
			nUInt type;
			nUInt size;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Buffer( );

		};

		/**
		 * Mesh struct
		 * @author : ALVES Quentin
		 * @note : Mesh representation.
		 **/
		struct NUT_API Mesh {

			nUInt ID;
			nUInt stride;
			Buffer ibo;
			Buffer vbo;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			Mesh( );

		};

		/**
		 * Initialize function
		 * @author : ALVES Quentin
		 * @note : Initialize OpenGL.
		 * @param editor : Current editor instance.
		 * @return : bool
		 **/
		NUT_API bool Initialize( NutEditor* editor );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Initialize OpenGL.
		 * @param context : Instance of context to store current context state.
		 * @param frame : Frame to bind.
		 **/
		NUT_API void Create( Context& context, const Frame& frame );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a frame.
		 * @param frame : Instance of context to store frame data.
		 * @param size : Query frame size.
		 **/
		NUT_API bool Create( Frame& frame, const ImVec2& size );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a frame.
		 * @param frame : Instance of context to store frame data.
		 * @param width : Query frame width.
		 * @param height : Query frame height.
		 **/
		NUT_API bool Create( Frame& frame, nUInt width, nUInt height );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a texture.
		 * @param texture : Instance of context to store texture data.
		 * @param size : Query texture size.
		 **/
		NUT_API bool Create( Texture& texture, const ImVec2& size );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a texture.
		 * @param texture : Instance of context to store texture data.
		 * @param width : Query texture width.
		 * @param height : Query texture height.
		 **/
		NUT_API bool Create( Texture& texture, nUInt width, nUInt height );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a texture.
		 * @param texture : Instance of context to store texture data.
		 * @param width : Query texture width.
		 * @param height : Query texture height.
		 * @param pixels : Query texture pixels.
		 **/
		NUT_API bool Create( Texture& texture, nUInt width, nUInt height, nUByte* pixels );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 * @param parameters : Query parameters array.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment, const std::vector<nString>& parameters );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 * @param size : Count of parameter.
		 * @param parameters : Query parameters array.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment, nUInt size, nString* parameters );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 * @param geometry : Query material geometry.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment, nString geometry );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 * @param geometry : Query material geometry.
		 * @param parameters : Query parameters array.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment, nString geometry, const std::vector<nString>& parameters );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a material.
		 * @param material : Instance of context to store material data.
		 * @param vertex : Query material vertex.
		 * @param fragment : Query material fragment.
		 * @param geometry : Query material geometry.
		 * @param size : Count of parameter.
		 * @param parameters : Query parameters array.
		 **/
		NUT_API bool Create( Material& material, nString vertex, nString fragment, nString geometry, nUInt size, nString* parameters );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a buffer.
		 * @param buffer : Instance of context to store buffer data.
		 * @param type : Query buffer type.
		 * @param size : Query buffer size.
		 **/
		NUT_API bool Create( Buffer& buffer, EBufferTypes type, nUInt size );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a mesh.
		 * @param mesh : Instance of context to store mesh data.
		 * @param stride : Query mesh stride.
		 **/
		NUT_API bool Create( Mesh& mesh, nUInt stride );

		/**
		 * IsValid function
		 * @author : ALVES Quentin
		 * @note : Get if a frame is valid.
		 * @param frame : Query frame.
		 * @return : bool
		 **/
		NUT_API bool IsValid( const Frame& frame );

		/**
		 * IsValid function
		 * @author : ALVES Quentin
		 * @note : Get if a texture is valid.
		 * @param frame : Query texture.
		 * @return : bool
		 **/
		NUT_API bool IsValid( const Texture& texture );

		/**
		 * IsValid function
		 * @author : ALVES Quentin
		 * @note : Get if a material is valid.
		 * @param frame : Query material.
		 * @return : bool
		 **/
		NUT_API bool IsValid( const Material& material );

		/**
		 * IsValid function
		 * @author : ALVES Quentin
		 * @note : Get if a buffer is valid.
		 * @param frame : Query buffer.
		 * @return : bool
		 **/
		NUT_API bool IsValid( const Buffer& buffer );

		/**
		 * IsValid function
		 * @author : ALVES Quentin
		 * @note : Get if a mesh is valid.
		 * @param frame : Query mesh.
		 * @return : bool
		 **/
		NUT_API bool IsValid( const Mesh& mesh );

		/**
		 * Resize method
		 * @author : ALVES Quentin
		 * @note : Resize a frame.
		 * @param frame : Query frame.
		 * @param size : New frame size.
		 **/
		NUT_API void Resize( Frame& frame, const ImVec2& size );

		/**
		 * Resize method
		 * @author : ALVES Quentin
		 * @note : Resize a frame.
		 * @param frame : Query frame.
		 * @param width : New frame width.
		 * @param height : New frame height.
		 **/
		NUT_API void Resize( Frame& frame, nUInt width, nUInt height );

		/**
		 * Refresh method
		 * @author : ALVES Quentin
		 * @note : Set current context refresh color.
		 * @param color : Query refresh color.
		 **/
		NUT_API void Refresh( const ImVec4& color );

		/**
		 * Refresh method
		 * @author : ALVES Quentin
		 * @note : Set current context refresh color.
		 * @param color : Query refresh color.
		 **/
		NUT_API void Refresh( const ImColor& color );

		/**
		 * Refresh method
		 * @author : ALVES Quentin
		 * @note : Set frame refresh color.
		 * @param frame : Query frame.
		 * @param color : Query refresh color.
		 **/
		NUT_API void Refresh( const Frame& frame, const ImVec4& color );

		/**
		 * Refresh method
		 * @author : ALVES Quentin
		 * @note : Set frame refresh color.
		 * @param frame : Query frame.
		 * @param color : Query refresh color.
		 **/
		NUT_API void Refresh( const Frame& frame, const ImColor& color );

		/**
		 * Fill method
		 * @author : ALVES Quentin
		 * @note : Fill a texture.
		 * @param texture : Query texture.
		 * @param pixels : Query pixels.
		 **/
		NUT_API void Fill( const Texture& texture, const void* pixels );

		/**
		 * Fill method
		 * @author : ALVES Quentin
		 * @note : Fill a texture.
		 * @param texture : Query texture.
		 * @param level : Query level.
		 * @param offset_x : Query offset_x.
		 * @param offset_y : Query offset_y.
		 * @param width : Query width.
		 * @param height : Query height.
		 * @param pixels : Query pixels.
		 **/
		NUT_API void Fill( const Texture& texture, nUInt level, nUInt offset_x, nUInt offset_y, nUInt width, nUInt height, const void* pixels );

		/**
		 * Fill method
		 * @author : ALVES Quentin
		 * @note : Fill a buffer.
		 * @param buffer : Query buffer.
		 * @param size : Query size.
		 * @param data : Query data.
		 **/
		NUT_API void Fill( const Buffer& buffer, const nUInt size, const void* data );

		/**
		 * Fill method
		 * @author : ALVES Quentin
		 * @note : Fill a buffer.
		 * @param buffer : Query buffer.
		 * @param offset : Query data offset.
		 * @param size : Query size.
		 * @param data : Query data.
		 **/
		NUT_API void Fill( const Buffer& buffer, const nUInt offset, const nUInt size, const void* data );

		/**
		 * Attribute method
		 * @author : ALVES Quentin
		 * @note : Create mesh attribute.
		 * @param mesh : Query mesh.
		 * @param index : Query index.
		 * @param size : Query size.
		 * @param type : Query type.
		 * @param offset : Query offset.
		 **/
		NUT_API void Attribute( const Mesh& mesh, const nUInt index, const nUInt size, EAttributeTypes type, const nULong offset );

		/**
		 * Upload method
		 * @author : ALVES Quentin
		 * @note : Upload parameter to shader.
		 * @param material : Query material.
		 * @param parameter : Query parameter name.
		 * @param type : Query parameter type.
		 * @param data : Query parameter data.
		 **/
		NUT_API void Upload( const Material& material, nString parameter, EParameterTypes type, const void* data );

		/**
		 * Bind method
		 * @author : ALVES Quentin
		 * @note : Bind	a texture.
		 * @param texture : Query texture.
		 * @param slot : Query textyre slot.
		 **/
		NUT_API void Bind( const Texture& texture, nUInt slot );

		/**
		 * Bind method
		 * @author : ALVES Quentin
		 * @note : Bind	a material.
		 * @param material : Query material.
		 **/
		NUT_API void Bind( const Material& material );

		/**
		 * Clear method
		 * @author : ALVES Quentin
		 * @note : Clear the current context.
		 **/
		NUT_API void Clear( );

		/**
		 * Clear method
		 * @author : ALVES Quentin
		 * @note : Clear a frame.
		 * @param frame : Query frame to clear.
		 **/
		NUT_API void Clear( const Frame& frame );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on current context.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 **/
		NUT_API void Display( const Material& material, const Mesh& mesh );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on current context.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 * @param textures : Query texture array.
		 **/
		NUT_API void Display( const Material& material, const Mesh& mesh, const std::vector<Texture>& textures );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on current context.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 * @param size : Count of texture to bind.
		 * @param textures : Query texture array.
		 **/
		NUT_API void Display( const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on a frame.
		 * @param frame : Query frame.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 **/
		NUT_API void Display( const Frame& frame, const Material& material, const Mesh& mesh );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on a frame.
		 * @param frame : Query frame.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 * @param textures : Query texture array.
		 **/
		NUT_API void Display( const Frame& frame, const Material& material, const Mesh& mesh, const std::vector<Texture>& textures );

		/**
		 * Display method
		 * @author : ALVES Quentin
		 * @note : Display a mesh on a frame.
		 * @param frame : Query frame.
		 * @param material : Query material.
		 * @param mesh : Query mesh.
		 * @param size : Count of texture to bind.
		 * @param textures : Query texture array.
		 **/
		NUT_API void Display( const Frame& frame, const Material& material, const Mesh& mesh, nUInt size, const Texture* textures );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a mesh.
		 * @param mesh : Query mesh.
		 **/
		NUT_API void Destroy( Mesh& mesh );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a buffer.
		 * @param mesh : Query buffer.
		 **/
		NUT_API void Destroy( Buffer& buffer );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a material.
		 * @param mesh : Query material.
		 **/
		NUT_API void Destroy( Material& material );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a texture.
		 * @param mesh : Query texture.
		 **/
		NUT_API void Destroy( Texture& texture );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a frame.
		 * @param mesh : Query frame.
		 **/
		NUT_API void Destroy( Frame& frame );

		/**
		 * Restore method
		 * @author : ALVES Quentin
		 * @note : Restore context.
		 * @param context : Query context.
		 **/
		NUT_API void Restore( const Context& context );

	};

#endif
