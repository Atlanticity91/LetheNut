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

#ifndef _IGS_NUT_TEXT_STYLE_HPP_
#define _IGS_NUT_TEXT_STYLE_HPP_

	#include <LetheNut/Utils/NutBasic.hpp>

	/**
	 * ENutTextStyleVars enum [ nUByte ]
	 * @author : ALVES Quentin
	 * @note : Defined default text editor style variable enumeration.
	 **/
	enum ENutTextStyleVars : nUByte {

		ETSV_DEFAULT,
		ETSV_LINECOUNT,
		ETSV_LINE,
		ETSV_SELECTION,
		ETSV_ERROR,

		ETSV_COMMENT,
		ETSV_PREPROCESSOR, 
		ETSV_PONCTUATION,
		ETSV_LITTERAL,
		ETSV_KEYWORD,
		ETSV_CONTROL,
		ETSV_TYPE,
		ETSV_MEMBER,

	};

	/**
	 * NutTextStyleVar struct
	 * @author : ALVES Quentin
	 * @note : Defined default text editor style variables.
	 **/
	union NutTextStyleVar {

		struct { 
			ImColor foreground;
			ImColor background;
		};
		struct {
			ImColor focus;
			ImColor unfocus;
		};

	};

	/**
	 * NutTextStyle class [ NutBasic ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Text Editor Style core class.
	 **/
	NUT_ELEMENT( NutTextStyle ) {

		using ColorBuilder = std::vector<float>;

	private:
		float line_space;
		std::map<ENutTextStyleVars, NutTextStyleVar> variables;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutTextStyle( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutTextStyle( );

		/**
		 * Set method
		 * @author : ALVES Quentin
		 * @note : Set the value of a style variable.
		 * @param query_var : Query style variable to set.
		 * @param background : Background color value.
		 * @param foreground : Foreground color value.
		 **/
		void Set( ENutTextStyleVars query_var, const ImColor& background, const ImColor& foreground );

		/**
		 * Set method
		 * @author : ALVES Quentin
		 * @note : Set the value of a style variable.
		 * @param query_var : Query style variable to set.
		 * @param background : Background color value.
		 * @param foreground : Foreground color value.
		 **/
		void Set( ENutTextStyleVars query_var, const ImColor&& background, const ImColor&& foreground );

		/**
		 * Set method
		 * @author : ALVES Quentin
		 * @note : Set the value of a style variable.
		 * @param query_var : Query style variable to set.
		 * @param builder : Float vector that contain the 8 channels values.
		 **/
		void Set( ENutTextStyleVars query_var, const ColorBuilder& builder );

		/**
		 * Set method
		 * @author : ALVES Quentin
		 * @note : Set the value of a style variable.
		 * @param query_var : Query style variable to set as string.
		 * @param builder : Float vector that contain the 8 channels values.
		 **/
		void Set( const std::string& query_var, const ColorBuilder & builder );

		/**
		 * SetLineSpacing method
		 * @author : ALVES Quentin
		 * @note : Set current style line spacing.
		 * @para spacing : New line spacing value.
		 **/
		void SetLineSpacing( float spacing );

		/**
		 * Convert virtual method
		 * @author : ALVES Quentin
		 * @note : Convert a string variable name to ENutTextStyleVars.
		 * @param query_var : Query style variable name.
		 * @return : ENutTextStyleVars
		 **/
		virtual ENutTextStyleVars Convert( const std::string & query_var );

	protected:
		/**
		 * Validate virtual method
		 * @author : ALVES Quentin
		 * @note : Validate the current style, adding default colors for unset varibles.
		 **/
		virtual void Validate( );

	public:
		/**
		 * GetBackground const function
		 * @author : ALVES Quentin
		 * @note : Get style editor background color.
		 * @return : const ImColor&
		 **/
		const ImColor& GetBackground( ) const;

		/**
		 * GetDefault const function
		 * @author : ALVES Quentin
		 * @note : Get style editor text color.
		 * @return : const ImColor&
		 **/
		const ImColor& GetDefault( ) const;

		/**
		 * GetLineSpacing const function
		 * @author : ALVES Quentin
		 * @note : Get style editor line spacing.
		 * @return : const float
		 **/
		const float GetLineSpacing( ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get a style variable value.
		 * @param query_var : Query style variable.
		 * @return : const NutTextStyleVar&
		 **/
		const NutTextStyleVar& Get( ENutTextStyleVars query_var ) const;

	public:
		/**
		 * operator[ ]
		 * @author : ALVES Quentin
		 * @note : Get a style variable value.
		 * @param query_var : Query style variable.
		 * @return : const NutTextStyleVar&
		 **/
		const NutTextStyleVar& operator[ ]( ENutTextStyleVars query_var ) const;

	};

#endif
