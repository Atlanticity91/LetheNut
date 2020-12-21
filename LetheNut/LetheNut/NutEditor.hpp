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

#ifndef _IGS_NUT_EDITOR_HPP_
#define _IGS_NUT_EDITOR_HPP_

	#include "Modules/NutKernel.hpp"
	#include "UI/NutWindow.hpp"
	#include "Vendor/OpenGL.hpp"

	// TODO : NutTextEditor
	// TODO : NutNodeEditor
	// TODO : NutSpriteEditor
	// TODO : NutFrameEditor
	// TODO : NutMaterialEditor
	// TODO : NutParticleEditor
	// TODO : Use Hash instead of string for labels.
	// TODO : FIX Imgui support for multiple windows.
	// TODO : FIX Sliders
	// TODO : FIX Custom Theme

	/**
	 * NutEditor final class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Editor core class.
	 **/
	NUT_WINDOW( NutEditor, final ) {
		
		friend class NutKernel;
		friend int main( int, char** );

	private:
		MUT_VEC( NutModule, modules );
		MUT_VEC( NutWindow, windows );

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutEditor( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutEditor( );

		/**
		 * EnableModule method
		 * @author : ALVES Quentin
		 * @note : Enable a module.
		 * @param name : Name of the query module.
		 **/
		void EnableModule( nString name );

		/**
		 * DisableModule method
		 * @author : ALVES Quentin
		 * @note : Disable a module.
		 * @param name : Name of the query module.
		 **/
		void DisableModule( nString name );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy a module.
		 * @param name : Name of the query module.
		 **/
		void Destroy( nString name );

		/**
		 * Exit method
		 * @author : ALVES Quentin
		 * @note : Exit the editor.
		 **/
		void Exit( );

	protected:
		/**
		 * OnCreate override method
		 * @author : ALVES Quentin
		 * @note : Called when the current panel is created.
		 **/
		virtual void OnCreate( class NutEditor* editor ) override;

		/**
		 * Start function
		 * @author : ALVES Quentin
		 * @note : Start the editor.
		 * @param argc : Count of argument.
		 * @param argv : Value for argument.
		 **/
		bool Start( int argc, char** argv );

		/**
		 * Run method
		 * @author : ALVES Quentin
		 * @note : Run the editor.
		 **/
		void Run( );

	public:
		/**
		 * Register template function
		 * @author : ALVES Quentin
		 * @note : Register a module.
		 * @template Type : Type of the query moduke.
		 * @template Args : All type of arguments pass for popup constructor call.
		 * @param args : List of arguments for constructor call.
		 * @return : Type*
		 **/
		template< typename Type = class NutModule, typename... Args >
		Type* Register( Args... args );

		/**
		 * Create template function
		 * @author : ALVES Quentin
		 * @note : Create a new window.
		 * @template Type : Instance of NutWindow of the new window.
		 * @template Args : Variadic template for arguments pass to window constructor.
		 * @param args : 
		 * @return : Type*
		 **/
		template< typename Type = class NutWindow, typename... Args >
		Type* Create( Args... args );

	public:
		/**
		 * GetKernel inline const function
 		 * @author : ALVES Quentin
		 * @note : Get current kernel module.
		 * @return : NutKernel*
		 **/
		inline NutKernel* GetKernel( ) const;

		/**
		 * GetLibrary inline const function
		 * @author : ALVES Quentin
		 * @note : Get a library from library list.
		 * @param name : Name of the query library.
		 * @return : NutLibrary*
		 **/
		inline NutLibrary* GetLibrary( nString name ) const;

	private:
		/**
		 * GetModules inline const function
		 * @author : ALVES Quentin
		 * @note : Get reference to module list.
		 * @return : const std::vector< NutModule* >&
		 **/
		inline std::vector< NutModule* >& GetModules( ) const;

	public:
		template< typename Type = NutTool >
		Type* GetTool( nString name ) const;

		/**
		 * GetModule template const function
		 * @author : ALVES Quentin
		 * @note : Get a module from module list.
		 * @template Type : Type of the query module.
		 * @param name : Name of the query module.
		 * @return : Type*
		 **/
		template< typename Type = NutModule >
		Type* GetModule( nString name ) const;

		/**
		 * GetWindow template const function
		 * @author : ALVES Quentin
		 * @note : Get a window from window list.
		 * @template Type : Type of the query window.
		 * @param name : Name of the query window.
		 * @return : Type*
		 **/
		template< typename Type = NutWindow >
		Type* GetWindow( nString name ) const;

	};

	#include <Templates/NutEditor.hpp>

#endif
