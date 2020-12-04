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

#ifndef _IGS_NUT_TEXT_PARSER_HPP_
#define _IGS_NUT_TEXT_PARSER_HPP_

	#include "NutTextStyle.hpp"

	/**
	 * NutTextParser class [ NutBasic ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Text Editor Style core class.
	 **/
	NUT_ELEMENT( NutTextParser ) {

		using StringList = std::vector<std::string>;

	protected:
		nUInt last_char;
		char result[ 4096 ];
		std::map<ENutTextStyleVars, StringList> tables;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the parser.
		 **/
		NutTextParser( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutTextParser( );

		/**
		 * Parse virtual method
		 * @author : ALVES Quentin
		 * @note : Parse text.
		 * @param input : Query text to parse.
		 **/
		virtual void Parse( const std::string& input );

	protected:
		/**
		 * Validate virtual method
		 * @author : ALVES Quentin
		 * @note : Validate the current style, adding default colors for unset varibles.
		 **/
		virtual void Validate( );

	protected:
		/**
		 * Register template method
		 * @author : ALVES Quentin
		 * @note : Validate the current style, adding default colors for unset varibles.
		 * @template args : Capture all strings.
		 * @param variable : Query style variable.
		 * @param args : Value for arguments.
		 **/
		template< typename... Args >
		void Register( ENutTextStyleVars variable, Args... args );

	public:
		/**
		 * GetNext function
		 * @author : ALVES Quentin
		 * @note : Validate the current style, adding default colors for unset varibles.
		 * @param style : Style variable to set.
		 * @param text : Text variable to set.
		 * @return : bool
		 **/
		bool GetNext( ENutTextStyleVars& style, nString& text );

	private:
		/**
		 * FindSyntax function
		 * @author : ALVES Quentin
		 * @note : Find style variable from text.
		 * @param text : Find syntax for text.
		 * @return : ENutTextStyleVars
		 **/
		ENutTextStyleVars FindSyntax( nString text );

	};

	#include <Templates/NutTextParser.hpp>

#endif
