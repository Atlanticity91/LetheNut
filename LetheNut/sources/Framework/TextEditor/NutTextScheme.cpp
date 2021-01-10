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
 * Copyright (C) 2021 ALVES Quentin.
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

#include <LetheNut/Framework/Editors/Text/NutTextScheme.hpp>

#define BACKGROUND ImColor{ 30, 30, 30, 255 }

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutTextScheme::NutTextScheme( )
	: NutTextStyle( "NutScheme", ImColor{ 200, 200, 200, 255 }, BACKGROUND )
{ }

///////////////////////////////////////////////////////////////////////////////////////////
//      PROTECTED
///////////////////////////////////////////////////////////////////////////////////////////
void NutTextScheme::OnCreate( ) {
	this->Set( NTCV_LINE_COUNT, BACKGROUND, ImColor{ 38, 143, 175, 255 } );
	this->Set( NTCV_LINE, BACKGROUND, ImColor{ 70,  70,  70, 255 } );
	this->Set( NTCV_SELECTION, ImColor{ 38,  79, 120, 255 }, ImColor{ 52,  52,  52, 255 } );
	this->Set( NTCV_COMMENT, BACKGROUND, ImColor{ 87, 166,  74, 255 } );
	this->Set( NTCV_WARNING, BACKGROUND, ImColor{ 32, 208,  32, 255 } );
	this->Set( NTCV_ERROR, ImColor{ 245,  61,  53, 255 }, ImColor{ 245, 229,  53, 255 } );
	this->Set( NTCV_MACRO, BACKGROUND, ImColor{ 155, 155, 155, 255 } );
	this->Set( NTCV_KEYWORD, BACKGROUND, ImColor{ 86, 156, 210, 255 } );
	this->Set( NTCV_LITTERAL, BACKGROUND, ImColor{ 128, 128,  32, 255 } );
	this->Set( NTCV_PONCTUATION, BACKGROUND, ImColor{ 255, 255, 0, 255 } );
	this->Set( NTCV_CONTROL_FLOW, BACKGROUND, ImColor{ 216, 160, 223, 255 } );
	this->Set( NTCV_MEMBER, ImColor{ 154, 154, 154, 255 }, ImColor{ 155, 219, 252, 255 } );
}
