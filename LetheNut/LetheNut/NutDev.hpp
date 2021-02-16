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
 * Copyright (C) 2021 ALVES Quentin.
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

#ifndef _IGS_NUT_DEV_HPP_
#define _IGS_NUT_DEV_HPP_

	#include "NutEditor.hpp"

	/**
	 * NEXPORT macro
	 * @author : ALVES Quentin
	 * @note : Helper for code exportation.
	 * @usage : NEXPORT( QUERY_OPTION_TO_EXPORT );
	 * @example :
	 *		NEXPORT( static void __declspec( dllexport ) Hi( ) { printf( "Hi\n" ); }; );
	 *
	 *		-> Export a method called Hi that print Hi on console.
	 *		-> Specifier __declspec( dllexport ) used for windows for dll export.
	 **/
	#define NEXPORT( ... ) extern "C" { __VA_ARGS__ }

	/**
	 * NAPI macro
	 * @author : ALVES Quentin
	 * @note : Helper for API declaration.
	 **/
	#ifdef _WIN64
		#define NAPI __declspec( dllexport )
	#else
		#define NAPI 
	#endif

	/**
	 * NFUNC_DCL macro
	 * @author : ALVES Quentin
	 * @note : Helper for function exportation.
	 * @usage : NFUNC( RETURN_TYPE, NAME, PARAMETERS );
	 * @example :
	 *		NFUNC( void, Hi );
	 *
	 *		-> Create method Hi declaration ready for export.
	 **/
	#define NFUNC_DCL( RETURN, NAME, ... ) RETURN NAPI NAME( __VA_ARGS__ )

	/**
	 * NFUNC macro
	 * @author : ALVES Quentin
	 * @note : Helper for function exportation.
	 * @usage : NFUNC( RETURN_TYPE, NAME, BODY, PARAMETERS );
	 * @example :
	 *		NFUNC( void, Hi, printf( "Hi\n" ); );
	 *
	 *		-> Create static method Hi ready for export.
	 **/
	#define NFUNC( RETURN, NAME, BODY, ... ) NFUNC_DCL( RETURN, NAME, __VA_ARGS__ ) { BODY }

	/**
	 * NLIBRARY_CREATE macro
	 * @author : ALVES Quentin
	 * @note : Helper for library creation and exportation.
	 * @usage : NLIBRARY_CREATE( NAME, DESCRIPTION, AUTHOR, VERSION, LICENSE );
	 * @warning :
	 *		You can't create function with names list below :
	 *			GetName
	 *			GetDescription
	 *			GetAuthor
	 *			GetVersion
	 *			GetLicense
	 *
	 * @example :
	 *		NLIBRARY_CREATE( ExampleLib, Simple example lib !, ALVES Quentin, 1.0, MIT );
	 *
	 *		-> Create the core functions for library export.
 	 *		-> GetName : Get the name of the library.
	 * 		-> GetDescription : Get the description of the library.
	 * 		-> GetAuthor : Get the author of the library.
	 * 		-> GetVersion : Get the version of the library.
	 * 		-> GetLicense : Get the license of the library.
	 **/
	#define NLIBRARY_CREATE( NAME, DESCRIPTION, AUTHOR, VERSION, LICENSE ) NEXPORT(\
		NFUNC( nString, GetName, return #NAME; );\
		NFUNC( nString, GetDescription, return #DESCRIPTION; );\
		NFUNC( nString, GetAuthor, return #AUTHOR; );\
		NFUNC( nString, GetVersion, return #VERSION; );\
		NFUNC( nString, GetLicense, return #LICENSE; );\
	)

	/**
	 * NMODULE_CREATE macro
	 * @author : ALVES Quentin
	 * @note : Helper for module exportation.
	 * @usage : NMODULE_CREATE( NAME );
	 * @example :
	 *		NMODULE_CREATE( ExampleModule );
	 *
	 *		-> Create the core function for module export.
	 *		-> The module ExampleModule is exported and ready to use inside NutEditor.
	 **/
	#define NMODULE_CREATE( MODULE ) NEXPORT(\
		NFUNC( void, RegisterModule, editor->Register< MODULE >( importer );, NutEditor* editor, NutPlatformLib* importer );\
	)

	/**
	 * NSTRUCT macro
	 * @author : ALVES Quentin
	 * @note : Helper for module class creation.
	 * @usage : NSTRUCT( NAME )
	 * @example :
	 *		NSTRUCT( Test )
	 *
	 *		-> Create a struct Test with API export decorator.
	 **/
	#define NSTRUCT( NAME ) struct NAPI NAME 

	/**
	 * NCLASS macro
	 * @author : ALVES Quentin
	 * @note : Helper for module class creation.
	 * @usage : NCLASS( NAME )
	 * @example :
	 *		NCLASS( Test )
	 *
	 *		-> Create a class Test with API export decorator.
	 **/
	#define NCLASS( NAME ) class NAPI NAME 

#endif
