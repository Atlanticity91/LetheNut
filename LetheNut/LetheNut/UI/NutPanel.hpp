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

	#include "NutUIElement.hpp"

	#define NUT_PANEL( NAME ) class NUT_API NAME : public NutPanel
	
	class NutWindow;

	/**
	 * NutPanel class [ NutUIElement ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Panel core class.
	 **/
	NUT_UI_ELEMENT( NutPanel ) {

		friend bool ImGUI::Panel( NutPanel* );
		friend class NutWindow;

	private:
		bool is_active;
		mutable ImVec2 padding;
		ImGuiWindowFlags flags;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the panel.
		 **/
		NutPanel( nString label );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the panel.
		 * @param flags : Flags of the panel.
		 **/
		NutPanel( nString label, ImGuiWindowFlags flags );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the panel.
		 * @param padding : Padding of the panel.
		 **/
		NutPanel( nString label, const ImVec2& padding );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the panel.
		 * @param padding : Padding of the panel.
		 * @param flags : Flags of the panel.
		 **/
		NutPanel( nString label, const ImVec2& padding, ImGuiWindowFlags flags );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutPanel( ) = default;

	protected:
		/**
		 * Enable method
		 * @author : ALVES Quentin
		 * @note : Enable the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		void Enable( NutEditor* editor, NutWindow* parent );

		/**
		 * Disable method
		 * @author : ALVES Quentin
		 * @note : Disable the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		void Disable( NutEditor* editor, NutWindow* parent );

		/**
		 * OnEnable method
		 * @author : ALVES Quentin
		 * @note : On enable the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		virtual void OnEnable( NutEditor* editor, NutWindow* parent );

		/**
		 * OnDisable method
		 * @author : ALVES Quentin
		 * @note : On disable the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		virtual void OnDisable( NutEditor* editor, NutWindow* parent );

		/**
		 * OnCreate pure-virtual method
		 * @author : ALVES Quentin
		 * @note : On create the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		virtual void OnCreate( NutEditor* editor, NutWindow* parent ) = 0;

		/**
		 * OnDestroy function
		 * @author : ALVES Quentin
		 * @note : On destroy the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 * @return : bool
		 **/
		virtual bool OnDestroy( NutEditor* editor, NutWindow* parent );

		/**
		 * OnProcess pure-virtual method
		 * @author : ALVES Quentin
		 * @note : On process the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		virtual void OnProcess( NutEditor* editor, NutWindow* parent ) = 0;

		/**
		 * OnRender pure-virtual method
		 * @author : ALVES Quentin
		 * @note : On render the current panel.
		 * @param editor : Pointer to current editor instance.
		 * @param parent : Current panel parent window.
		 **/
		virtual void OnRender( NutEditor* editor, NutWindow* parent ) = 0;

	public:
		/**
		 * GetIsActive const function
		 * @author : ALVES Quentin
		 * @note : Get current panel state.
		 * @return : bool
		 **/
		bool GetIsActive( ) const;

	private:
		/**
		 * GetFlags const function
		 * @author : ALVES Quentin
		 * @note : Get current panel flags.
		 * @return : ImGuiWindowFlags
		 **/
		ImGuiWindowFlags GetFlags( ) const;

		/**
		 * GetPadding const function
		 * @author : ALVES Quentin
		 * @note : Get current panel padding.
		 * @return : ImVec2&
		 **/
		ImVec2& GetPadding( ) const;

	public:
		/**
		 * [] const operator
		 * @author : ALVES Quentin
		 * @note : Get a menu of the current panel.
		 * @return : NutMenu*
		 **/
		NutMenu* operator[]( nString label ) const;

	};

#endif
