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

#ifndef _IGS_NUT_BASIC_HPP_
#define _IGS_NUT_BASIC_HPP_

	#include <LetheNut/Core.hpp>

	#define NUT_ELEMENT( NAME, ... ) NUT_CLASS( NAME, NutBasic, __VA_ARGS__ )

	class NutEditor;

	/**
	 * NutBasic class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Basic core class.
	 **/
	class NUT_API NutBasic {

	private:
		NutHash hash;
		nString name;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current element.
		 **/
		NutBasic( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutBasic( ) = default;

	public:
		/**
		 * GetHash inline const function
		 * @author : ALVES Quentin
		 * @note : Get hash of the current element.
		 * @return : NutHash
		 **/
		inline NutHash GetHash( ) const;

		/**
		 * GetName inline const function
		 * @author : ALVES Quentin
		 * @note : Get the name of the current element.
		 * @return : nString
		 **/
		inline nString GetName( ) const;

	};

#endif
