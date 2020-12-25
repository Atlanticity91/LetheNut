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

#include <LetheNut/Utils/NutImage.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutImage::NutImage( )
{ }

NutImage::NutImage( NutHash hash, OpenGL::Texture texture, nUShort columns, nUShort rows )
	: hash( hash ),
	texture( texture ),
	sprite_count( columns * rows )
{ 
	if ( this->sprite_count > 1 ) {
		this->uvs.reserve( this->sprite_count );

		this->GenerateUV( columns, rows );
	} else
		this->sprite_count = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PRIVATE
///////////////////////////////////////////////////////////////////////////////////////////
void NutImage::GenerateUV( nUShort columns, nUShort rows ) {
	float sprite_width = 1.f / columns;
	float sprite_height = 1.f / rows;

	for ( auto ydx = 0; ydx < rows; ydx++ ) {
		for ( auto xdx = 0; xdx < columns; xdx++ ) {
			float spr_x = xdx * sprite_width;
			float spr_y = ydx * sprite_height;
			ImRect uv = ImRect{ spr_x, spr_y, sprite_width + spr_x, sprite_height + spr_y };

			this->uvs[ ydx * columns + xdx ] = uv;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutHash NutImage::GetHash( ) const { return this->hash; }

OpenGL::Texture& NutImage::GetTexture( ) const { return this->texture; }

ImTextureID NutImage::GetTextureID( ) const {
	nULong texture = this->texture.ID;

	return reinterpret_cast<ImTextureID>( texture );
}

const ImRect NutImage::GetSprite( nUInt index ) const {
	if ( index < this->sprite_count )
		return this->uvs[ index ];

	return ImRect{ 0.f, 0.f, 1.f, 1.f };
}

///////////////////////////////////////////////////////////////////////////////////////////
//     OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////
NutImage::operator OpenGL::Texture& ( ) const { return this->GetTexture( ); }

NutImage::operator ImTextureID( ) const { return this->GetTextureID( ); }

const ImRect NutImage::operator[]( nUInt index ) const {
	return this->GetSprite( index ); 
}
