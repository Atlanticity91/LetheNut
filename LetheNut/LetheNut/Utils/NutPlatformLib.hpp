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

#ifndef _IGS_NUT_PLATFORM_LIB_HPP_
#define _IGS_NUT_PLATFORM_LIB_HPP_

	#include <LetheNut/NutCore.hpp>

	 /**
	  * NutLibrary final class
	  * @author : ALVES Quentin
	  * @note : Defined Nut Procedure core class.
	  **/
	class NUT_API NutProcedure final {

	private:
#ifdef _WIN64
		FARPROC handle;
#else
		void* handle;
#endif

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param handle : Default handle value.
		 **/
#ifdef _WIN64
		NutProcedure( FARPROC handle );
#else
		NutProcedure( void* handle );
#endif

	public:
		/**
		 * operator () const
		 * @author : ALVES Quentin
		 * @note : Get the procedure casted to query function.
		 * @return : Functor*
		 **/
		template <typename Functor, typename = std::enable_if_t<std::is_function_v<Functor>>>
		operator Functor* ( ) const {
			return reinterpret_cast<Functor*>( this->handle );
		};

	};

	/**
	 * NutPlatformLib final class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Platform Library core class.
	 **/
	class NUT_API NutPlatformLib final {

	private:
#ifdef _WIN64
		HMODULE handle;
#else
		void* handle;
#endif

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutPlatformLib( );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param path : Path to the query library file.
		 **/
		NutPlatformLib( nString path );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param path : Path to the query library file.
		 **/
		NutPlatformLib( const std::string& path );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutPlatformLib( );

	public:
		/**
		 * GetIsValid const function
		 * @author : ALVES Quentin
		 * @note : Get if the library is valid.
		 * @return : bool
		 **/
		bool GetIsValid( ) const;

		/**
		 * Has const function
		 * @author : ALVES Quentin
		 * @note : Get if the library has a procedure.
		 * @param query_name : Name of the query procedure.
		 * @return : bool
		 **/
		bool Has( nString query_name ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get a procedure of library.
		 * @param query_name : Name of the query procedure.
		 * @return : NutProcedure
		 **/
		NutProcedure Get( nString query_name ) const;

	private:
		/**
		 * IsValid const function
		 * @author : ALVES Quentin
		 * @note : Get if the library is valid.
		 * @param query_name : Name of the query procedure.
		 * @return : bool
		 **/
		bool IsValid( nString query_name ) const;

	public:
		/**
		 * operator[] const
		 * @author : ALVES Quentin
		 * @note : Get a procedure of library.
		 * @param query_name : Name of the query procedure.
		 * @return : NutProcedure
		 **/
		NutProcedure operator[]( nString query_name ) const;

	};

#endif
