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

#ifndef _IGS_NUT_VENDOR_JSON_IMP_HPP_
#define _IGS_NUT_VENDOR_JSON_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC	
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Type >
	void JSON::Append( nString parameter, const Type& data ) {
		if ( parameter && strlen( parameter ) > 0 )
			this->data[ parameter ] = data;
	}

	template< typename Type >
	void JSON::Append( nString parameter, const Type&& data ) {
		return this->Append( parameter, data );
	}

	template< typename Type, typename Action, typename... Args >
	void JSON::Foreach( nString parameter, Action&& action, Args... args ) {
		if constexpr ( std::is_same<Type, std::string>::value )
			this->InternalForeach<JSON::StringArray>( parameter, Action, args... );
		else if constexpr ( std::is_same<Type, bool>::value )
			this->InternalForeach<JSON::BoolArray>( parameter, Action, args... );
		else if constexpr ( std::is_same<Type, nInt>::value )
			this->InternalForeach<JSON::IntArray>( parameter, Action, args... );
		else if constexpr ( std::is_same<Type, nUInt>::value )
			this->InternalForeach<JSON::UIntArray>( parameter, Action, args... );
		else if constexpr ( std::is_same<Type, float>::value )
			this->InternalForeach<JSON::FloatArray>( parameter, Action, args... );
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PRIVATE
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Type, typename Action, typename... Args >
	void JSON::InternalForeach( nString parameter, Action&& action, Args... args ) {
		auto element_array = this->InternalGetArray<Type>( parameter );

		for ( const auto& element : element_array )
			action( element, args... );
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC GET
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Type >
	const Type JSON::Get( nString parameter ) const {
		if constexpr ( std::is_same<Type, std::string>::value ) {
			if ( this->data[ parameter ].is_string( ) )
				return this->data[ parameter ];
		} else if constexpr ( std::is_same<Type, bool>::value ) {
			if ( this->data[ parameter ].is_boolean( ) )
				return this->data[ parameter ];
		} else if constexpr ( std::is_same<Type, nInt>::value ) {
			if ( this->data[ parameter ].is_number_integer( ) )
				return this->data[ parameter ];
		} else if constexpr ( std::is_same<Type, nUInt>::value ) {
			if ( this->data[ parameter ].is_number_unsigned( ) )
				return this->data[ parameter ];
		} else if constexpr ( std::is_same<Type, float>::value ) {
			if ( this->data[ parameter ].is_number_float( ) )
				return this->data[ parameter ];
		} else if constexpr ( std::is_same<Type, JSON::StringArray>::value )
			return this->InternalGetArray<JSON::StringArray>( parameter );
		else if constexpr ( std::is_same<Type, JSON::BoolArray>::value )
			return this->InternalGetArray<JSON::BoolArray>( parameter );
		else if constexpr ( std::is_same<Type, JSON::IntArray>::value )
			return this->InternalGetArray<JSON::IntArray>( parameter );
		else if constexpr ( std::is_same<Type, JSON::UIntArray>::value )
			return this->InternalGetArray<JSON::UIntArray>( parameter );
		else if constexpr ( std::is_same<Type, JSON::FloatArray>::value )
			return this->InternalGetArray<JSON::FloatArray>( parameter );

		return Type( );
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PRIVAET GET
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Array >
	const Array JSON::InternalGetArray( nString parameter ) const {
		if ( this->data[ parameter ].is_array( ) )
			return this->data[ parameter ];

		return Array( );
	}

#endif
