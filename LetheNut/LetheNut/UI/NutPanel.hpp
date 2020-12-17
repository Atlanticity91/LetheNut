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

#ifndef _IGS_NUT_PANEL_HPP_
#define _IGS_NUT_PANEL_HPP_

	#include "NutMenu.hpp"
	#include <LetheNut/Vendor/OpenGL.hpp>

	#define NUT_PANEL( NAME, ... ) NUT_CLASS( NAME, NutPanel, __VA_ARGS__ )

	/**
	 * NutPanel class
	 * @author : ALVES Quentin
	 * @note : Define Nut Panel core class.
	 **/
	NUT_ELEMENT( NutPanel ) {

		friend class NutPopup;
		friend class NutEditor;

	private:
		mutable bool is_active;
		mutable ImVec2 padding;
		mutable std::vector< class NutMenu > menus;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current panel.
		 * @param is_active : Defined if the current panel is active by default.
		 **/
		NutPanel( nString name, bool is_active, const ImVec2& padding );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current panel.
		 * @param is_active : Defined if the current panel is active by default.
		 **/
		NutPanel( nString name, bool is_active, const ImVec2 && padding );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutPanel( ) = default;

		/**
		 * Enable virtual function
		 * @author : ALVES Quentin
		 * @note : Enable the current panel.
		 * @return : class NutPanel*
		 **/
		virtual class NutPanel* Enable( );

		/**
		 * Disable virtual function
		 * @author : ALVES Quentin
		 * @note : Disable the current panel.
		 * @return : class NutPanel*
		 **/
		virtual class NutPanel* Disable( );

		/**
		 * CreateMenu function
		 * @author : ALVES Quentin
		 * @note : Create a menu for the current panel.
		 * @param name : Name for the new menu.
		 * @return : class NutMenu*
		 **/
		class NutMenu* CreateMenu( nString name );

	protected:
		/**
		 * OnCreate virtual method
		 * @author : ALVES Quentin
		 * @note : Called when the current panel is created.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnCreate( NutEditor* editor );

		/**
		 * OnEditorRender virtual method
		 * @author : ALVES Quentin
		 * @note : Called once a frame to render ImGUI stuff.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorRender( NutEditor* editor );

	public:
		/**
		 * IsActive inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current panel is active.
		 * @return : bool
		 **/
		inline bool GetIsActive( ) const;

		/**
		 * GetPadding inline const function
		 * @author : ALVES Quentin
		 * @note : Get the current panel padding.
		 * @return : const ImVec2&
		 **/
		inline const ImVec2& GetPadding( ) const;

		/**
		 * GetMenu const function
		 * @author : ALVES Quentin
		 * @note : Cet a menu of the current panel by is name.
		 * @param name : Name of the query panel.
		 * @return : class NutMenu*
		 **/
		class NutMenu* GetMenu( nString name ) const;

	};

#endif
