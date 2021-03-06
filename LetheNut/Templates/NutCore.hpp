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

#ifndef _IGS_NUT_CORE_IMP_HPP_
#define _IGS_NUT_CORE_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Type >
	Type* nHelper::Alloc( size_t count ) { return (Type*)malloc( sizeof( Type ) * count ); }

	template< typename Type >
	void nHelper::Copy( const Type& source, Type& destination ) {
		nHelper::Copy( source, destination, 1 );
	}

	template< typename Type >
	void nHelper::Copy( const Type& source, Type& destination, nULong count ) {
		count = ( count > 0 ) ? count : 1;

#ifdef _WIN64
		memcpy_s( &destination, sizeof( Type ) * count, &source, sizeof( Type ) * count );

#else
		memcpy( &destination, &source, sizeof( Type ) * count );
#endif
	}

	template< typename Type >
	void nHelper::Clamp( Type& value, Type min, Type max ) {
		if ( value < min )
			value = min;
		else if ( value > max )
			value = max;
	}

	template< typename Callback, typename... Args >
	void nHelper::Blink( nTimePoint& time, nTimePoint duration, Callback&& callback, Args... args ) {
		auto timeEnd = nHelper::GetTime( );
		auto elapsed = timeEnd - time;

		if ( elapsed > duration ) {
			callback( args... );

			if ( elapsed > duration * 2 )
				time = timeEnd;
		}
	}

	template< typename Function, typename... Args >
	void nHelper::Async( Function&& function, Args... args ) {
		std::async( std::launch::async, function, args... );
	}

	template< typename Return, typename Function, typename... Args >
	std::future<Return> nHelper::Async( Function&& function, Args... args ) {
		return std::async( std::launch::async, function, args... );
	}

#endif
