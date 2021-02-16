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

	#include <LetheNut/Vendor/ImGUI.hpp>

	#include "NutPanel.hpp"

	#define NUT_WINDOW( NAME ) class NUT_API NAME : public NutWindow

	/**
	 * NutWindow class [ NutUIElement ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Window core class.
	 **/
	NUT_UI_ELEMENT( NutWindow ) {

		friend bool ImGUI::Window( NutWindow* );
		friend class NutEditor;

	private:
		mutable GLFW::Window window;
		mutable ImGuiContext* context;
		mutable NutList<NutPanel*> panels;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the window.
		 * @param width : Default width of the window.
		 * @param height : Default height of the window.
		 **/
		NutWindow( nString name, const nInt width, const nInt height );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutWindow( );

		/**
		 * Enable method
		 * @author : ALVES Quentin
		 * @note : Enable a panel.
		 * @param editor : Pointer to current editor.
		 * @param panel : Name of the panel to enable.
		 **/
		void Enable( NutEditor* editor, nString panel );

		/**
		 * Disable method
		 * @author : ALVES Quentin
		 * @note : Disable a panel.
		 * @param editor : Pointer to current editor.
		 * @param panel : Name of the panel to disable.
		 **/
		void Disable( NutEditor* editor, nString panel );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a panel.
		 * @param editor : Pointer to current editor.
		 * @param panel : Name of the panel to destroy.
		 **/
		void Destroy( NutEditor* editor, nString panel );

	protected:
		/**
		 * Open function
		 * @author : ALVES Quentin
		 * @note : Open the current window.
		 * @param ressources : OpenGL context used for ressources loading.
		 * @return : bool
		 **/
		bool Open( const nPointer ressources );

		/**
		 * OnCreate pure-virtual method
		 * @author : ALVES Quentin
		 * @note : Called once when the window is created.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnCreate( NutEditor* editor ) = 0;

		/**
		 * OnCreate function
		 * @author : ALVES Quentin
		 * @note : Called once when the window is destroyed.
		 * @param editor : Pointer to current editor.
		 * @return : bool
		 **/
		virtual bool OnDestroy( NutEditor* editor );

		/**
		 * OnRender method
		 * @author : ALVES Quentin
		 * @note : Called every tick when is active to render current window.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnRender( NutEditor* editor );

	public:
		/**
		 * Create template function
		 * @author : ALVES Quentin
		 * @note : Called every tick when is active to render current window.
		 * @template Type : Query instance of panel to create.
		 * @template Args : Arguments type capture.
		 * @param editor : Pointer to current editor.
		 * @param Args : Arguements for the panel contructor call.
		 * @return : Type*
		 **/
		template<typename Type = NutPanel, typename... Args>
		Type* Create( NutEditor* editor, Args... args );

	public:
		/**
		 * GetHandle const function
		 * @author : ALVES Quentin
		 * @note : Get current GLFW handle.
		 * @return : GLFW::Window&
		 **/
		GLFW::Window& GetHandle( ) const;

		/**
		 * GetContext const function
		 * @author : ALVES Quentin
		 * @note : Get current ImGui context.
		 * @return : const ImGuiContext*
		 **/
		const ImGuiContext* GetContext( ) const;

		/**
		 * ShouldRun const function
		 * @author : ALVES Quentin
		 * @note : Get if the current window should run.
		 * @return : bool
		 **/
		bool ShouldRun( ) const;

		/**
		 * GetPanels const function
		 * @author : ALVES Quentin
		 * @note : Get current window panel list.
		 * @return : NutList<NutPanel*>&
		 **/
		NutList<NutPanel*>& GetPanels( ) const;

		/**
		 * GetPanel const function
		 * @author : ALVES Quentin
		 * @note : Get a panel of current window panel list.
		 * @param name : Name of the query panel.
		 * @return : NutPanel*
		 **/
		NutPanel* GetPanel( nString name ) const;

	public:
		/**
		 * GetPanel const function
		 * @author : ALVES Quentin
		 * @note : Get a panel of current window panel list.
		 * @template Type : Query instance of panel to create.
		 * @param name : Name of the query panel.
		 * @return : Type*
		 **/
		template<typename Type = NutPanel>
		Type* GetPanel( nString panel );

	};

	#include <Templates/NutWindow.hpp>

#endif
