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

	#include <LetheNut/Utils/NutElement.hpp>
	#include <LetheNut/Vendor/ImGUI.hpp>

	#define NUT_STYLE( NAME ) class NUT_API NAME : public NutStyle 

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
	 * NutStyleFont struct
	 * @author : ALVES Quentin
	 * @note : Defined style font.
	 **/
	struct NUT_API NutStyleFont {

		nString path;
		float size;

	};

	/**
	 * NutStyle final class
	 * @author : ALVES Quentin
	 * @note : Define Nut Style core class.
	 **/
	NUT_ELEMENT( NutStyle ) {

		friend class NutEditor;

		using ColorList = std::vector<NutStyleColor>;
		using RuleList = std::vector<NutStyleRule>;
		using FontList = std::vector<NutStyleFont>;
		using ColorRef = std::optional<std::reference_wrapper<NutStyleColor>>;
		using RuleRef = std::optional<std::reference_wrapper<NutStyleRule>>;

	private:
		bool has_changed;
		mutable ColorList colors;
		mutable RuleList rules;
		mutable FontList fonts;

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
		void SetColor( ImGuiCol_ query, const ImVec4 & value );

		/**
		 * SetColor method
		 * @author : ALVES Quentin
		 * @note : Edit or set the value of a color property.
		 * @param query : Query color property to edit.
		 * @param value : Value for the query color property.
		 **/
		void SetColor( ImGuiCol_ query, const ImVec4 && value );

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
		 * AddFont method
		 * @author : ALVES Quentin
		 * @note : Add font to current style.
		 * @param path : Path to font file.
		 * @param size : Size of the font.
		 **/
		void AddFont( nString path, float size );

		/**
		 * AddFont method
		 * @author : ALVES Quentin
		 * @note : Add font to current style.
		 * @param path : Path to font file.
		 * @param size : Size of the font.
		 **/
		inline void AddFont( const std::string& path, float size );

		/**
		 * OnStyleInit virtual method
		 * @author : ALVES Quentin
		 * @note : Setup the current style.
		 **/
		virtual void OnCreate( ) = 0;

	public:
		/**
		 * GetHasChanged const function
		 * @author : ALVES Quentin
		 * @note : Get if the style has changed.
		 * @preturn : bool
		 **/
		bool GetHasChanged( ) const;

		/**
		 * GetColors const function
		 * @author : ALVES Quentin
		 * @note : Get the list of color defined by the style.
		 * return : ColorList&
		 **/
		ColorList& GetColors( ) const;

		/**
		 * GetRules const function
		 * @author : ALVES Quentin
		 * @note : Get the list of rule defined by the style.
		 * @return : RuleList&
		 **/
		RuleList& GetRules( ) const;

		/**
		 * GetFonts const function
		 * @author : ALVES Quentin
		 * @note : Get the list of fonts defined by the style.
		 * @return : FontList&
		 **/
		FontList& GetFonts( ) const;

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
