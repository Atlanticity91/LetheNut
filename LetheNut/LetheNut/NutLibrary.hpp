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
 * This file is part of Lethe Nut project : https://github.com/Atlanticity91/LetheNut
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

#ifndef _IGS_NUT_LIBRARY_HPP_
#define _IGS_NUT_LIBRARY_HPP_

	#include "PlatformLib.hpp"

	/**
	 * NutLibImporter definition
	 * @author : ALVES Quentin
	 * @node : Define the function type for default library imports functions.
	 **/
	typedef nString( *NutLibImporter )( );

	/**
	 * NutLibrary final class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Library core class.
	 **/
	class NUT_API NutLibrary final {

		friend class NutKernel;

	private:
		NutPlatformLib handle;
		NutLibImporter name;
		NutLibImporter description;
		NutLibImporter author;
		NutLibImporter version;
		NutLibImporter license;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutLibrary( ) = default;

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param path : Path to the query library.
		 **/
		NutLibrary( nString path );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param path : Path to the query library.
		 **/
		NutLibrary( const std::string& path );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutLibrary( ) = default;

	public:
		/**
		 * Call template function
		 * @author : ALVES Quentin
		 * @note : Initialize the current library.
		 * @template Return : Return type of the function.
		 * @temlate Type : Function type definition.
		 * @template Args : Capture types of arguments.
		 * @param name : Name of the query function.
		 * @param args : Arguments for the function call.
		 * @return : Return
		 **/
		template< typename Functor, typename... Args >
		auto Call( nString name, Args... args );

	public:
		/**
		 * GetIsValid const function
		 * @author : ALVES Quentin
		 * @note : Get if the library is valid.
		 * @return : bool
		 **/
		bool GetIsValid( ) const;

		/**
		 * GetName const function
		 * @author : ALVES Quentin
		 * @note : Get if the library name.
		 * @return : nString
		 **/
		nString GetName( ) const;

		/**
		 * GetDescription const function
		 * @author : ALVES Quentin
		 * @note : Get if the library description.
		 * @return : nString
		 **/
		nString GetDescription( ) const;

		/**
		 * GetAuthor const function
		 * @author : ALVES Quentin
		 * @note : Get if the library author.
		 * @return : nString
		 **/
		nString GetAuthor( ) const;

		/**
		 * GetVersion const function
		 * @author : ALVES Quentin
		 * @note : Get if the library version.
		 * @return : nString
		 **/
		nString GetVersion( ) const;

		/**
		 * GetLicense const function
		 * @author : ALVES Quentin
		 * @note : Get if the library license.
		 * @return : nString
		 **/
		nString GetLicense( ) const;

		NutProcedure Get( nString name ) const;

	public:
		NutProcedure operator[]( nString name ) const;

	};

	#include <Templates/NutLibrary.hpp>

#endif
