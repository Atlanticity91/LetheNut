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

#ifndef _IGS_NUT_WINDOW_HPP_
#define _IGS_NUT_WINDOW_HPP_

	#include "NutPopup.hpp"
	#include "NutStyle.hpp"

	#define NUT_WINDOW( NAME, ... ) NUT_CLASS( NAME, NutWindow, __VA_ARGS__ )
	#define MUT_VEC( TYPE, NAME ) mutable std::vector< TYPE * > NAME

	/**
	 * NutWindow class [ NutPopup ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Window core class.
	 **/
	NUT_POPUP( NutWindow ) {

		friend class NutEditor;

	private:
		mutable nPointer handle;
		MUT_CLASS( NutStyle, style );
		MUT_VEC( NutPopup, popups );

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current window.
		 * @param width : Width of the window.
		 * @param height : Height of the window.
		 **/
		NutWindow( nString label, const nUInt width, const nUInt height );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutWindow( );

	protected:
		/**
		 * OnCreate override method
		 * @author : ALVES Quentin
		 * @note : Called when the current panel is created.
		 **/
		virtual void OnCreate( NutEditor* editor ) override;

		/**
		 * OnEditorRender override method
		 * @author : ALVES Quentin
		 * @note : Called once a frame to render ImGUI stuff.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorRender( NutEditor* editor ) override;

		/**
		 * OnPopupRender method
		 * @author : ALVES Quentin
		 * @note : Render all popup's.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnPopupRender( NutEditor* editor );

	public:
		/**
		 * OpenPopup template function
		 * @author : ALVES Quentin
		 * @note : Open a popup.
		 * @template Type : Type of the query popup.
		 * @template Args : All type of arguments pass for popup constructor call.
		 * @param popup : Internal use to store the popup address.
		 * @param args : List of arguments for constructor call.
		 * @return : PopupType*
		 **/
		template< typename Type = class NutPopup, typename... Args >
		Type* OpenPopup( NutEditor* editor, Args... args );

		/**
		 * ClosePopup method
		 * @author : ALVES Quentin
		 * @note : Close a popup.
		 * @template Type : Type of the query popup.
		 **/
		template< typename Type = class NutPopup >
		void ClosePopup( );

	public:
		/**
		 * GetStyle inline const function
		 * @author : ALVES Quentin
		 * @note : Get current editor style.
		 * @return : class NutStyle&
		 **/
		inline class NutStyle& GetStyle( ) const;

		/**
		 * GetHandle inline const function
		 * @author : ALVES Quentin
		 * @note : Get current window GLFW window pointer.
		 * @return : nPointer&
		 **/
		inline nPointer& GetHandle( ) const;

	public:
		/**
		 * GetPopup const template function
		 * @author : ALVES Quentin
		 * @note : Get a popup by it's name.
		 * @template Type : Type of the query popup.
		 * @param name : Name of the query popup.
		 * @return : class NutPopup*
		 **/
		template< typename Type = class NutPopup >
		Type* GetPopup( ) const;

	};

	#include <Templates/NutWindow.hpp>

#endif
