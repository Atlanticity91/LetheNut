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

#ifndef _IGS_NUT_CORE_HPP_
#define _IGS_NUT_CORE_HPP_

	/** 
	 * Import native C libraries.
	 * @author : ALVES Quentin
	 **/
	extern "C" {

		#include <stdarg.h>
		#include <stdlib.h>
		#include <stdio.h>
		#include <stdint.h>

	};

	/**
	 * Import native C++ libraries.
	 * @author : ALVES Quentin
	 **/
	#include <bitset>
	#include <map>
	#include <memory>
	#include <new>
	#include <optional>
	#include <random>
	#include <regex>
	#include <string>
	#include <type_traits>
	#include <vector>

	/**
	 * Defined NUT_API for import and export data from DLL.
	 * @author : ALVES Quentin
	 **/
	#ifdef _WIN64
		#include <windows.h>
		
		/**
		 * Disable un-usefull warnings on MSC.
		 * @author : ALVES Quentin
		 **/
		#ifdef _MSC_VER
			// Disable C4251 on visual studio to avoid :
			// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
			#pragma warning( disable: 4251 )
		#endif

		#ifdef NBUILD
			#define NUT_API __declspec( dllexport )
		#else
			#define NUT_API __declspec( dllimport )
		#endif
	#else
		#define NUT_API
	#endif

	/**
	 * Defined Lethe unicode support for strings.
	 * @author : ALVES Quentin
	 **/
	#ifndef NTEXT 
		#ifdef PLATFORM_TCHAR_IS_CHAR16
			#define NTEXT_PASTE( QUERY ) u ## QUERY
		#else
			#define NTEXT_PASTE( QUERY ) L ## QUERY
		#endif

		#define NTEXT( QUERY ) NTEXT_PASTE( QUERY )
	#endif

	/**
	 * NUT_DEPRECATED macro
	 * @author : ALVES Quentin
	 * @note :
	 * @usage : NUT_DEPRECATED( NUT_VERSION, NEW_DEFINITION )
	 * @example :
	 *		NUT_DEPRECATED( 1.8, void Print( nString sender, nString format, ... ) )
	 *		void Print( nString string );
	 * 
	 *		-> During compilation if Print( nString string ) is used, the compiler will show :
	 *			Deprecated since : 1.8, update your code base to use : void 
				Print( nString sender, nString format, ... ) instead.

	 *		-> The first parameter of the macro SINCE defined the first version of LetheNut 
	 *		   where a new version of the function is provide.
	 *	
	 *		-> The second parameter NEW defined the new prototype of the function.
	 **/
	#define NUT_DEPRECATED( SINCE, DEFINITION ) [[deprecated( "Deprecated since : " #SINCE ", update your code base to use : " #DEFINITION " instead." )]]

	/**
	 * Mutable helper macro's
	 * @author : ALVES Quentin
	 * @note : Defined mutable variable definition more easily.
	 **/
	#define MUT_BYTE( NAME ) mutable leByte NAME
	#define MUT_SHORT( NAME ) mutable leShort NAME
	#define MUT_INT( NAME ) mutable leInt NAME
	#define MUT_LONG( NAME ) mutable leLong NAME
	#define MUT_UBYTE( NAME ) mutable leUByte NAME
	#define MUT_USHORT( NAME ) mutable leUShort NAME
	#define MUT_UINT( NAME ) mutable leUInt NAME
	#define MUT_ULONG( NAME ) mutable leULong NAME 
	#define MUT_FLOAT( NAME ) mutable float NAME 
	#define MUT_ENUM( TYPE, NAME ) mutable enum TYPE NAME
	#define MUT_STRUCT( TYPE, NAME ) mutable struct TYPE NAME
	#define MUT_CLASS( TYPE, NAME ) mutable class TYPE NAME
	#define MUT_UNION( TYPE, NAME ) mutable union TYPE NAME

	/**
	 * Type size helper macro's
	 * @author : ALVES Quentin
	 **/
	#define SIZE_ENUM( NAME ) sizeof( enum NAME )
	#define SIZE_STRUCT( NAME ) sizeof( struct NAME )
	#define SIZE_CLASS( NAME ) sizeof( class NAME )
	#define SIZE_UNION( NAME ) sizeof( union NAME )

	/**
	 * Size helper macro's
	 * @author : ALVES Quentin
	 **/
	#define SIZE_CHAR sizeof( char )
	#define SIZE_BYTE sizeof( nByte )
	#define SIZE_SHORT sizeof( nShort )
	#define SIZE_INT sizeof( nInt )
	#define SIZE_LONG sizeof( nLong )
	#define SIZE_FLOAT sizeof( float )
	#define SIZE_DOUBLE sizeof( double )

	/**
	 * Bit's shift helper macro's
	 * @author : ALVES Quentin
	 **/
	#define SHIFT_L( VAL, BITS ) ( VAL << BITS )
	#define SHIFT_R( VAL, BITS ) ( VAL >> BITS )

	/**
	 * Max macro
	 * @author : ALVES Quentin
	 * @note : Macro for variable max value.
	 **/
	#define MAX( A, B ) ( ( A < B ) ? B : A )

	/**
	 * NUT_CLASS macro
	 * @author : ALVES Quentin
	 * @note : Internal helper for class declaration.
	 **/
	#define NUT_CLASS( NAME, PARENT, ... ) class NUT_API NAME __VA_ARGS__ : public PARENT

	/**
	 * Type alias definition.
	 * @author : ALVES Quentin
	 **/
	typedef int8_t nByte;
	typedef int16_t nShort;
	typedef int32_t nInt;
	typedef int64_t nLong;
	typedef uint8_t nUByte;
	typedef uint16_t nUShort;
	typedef uint32_t nUInt;
	typedef uint64_t nULong;
	typedef uint8_t* nPointer;
	typedef const char* nString;

	/**
	 * Alloc template function
	 * @author : ALVES Quentin
	 * @note : Internal definition for memory allocation.
	 * @template Type : Query type to allocate.
	 * @param count : How many instance to allocate.
	 * @return : Type*
	 **/
	template< typename Type >
	Type* Alloc( size_t count ) { return (Type*)malloc( sizeof( Type ) * count );  }

	/**
	 * nClamp template method
	 * @author : ALVES Quentin
	 * @note : Internal definition for clamp method.
	 * @template Type : Query type to clamp.
	 * @param value : How many instance to allocate.
	 * @param min : Minimum value.
	 * @param max : Maximum value.
	 **/
	template< typename Type >
	void nClamp( Type& value, Type min, Type max ) {
		if constexpr ( std::is_literal_type<Type>::value ) {
			if ( value < min )
				value = min;
			else if ( value > max )
				value = max;
		}
	}

#endif
