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

#ifndef _IGS_NUT_KERNEL_HPP_
#define _IGS_NUT_KERNEL_HPP_

	#include "NutModule.hpp"
	#include <LetheNut/NutLibrary.hpp>
	#include <LetheNut/Vendor/JSON.hpp>
	#include <LetheNut/Vendor/OpenGL.hpp>
	#include <LetheNut/Vendor/STB.hpp>

	class NutMenuItem;
	class NutPanel;

	/**
	 * NutKernel final class [ NutModule ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Kernel module core class.
	 **/
	NUT_MODULE( NutKernel, final ) {
	
	private:
		nJSON config;
		STB::Image image_loader;
		std::vector<NutLibrary*> libraries;
		std::map<nString, OpenGL::Texture> images;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutKernel( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutKernel( );

		bool LoadImage( nString alias, nString path );

	protected:
		/**
		 * Initialize method
		 * @author : ALVES Quentin
		 * @note : Initialize the current kernel module.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Initialize( NutEditor* editor ) override;

		/**
		 * OnCreate override method
		 * @author : ALVES Quentin
		 * @note : On create the kernel module
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnCreate( NutEditor* editor ) override;

		/**
		 * Process override method
		 * @author : ALVES Quentin
		 * @note : Process the kernel module
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Process( NutEditor* editor ) override;

	private:
		/**
		 * LoadLibraries method
		 * @author : ALVES Quentin
		 * @note : Load all libraries of the editor.
		 * @param editor : Pointer to current editor.
		 **/
		void LoadLibraries( NutEditor* editor );

		/**
		 * LoadModules method
		 * @author : ALVES Quentin
		 * @note : Load all modules of the editor.
		 * @param editor : Pointer to current editor.
		 **/
		void LoadModules( NutEditor* editor );

	private:
		/**
		 * OnOpen static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Open button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnOpen( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnOpenScene static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Open Scene button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnOpenScene( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnLoad static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Load button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnLoad( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnSave static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Save button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnSave( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnImport static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Import button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnImport( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnExport static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Export button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnExport( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnOnExitSave static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Exit button from editor File menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnExit( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnUndo static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Undo button from editor Edit menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnUndo( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnRedo static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Redo button from editor Edit menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnRedo( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnCopy static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Copy button from editor Edit menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnCopy( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnCut static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Cut button from editor Edit menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnCut( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnPaste static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Paste button from editor Edit menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnPaste( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnTheme static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for Theme button from editor Preferences menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnTheme( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

		/**
		 * OnAbout static method
		 * @author : ALVES Quentin
		 * @note : Defined default callback for About button from editor Preferences menu.
		 * @param item : Reference of the item that use the callback.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		static void OnAbout( NutMenuItem& item, NutEditor* editor, NutPanel& parent );

	public:
		/**
		 * GetVersion inline const function
		 * @author : ALVES Quentin
		 * @note : Get current NutEditor version.
		 * @return : const std::string
		 **/
		inline const std::string GetVersion( ) const;

		/**
		 * GetLicense inline const function
		 * @author : ALVES Quentin
		 * @note : Get current NutEditor license.
		 * @return : const std::string
		 **/
		inline const std::string GetLicense( ) const;

		/**
		 * GetLibrary const function
		 * @author : ALVES Quentin
		 * @note : Get a library from current editor library list.
		 * @return : NutLibrary*
		 **/
		NutLibrary* GetLibrary( nString name ) const;

		const ImTextureID GetImage( nString name ) const;

	};

#endif
