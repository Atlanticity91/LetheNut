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

#ifndef _IGS_NUT_STYLE_HPP_
#define _IGS_NUT_STYLE_HPP_

	#include <LetheNut/Utils/NutBasic.hpp>
	#include <LetheNut/Vendor/ImGUI.hpp>

	/**
	 * NutStyleColor struct
	 * @author : ALVES Quentin
	 * @note : Defined style color.
	 **/
	struct NUT_API NutStyleColor {

		ImGuiCol_ target;
		ImVec4 value;

	};

	/**
	 * NutStyleRule struct
	 * @author : ALVES Quentin
	 * @note : Defined style rule.
	 **/
	struct NUT_API NutStyleRule {

		ImGuiStyleVar_ target;
		ImVec2 value;

	};

	/**
	 * NutStyle final class
	 * @author : ALVES Quentin
	 * @note : Define Nut Style core class.
	 **/
	NUT_ELEMENT( NutStyle, final ) {

		using ColorRef = std::optional< std::reference_wrapper< NutStyleColor > >;
		using RuleRef = std::optional< std::reference_wrapper< NutStyleRule > >;

	private:
		mutable std::vector< NutStyleColor > colors;
		mutable std::vector< NutStyleRule > rules;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the style.
		 **/
		NutStyle( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutStyle( ) = default;

	protected:
		/**
		 * SetColor method
		 * @author : ALVES Quentin
		 * @note : Edit or set the value of a color property.
		 * @param query : Query color property to edit.
		 * @param value : Value for the query color property.
		 **/
		void SetColor( ImGuiCol_ query, const ImVec4& value );

		/**
		 * SetColor method
		 * @author : ALVES Quentin
		 * @note : Edit or set the value of a color property.
		 * @param query : Query color property to edit.
		 * @param value : Value for the query color property.
		 **/
		void SetColor( ImGuiCol_ query, const ImVec4&& value );

		/**
		 * SetColor method
		 * @author : ALVES Quentin
		 * @note : Edit or set the value of a color property.
		 * @param query : Query color property to edit.
		 * @param red : Value for the query color red channel.
		 * @param green : Value for the query color green channel.
		 * @param blue : Value for the query color blue channel.
		 * @param alpha : Value for the query color alpha channel.
		 **/
		void SetColor( ImGuiCol_ query, const float red, const float green, const float blue, const float alpha );

		/**
		 * SetRule method
		 * @author : ALVES Quentin
		 * @note : Edit or set the value of a rule.
		 * @param query : Query rule to edit.
		 * @param x : X value for the rule.
		 * @param y : Y value for the rule.
		 **/
		void SetRule( ImGuiStyleVar_ query, float x, float y = 0.f );

		/**
		 * OnStyleInit virtual method
		 * @author : ALVES Quentin
		 * @note : Setup the current style.
		 **/
		virtual void OnStyleInit( );

	private:
		/**
		 * Apply method
		 * @author : ALVES Quentin
		 * @note : Apply the theme.
		 **/
		void Apply( );

	public:
		/**
		 * GetColors const function
		 * @author : ALVES Quentin
		 * @note : Get the list of color defined by the style.
		 * return : std::vector< NutStyleColor >&
		 **/
		std::vector< NutStyleColor >& GetColors( ) const;

		/**
		 * GetRules const function
		 * @author : ALVES Quentin
		 * @note : Get the list of rule defined by the style.
		 * @return : std::vector< NutStyleRule >&
		 **/
		std::vector< NutStyleRule >& GetRules( ) const;

		/**
		 * GetColor const function
		 * @author : ALVES Quentin
		 * @note : Get a color of the style.
		 * @param query : Query color.
		 * @return : ColorRef
		 **/
		ColorRef GetColor( ImGuiCol_ query ) const;

		/**
		 * GetRule const function
		 * @author : ALVES Quentin
		 * @note : Get a rule of the style.
		 * @param query : Query rule.
		 * @return : RuleRef
		 **/
		RuleRef GetRule( ImGuiStyleVar_ query ) const;

	};

#endif
