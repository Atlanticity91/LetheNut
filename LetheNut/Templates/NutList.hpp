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

#ifndef _IGS_NUT_LIST_IMP_HPP_
#define _IGS_NUT_LIST_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename Type>
	NutList<Type>::NutList( )
		: data( )
	{ }

	template<typename Type>
	NutList<Type>::~NutList( ) {
		if constexpr ( std::is_pointer<Type>::value ) {
			for ( auto& element : this->data ) 
				delete element;
		}
	}

	template<typename Type>
	void NutList<Type>::Emplace( const Type& data ) {
		if constexpr ( !std::is_pointer<Type>::value )
			this->data.emplace_back( data );
		else {
			if ( data )
				this->data.emplace_back( data );
		}
	}

	template<typename Type>
	void NutList<Type>::Erase( size_t query_id ) {
		if ( query_id < this->data.size( ) ) {
			if constexpr ( std::is_pointer<Type>::value )
				delete this->data[ query_id ];

			this->data.erase( this->data.begin( ) + query_id );
		}
	}

	template<typename Type>
	void NutList<Type>::Erase( nString label ) {
		if ( nHelper::GetIsValid( label ) ) {
			auto hash = nHelper::Hash( label );
			auto idx = this->data.size( );

			while ( idx-- > 0 ) {
				if constexpr ( !std::is_pointer<Type>::value ) {
					if ( this->data[ idx ].GetHash( ) == hash ) {
						this->data.erase( this->data.begin( ) + idx );

						return;
					}
				} else {
					if ( this->data[ idx ]->GetHash( ) == hash ) {
						delete this->data[ idx ];
						this->data.erase( this->data.begin( ) + idx );

						return;
					}
				}
			}
		}
	}

	template<typename Type>
	void NutList<Type>::Erase( const std::string& label ) {
		this->Erase( label.c_str( ) );
	}

	template<typename Type>
	template<typename... Args>
	Type* NutList<Type>::Append( Args... args ) {
		if constexpr ( !std::is_pointer<Type>::value ) {
			auto data = Type( args... );
			this->data.emplace_back( data );
		} else {
			auto* data = new Type( args... );

			if ( data )
				this->data.emplace_back( data );
			else
				return nullptr;
		}

		return &this->data[ this->data.size( ) - 1 ];
	}

	template<typename Type>
	template<typename Functor, typename... Args>
	void NutList<Type>::Foreach( Functor&& functor, Args... args ) {
		for ( auto& element : this->data )
			functor( element, args... );
	}

	template<typename Type>
	template<typename Functor, typename... Args>
	void NutList<Type>::Foreach( bool& condition, Functor&& functor, Args... args ) {
		for ( auto& element : this->data ) {
			if ( condition )
				functor( condition, element, args... );
			else
				break;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC GET
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename Type>
	const size_t NutList<Type>::GetSize( ) const { return this->data.size( ); }

	template<typename Type>
	Type* NutList<Type>::At( size_t query_id ) const {
		if ( query_id < this->data.size( ) )
			return &this->data[ query_id ];

		return nullptr;
	}

	template<typename Type>
	Type* NutList<Type>::Get( nString label ) const {
		if ( nHelper::GetIsValid( label ) ) {
			auto hash = nHelper::Hash( label );
			auto idx = this->data.size( );

			while ( idx-- > 0 ) {
				if constexpr ( !std::is_pointer<Type>::value ) {
					if ( this->data[ idx ].GetHash( ) == hash )
						return &this->data[ idx ];
				} else {
					if ( this->data[ idx ]->GetHash( ) == hash )
						return &this->data[ idx ];
				}
			}
		}

		return nullptr;
	}

	template<typename Type>
	Type* NutList<Type>::Get( const std::string& label ) const {
		return this->Get( label.c_str( ) );
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      OPERATOR
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename Type>
	NutList<Type>::operator bool( ) const { return this->data.size( ) > 0; }

	template<typename Type>
	NutList<Type>::operator size_t( ) const { return this->data.size( ); }

	template<typename Type>
	Type* NutList<Type>::operator[]( size_t query_id ) const {
		return this->At( query_id );
	}

	template<typename Type>
	Type* NutList<Type>::operator[]( nString label ) const {
		return this->Get( label );
	}

	template<typename Type>
	Type* NutList<Type>::operator[]( const std::string& label ) const {
		return this->Get( label );
	}

#endif
