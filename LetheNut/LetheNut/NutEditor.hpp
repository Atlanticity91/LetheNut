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

	#include "NutFramework.hpp"
	#include "Assets/NutAssetManager.hpp"
	#include "Utils/NutLibrary.hpp"
	#include "Utils/NutModule.hpp"
	#include "Vendor/JSON.hpp"

	/**
	 * NutEditor final class
	 * @author : ALVES Quentin
	 * @note : Defined editor core class.
	 **/
	class NUT_API NutEditor final {

		friend int main( int argc, char** argv );

	private:
		bool is_running;
		mutable NutFileSystem file_system;
		mutable NutAssetManager assets;
		NutLogger logger;
		JSON config;
		NutStyle* style;
		NutList<NutLibrary*> libraries;
		NutList<NutModule*> modules;
		NutList<NutWindow*> windows;

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
		 * LoadLibrary function
		 * @author : ALVES Quentin
		 * @note : Load a library to the editor.
		 * @param path : Path to the query library file.
		 * @return : bool 
		 **/
		bool LoadLibrary( nString path );

		/**
		 * LoadLibrary function
		 * @author : ALVES Quentin
		 * @note : Load a library to the editor.
		 * @param path : Path to the query library file.
		 * @return : bool
		 **/
		inline bool LoadLibrary( const std::string& path );

		/**
		 * LoadModule function
		 * @author : ALVES Quentin
		 * @note : Load a module to the editor.
		 * @param path : Path to the query module file.
		 * @return : bool
		 **/
		bool LoadModule( nString path );

		/**
		 * LoadModule function
		 * @author : ALVES Quentin
		 * @note : Load a module to the editor.
		 * @param path : Path to the query module file.
		 * @return : bool
		 **/
		inline bool LoadModule( const std::string& path );

		/**
		 * UnLoadLibrary function
		 * @author : ALVES Quentin
		 * @note : UnLoad a library from the editor.
		 * @param name : Name to the query library.
		 * @return : bool
		 **/
		void UnLoadLibrary( nString name );

		/**
		 * UnLoadLibrary function
		 * @author : ALVES Quentin
		 * @note : UnLoad a library from the editor.
		 * @param name : Name to the query library.
		 * @return : bool
		 **/
		inline void UnLoadLibrary( const std::string& path );

		/**
		 * UnLoadModule function
		 * @author : ALVES Quentin
		 * @note : UnLoad a module from the editor.
		 * @param name : Name to the query module.
		 * @return : bool
		 **/
		void UnLoadModule( nString name );

		/**
		 * UnLoadModule function
		 * @author : ALVES Quentin
		 * @note : UnLoad a module from the editor.
		 * @param name : Name to the query module.
		 * @return : bool
		 **/
		inline void UnLoadModule( const std::string& path );

		/**
		 * Close method
		 * @author : ALVES Quentin
		 * @note : Close a window from the editor.
		 * @param name : Name of the query window.
		 **/
		void Close( nString name );

		/**
		 * Close method
		 * @author : ALVES Quentin
		 * @note : Close a window from the editor.
		 * @param name : Name of the query window.
		 **/
		inline void Close( const std::string& name );

		/**
		 * Exit method
		 * @author : ALVES Quentin
		 * @note : Exit the editor.
		 **/
		void Exit( );

	private:
		/**
		 * LoadDependencies method
		 * @author : ALVES Quentin
		 * @note : Load dependencies of the editor.
		 **/
		void LoadDependencies( );

		/**
		 * Start function
		 * @author : ALVES Quentin
		 * @note : Start the editor.
		 * @param argc : Count of argument.
		 * @param argv : Value for argument.
		 * @return : bool
		 **/
		bool Start( int argc, char** argv );

		/**
		 * Run method
		 * @author : ALVES Quentin
		 * @note : Run the editor.
		 **/
		void Run( );

		/**
		 * Stop method
		 * @author : ALVES Quentin
		 * @note : Stop the editor.
		 **/
		void Stop( );

	public:
		/**
		 * Log template method
		 * @author : ALVES Quentin
		 * @note : Log information with editor logger.
		 * @template Args : Arguements types.
		 * @param mode : Logger mode.
		 * @param format : Format of the log.
		 * @param args : Arguments of the log.
		 **/
		template<typename... Args>
		void Log( NutLoggerModes mode, nString format, Args... args );

		/**
		 * Log template method
		 * @author : ALVES Quentin
		 * @note : Log information with editor logger.
		 * @template Args : Arguements types.
		 * @param mode : Logger mode.
		 * @param format : Format of the log.
		 * @param args : Arguments of the log.
		 **/
		template<typename... Args>
		void Log( NutLoggerModes mode, const std::string& format, Args... args );

		/**
		 * LogProfile template method
		 * @author : ALVES Quentin
		 * @note : Log information with editor logger.
		 * @template Args : Arguements types.
		 * @param profile : Name of the logger profile.
		 * @param mode : Logger mode.
		 * @param format : Format of the log.
		 * @param args : Arguments of the log.
		 **/
		template<typename... Args>
		void LogProfile( nString profile, NutLoggerModes mode, nString format, Args... args );

		/**
		 * LogProfile template method
		 * @author : ALVES Quentin
		 * @note : Log information with editor logger.
		 * @template Args : Arguements types.
		 * @param profile : Name of the logger profile.
		 * @param mode : Logger mode.
		 * @param format : Format of the log.
		 * @param args : Arguments of the log.
		 **/
		template<typename... Args>
		void LogProfile( const std::string& profile, NutLoggerModes mode, const std::string& format, Args... args );

		/**
		 * SetStyle template method
		 * @author : ALVES Quentin
		 * @note : Set editor style.
		 * @template Type : NutStyle instance.
		 **/
		template<typename Type = NutStyle>
		void SetStyle( );

		/**
		 * Register template function
		 * @author : ALVES Quentin
		 * @note : Register a module to the editor.
		 * @template Type : NutModule instance.
		 * @template Args : Arguements types.
		 * @param importer : Pointer to current module importer.
		 * @param args : Arguments for module constructor.
		 * @return : Type*
		 **/
		template<typename Type = NutModule, typename... Args>
		Type* Register( NutPlatformLib* importer, Args... args );

		/**
		 * Open template function
		 * @author : ALVES Quentin
		 * @note : Open a new window on the editor.
		 * @template Type : NutWindow instance.
		 * @template Args : Arguements types.
		 * @param args : Arguments for window constructor.
		 * @return : Type*
		 **/
		template<typename Type = NutWindow, typename... Args>
		Type* Open( Args... args );

	public:
		/**
		 * GetVersion const function
		 * @author : ALVES Quentin
		 * @note : Get current editor version.
		 * @return : const std::string
		 **/
		const std::string GetVersion( ) const;

		/**
		 * GetLicense const function
		 * @author : ALVES Quentin
		 * @note : Get current editor license.
		 * @return : const std::string
		 **/
		const std::string GetLicense( ) const;

		/**
		 * GetFileSystem const function
		 * @author : ALVES Quentin
		 * @note : Get current editor file system.
		 * @return : NutFileSystem*
		 **/
		inline NutFileSystem* GetFileSystem( ) const;

		/**
		 * GetAssetManager const function
		 * @author : ALVES Quentin
		 * @note : Get current editor asset manager.
		 * @return : NutAssetManager*
		 **/
		inline NutAssetManager* GetAssetManager( ) const;

		/**
		 * GetStyle const function
		 * @author : ALVES Quentin
		 * @note : Get current editor style.
		 * @return : NutStyle*
		 **/
		inline NutStyle* GetStyle( ) const;

		/**
		 * GetLibrary const function
		 * @author : ALVES Quentin
		 * @note : Get a library form the editor.
		 * @param name : Name of the library.
		 * @return : NutLibrary*
		 **/
		inline NutLibrary* GetLibrary( nString name ) const;

		/**
		 * GetModule const function
		 * @author : ALVES Quentin
		 * @note : Get a module form the editor.
		 * @param name : Name of the module.
		 * @return : NutModule*
		 **/
		inline NutModule* GetModule( nString name ) const;

		/**
		 * GetWindow const function
		 * @author : ALVES Quentin
		 * @note : Get a window form the editor.
		 * @param name : Name of the window.
		 * @return : NutWindow*
		 **/
		inline NutWindow* GetWindow( nString name ) const;

	public:
		/**
		 * GetLibrary template const function
		 * @author : ALVES Quentin
		 * @note : Get a library form the editor.
		 * @template Type : NutLibrary instance.
		 * @param name : Name of the library.
		 * @return : NutLibrary*
		 **/
		template<typename Type = NutLibrary>
		inline Type* GetLibrary( nString name ) const;

		/**
		 * GetModule template const function
		 * @author : ALVES Quentin
		 * @note : Get a module form the editor.
		 * @template Type : NutModule instance.
		 * @param name : Name of the module.
		 * @return : NutModule*
		 **/
		template<typename Type = NutModule>
		inline Type* GetModule( nString name ) const;

		/**
		 * GetWindow template const function
		 * @author : ALVES Quentin
		 * @note : Get a window form the editor.
		 * @template Type : NutWindow instance.
		 * @param name : Name of the window.
		 * @return : Type*
		 **/
		template<typename Type = NutWindow>
		inline Type* GetWindow( nString name ) const;

	};

	#include <Templates/NutEditor.hpp>

#endif
