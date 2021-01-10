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

#ifndef _IGS_NUT_TEXT_STYLE_HPP_
#define _IGS_NUT_TEXT_STYLE_HPP_

	#include <LetheNut/Vendor/ImGUI.hpp>

	#include "NutTextParser.hpp"

	#define NUT_TEXT_STYLE( NAME ) class NUT_API NAME : public NutTextStyle

	struct NUT_API NutTextColor {

		ImColor foreground;
		ImColor background;

	};

	NUT_ELEMENT( NutTextStyle ) {

		using ColorMap = std::map<nUInt, NutTextColor>;

	private:
		mutable NutTextColor default_var;
		mutable ColorMap vars;

	public:
		NutTextStyle( nString name, const ImVec4& foreground, const ImVec4& background );

		NutTextStyle( nString name, const ImColor& foreground, const ImColor& background );

		virtual ~NutTextStyle( ) = default;

	protected:
		virtual void OnCreate( );

		void SetText( const ImVec4& color );

		void SetText( const ImColor& color );

		void SetBackground( const ImVec4& color );

		void SetBackground( const ImColor& color );

		void Set( nUInt query, const NutTextColor& color );

		inline void Set( nUInt query, const ImVec4& foreground, const ImVec4& background );

		inline void Set( nUInt query, const ImColor& foreground, const ImColor& background );

	public:
		ImVec4& GetText( ) const;

		ImVec4& GetBackground( ) const;

		NutTextColor& Get( ) const;
		
		NutTextColor& GetVar( nUInt query ) const;

	};

#endif
