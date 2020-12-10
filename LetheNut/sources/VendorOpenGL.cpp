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

#include <LetheNut/Vendor/OpenGL.hpp>
#include <Thirdparty/GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL 
///////////////////////////////////////////////////////////////////////////////////////////
bool internal_CreateRender( nUInt& render, const nUInt width, const nUInt height ) {
	glGenRenderbuffers( 1, &render );

	if ( render > 0 ) {
		glBindRenderbuffer( GL_RENDERBUFFER, render );
		glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height );
	}

	return render > 0;
}

bool internal_CreateTexture( nUInt& texture, const nUInt width, const nUInt height ) {
	glCreateTextures( GL_TEXTURE_2D, 1, &texture );

	if ( texture > 0 ) {
		glBindTexture( GL_TEXTURE_2D, texture );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	return texture > 0;
}

nUInt internal_CreateShader( nInt type, nString source ) {
	if ( type && source && strlen( source ) > 0 ) {
		nUInt source_id = glCreateShader( type );

		glShaderSource( source_id, 1, &source, nullptr );
		glCompileShader( source_id );

		return source_id;
	}

	return 0;
}

nUInt internal_BufferType( nUByte type ) {
	switch ( type ) {
		case OpenGL::EBufferTypes::EBT_INDEX : return GL_ELEMENT_ARRAY_BUFFER;
		case OpenGL::EBufferTypes::EBT_BUFFER : return GL_ARRAY_BUFFER;
		case OpenGL::EBufferTypes::EBT_STORAGE : return GL_SHADER_STORAGE_BUFFER;
		case OpenGL::EBufferTypes::EBT_UNIFORM : return GL_UNIFORM_BUFFER;

		default: break;
	}

	return 0;
}

nUInt internal_AttributeType( nUByte type ) {
	switch ( type ) {
		case OpenGL::EAttributeTypes::EAT_BYTE : return GL_BYTE;
		case OpenGL::EAttributeTypes::EAT_INT : return GL_INT;
		case OpenGL::EAttributeTypes::EAT_UNSIGNED_BYTE : return GL_UNSIGNED_BYTE;
		case OpenGL::EAttributeTypes::EAT_UNSIGNED_INT : return GL_UNSIGNED_INT;
		case OpenGL::EAttributeTypes::EAT_FLOAT : return GL_FLOAT;

		default: break;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
OpenGL::Context::Context( )
	: FrameBuffer( 0 ),
	Width( 0 ), 
	Height( 0 ),
	Material( 0 )
{ }

OpenGL::Frame::Frame( )
	: ID( 0 ),
	Width( 0 ),
	Height( 0 ),
	color( 0 ),
	render( 0 ) 
{ }

OpenGL::Texture::Texture( )
	: ID( 0 ),
	Width( 0 ),
	Height( 0 )
{ }

OpenGL::Material::Material( )
	: ID( 0 ),
	Buffer( 0 ),
	Fragment( 0 ),
	Geometry( 0 ),
	Locations( nullptr )
{ }

OpenGL::Buffer::Buffer( )
	: ID( 0 ),
	type( 0 ),
	size( 0 )
{ }

OpenGL::Mesh::Mesh( )
	: ID( 0 ),
	stride( 0 ),
	ibo( ),
	vbo( )
{ }

bool OpenGL::Initialize( const nPointer& window ) {
	if ( glewInit( ) == GLEW_OK ) {
		nInt width, height;

		glfwGetWindowSize( (struct GLFWwindow*)window, &width, &height );
		glViewport( 0, 0, width, height );

		return true;
	}

	return false;
}

void OpenGL::Create( Context& context, const Frame& frame ) {
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, &context.FrameBuffer );

	GLint dims[ 4 ] = { 0 };
	glGetIntegerv( GL_VIEWPORT, dims );
	context.Width = dims[ 2 ];
	context.Height = dims[ 3 ];

	glGetIntegerv( GL_CURRENT_PROGRAM, &context.Material );

	if ( OpenGL::IsValid( frame ) ) {
		glBindFramebuffer( GL_FRAMEBUFFER, frame.ID );
		glViewport( 0, 0, frame.Width, frame.Height );
	}
}

bool OpenGL::Create( Frame& frame, const ImVec2& size ) { 
	return OpenGL::Create( frame, (nUInt)size.x, (nUInt)size.y ); 
}

bool OpenGL::Create( Frame& frame, const ImVec2&& size ) { 
	return OpenGL::Create( frame, (nUInt)size.x, (nUInt)size.y ); 
}

bool OpenGL::Create( Frame& frame, nUInt width, nUInt height ) {
	glCreateFramebuffers( 1, &frame.ID );

	if ( OpenGL::IsValid( frame ) ) {
		if ( 
			internal_CreateTexture( frame.color, width, height ) && 
			internal_CreateRender( frame.render, width, height ) 
		) {
			glBindFramebuffer( GL_FRAMEBUFFER, frame.ID );
			glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame.color, 0 );
			glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frame.render );

			GLenum DrawBuffers[ 2 ] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT };
			glDrawBuffers( 2, DrawBuffers );
		}

		if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			glDeleteFramebuffers( 1, &frame.ID );

		glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	}

	return OpenGL::IsValid( frame );
}

bool OpenGL::Create( Texture& texture, const ImVec2& size ) {
return OpenGL::Create( texture, (nUInt)size.x, (nUInt)size.y );
}

bool OpenGL::Create( Texture& texture, const ImVec2&& size ) {
	return OpenGL::Create( texture, (nUInt)size.x, (nUInt)size.y );
}

bool OpenGL::Create( Texture& texture, nUInt width, nUInt height ) {
	if ( internal_CreateTexture( texture.ID, width, height ) ) {
		texture.Width = width;
		texture.Height = height;
	}

	return OpenGL::IsValid( texture );
}

bool OpenGL::Create( Material& material, nString vertex, nString fragment ) {
	return OpenGL::Create( material, vertex, fragment, nullptr );
}

bool OpenGL::Create( Material& material, nString vertex, nString fragment, nUInt size, nString* parameters ) {
	return OpenGL::Create( material, vertex, fragment, nullptr, size, parameters );
}

bool OpenGL::Create( Material& material, nString vertex, nString fragment, nString geometry ) {
	material.ID = glCreateProgram( );

	if ( OpenGL::IsValid( material ) ) {
		material.Buffer = internal_CreateShader( GL_VERTEX_SHADER, vertex );
		material.Fragment = internal_CreateShader( GL_FRAGMENT_SHADER, fragment );
		material.Geometry = internal_CreateShader( GL_GEOMETRY_SHADER, geometry );

		glAttachShader( material.ID, material.Buffer );
		glAttachShader( material.ID, material.Fragment );
		glAttachShader( material.ID, material.Geometry );

		glLinkProgram( material.ID );

		glDetachShader( material.ID, material.Buffer );
		glDetachShader( material.ID, material.Fragment );
		glDetachShader( material.ID, material.Geometry );
	}

	return OpenGL::IsValid( material );
}

bool OpenGL::Create( Material& material, nString vertex, nString fragment, nString geometry, nUInt size, nString* parameters ) {
	if ( OpenGL::Create( material, vertex, fragment, nullptr ) && size > 0 && parameters ) {
		material.Locations = nHelper::Alloc<nUInt>( size );
		
		if ( material.Locations ) {
			glUseProgram( material.ID );

			while ( size > 0 ) {
				size -= 1;

				material.Locations[ size ] = glGetUniformLocation( material.ID, parameters[ size ] );
			}

			glUseProgram( 0 );
		}
	}

	return OpenGL::IsValid( material );
}

bool OpenGL::Create( Buffer& vertex, EBufferTypes type, nUInt size ) {
	glCreateBuffers( 1, &vertex.ID );

	if ( OpenGL::IsValid( vertex ) ) {
		vertex.type = internal_BufferType( type );
		vertex.size = size;

		glBindBuffer( vertex.type, vertex.ID );
		glBufferData( vertex.type, size, nullptr, GL_DYNAMIC_DRAW );
	}

	return OpenGL::IsValid( vertex );
}

bool OpenGL::Create( Mesh& mesh, nUInt stride ) {
	if ( OpenGL::IsValid( mesh.ibo ) && OpenGL::IsValid( mesh.vbo ) ) {
		glCreateVertexArrays( 1, &mesh.ID );

		if ( OpenGL::IsValid( mesh ) ) {
			mesh.stride = stride;

			glBindVertexArray( mesh.ID );
			glBindBuffer( mesh.ibo.type, mesh.ibo.ID );
			glBindBuffer( mesh.vbo.type, mesh.vbo.ID );
			glBindVertexArray( 0 );
		}
	}

	return OpenGL::IsValid( mesh );
}

bool OpenGL::IsValid( const Frame& frame ) { return frame.ID > 0; }

bool OpenGL::IsValid( const Texture& texture ) { return texture.ID > 0; }

bool OpenGL::IsValid( const Material& material ) { return material.ID > 0; }

bool OpenGL::IsValid( const Buffer& vertex ) { return vertex.ID > 0; }

bool OpenGL::IsValid( const Mesh& mesh ) { return mesh.ID > 0; }

void OpenGL::Resize( Frame& frame, const ImVec2& size ) {
	OpenGL::Resize( frame, (nUInt)size.x, (nUInt)size.y );
}

void OpenGL::Resize( Frame& frame, const ImVec2&& size ) {
	OpenGL::Resize( frame, (nUInt)size.x, (nUInt)size.y );
}

void OpenGL::Resize( Frame& frame, nUInt width, nUInt height ) {
	if ( OpenGL::IsValid( frame ) ) {
		OpenGL::Destroy( frame );
		OpenGL::Create( frame, width, height );
	}
}

void OpenGL::Refresh( const ImVec4& color ) { glClearColor( color.x, color.y, color.z, color.w ); }

void OpenGL::Refresh( const ImVec4&& color ) { OpenGL::Refresh( color ); }

void OpenGL::Refresh( const Frame& frame, const ImVec4& color ) {
	if ( OpenGL::IsValid( frame ) ) {
		OpenGL::Context context;

		OpenGL::Create( context, frame );
		glClearColor( color.x, color.y, color.z, color.w );
		OpenGL::Restore( context );
	}
}

void OpenGL::Refresh( const Frame& frame, const ImVec4&& color ) { OpenGL::Refresh( frame, color ); }

void OpenGL::Fill( const Buffer& vertex, const nUInt size, const void* data ) { OpenGL::Fill( vertex, 0, size, data ); }

void OpenGL::Fill( const Buffer& vertex, const nUInt offset, const nUInt size, const void* data ) {
	if ( OpenGL::IsValid( vertex ) && size > 0 && data ) {
		glBindBuffer( vertex.type, vertex.ID );
		glBufferSubData( vertex.type, offset, size, data );
		glBindBuffer( vertex.type, 0 );
	}
}

void OpenGL::Attribute( const Mesh& mesh, const nUInt index, const nUInt size, EAttributeTypes type, const nULong offset ) {
	if ( OpenGL::IsValid( mesh ) ) {
		glBindVertexArray( mesh.ID );
		glVertexAttribPointer( index, size, internal_AttributeType( type ), GL_FALSE, mesh.stride, (const void*)offset );
		glEnableVertexAttribArray( index );
		glBindVertexArray( 0 );
	}
}

void OpenGL::Upload( const Material& material, nString parameter, EParameterTypes type, const void* data ) {
	if ( OpenGL::IsValid( material ) && parameter && strlen( parameter ) > 0 && data ) {

	}
}

void OpenGL::Bind( const Texture& texture, nUInt slot ) {
	if ( OpenGL::IsValid( texture ) )
		glBindTextureUnit( slot, texture.ID );
}

void OpenGL::Bind( const Material& material ) {
	if ( OpenGL::IsValid( material ) )
		glUseProgram( material.ID );
}

void OpenGL::Clear( ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
}

void OpenGL::Clear( const Frame& frame ) {
	if ( OpenGL::IsValid( frame ) ) {
		OpenGL::Context context;

		OpenGL::Create( context, frame );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
		OpenGL::Restore( context );
	}
}

void OpenGL::Display( const Material& material, const Mesh& mesh ) {
	if ( OpenGL::IsValid( material ) && OpenGL::IsValid( mesh ) ) {
		glBindVertexArray( mesh.ID );
		glUseProgram( material.ID );
		glDrawElements( GL_TRIANGLES, mesh.ibo.size / sizeof( nUInt ), GL_UNSIGNED_INT, nullptr );
		glBindVertexArray( 0 );
	}
}

void OpenGL::Display( const Material& material, const Mesh& mesh, nUInt size, const Texture* textures ) {
	if ( size > 0 && textures ) {
		while ( size > 0 ) {
			size -= 1;

			if ( OpenGL::IsValid( textures[ size ] ) )
				glBindTextureUnit( size, textures[ size ].ID );
		}
	}

	OpenGL::Display( material, mesh );
}

void OpenGL::Display( const Frame& frame, const Material& material, const Mesh& mesh ) {
	OpenGL::Display( frame, material, mesh, 0, nullptr );
}

void OpenGL::Display( const Frame& frame, const Material& material, const Mesh& mesh, nUInt size, const Texture* textures ) {
	OpenGL::Context context;

	OpenGL::Create( context, frame );
	OpenGL::Display( material, mesh, size, textures );
	OpenGL::Restore( context );
}

void OpenGL::Destroy( Mesh& mesh ) {
	if ( OpenGL::IsValid( mesh ) ) {
		glDeleteFramebuffers( 1, &mesh.ID );

		OpenGL::Destroy( mesh.ibo );
		OpenGL::Destroy( mesh.vbo );

		mesh.ID = 0;
	}
}

void OpenGL::Destroy( Buffer& vertex ) {
	if ( OpenGL::IsValid( vertex ) ) {
		glDeleteBuffers( 1, &vertex.ID );

		vertex.ID = 0;
	}
}

void OpenGL::Destroy( Material& material ) {
	if ( OpenGL::IsValid( material ) ) {
		glDeleteProgram( material.ID );
		glDeleteShader( material.Buffer );
		glDeleteShader( material.Fragment );
		glDeleteShader( material.Geometry );

		if ( material.Locations ) {
			free( material.Locations );

			material.Locations = nullptr;
		}

		material.ID = 0;
	}
}

void OpenGL::Destroy( Texture& texture ) {
	if ( OpenGL::IsValid( texture ) ) {
		glDeleteTextures( 1, &texture.ID );

		texture.ID = 0;
	}
}

void OpenGL::Destroy( Frame& frame ) {
	if ( OpenGL::IsValid( frame ) ) {
		glDeleteFramebuffers( 1, &frame.ID );

		frame.ID = 0;
	}
}

void OpenGL::Restore( const Context& context ) {
	glBindFramebuffer( GL_FRAMEBUFFER, context.FrameBuffer );
	glViewport( 0, 0, context.Width, context.Height );
	glUseProgram( context.Material );
}
