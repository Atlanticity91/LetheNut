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

#ifndef _IGS_NUT_LIST_HPP_
#define _IGS_NUT_LIST_HPP_

	#include "NutElement.hpp"

	/**
	 * NutList template final class
	 * @author : ALVES Quentin
	 * @note : Defined NutList core class.
	 * @template Type : NutElement instance.
	 **/
	template<typename Type = NutElement>
	class NutList final {

	private:
		mutable std::vector<Type> data;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutList( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutList( );

		/**
		 * Emplace function
		 * @author : ALVES Quentin
		 * @param data : Data to emplace.
		 * @return : Type*
		 **/
		Type* Emplace( const Type& data );

		/**
		 * Erase method
		 * @author : ALVES Quentin
		 * @param query_id : Index of the query element.
		 **/
		void Erase( size_t query_id );

		/**
		 * Erase method
		 * @author : ALVES Quentin
		 * @param label : Label of the query element.
		 **/
		void Erase( nString label );

		/**
		 * Erase method
		 * @author : ALVES Quentin
		 * @param label : Label of the query element.
		 **/
		void Erase( const std::string& label );

	public:
		/**
		 * Append function
		 * @author : ALVES Quentin
		 * @node : Append a new element.
		 * @template Args : Arguments types.
		 * @param args : Arguments of the new element.
		 * @return : Type*
		 **/
		template<typename... Args>
		Type* Append( Args... args );

		/**
		 * Foreach function
		 * @author : ALVES Quentin
		 * @node : Append a new element.
		 * @template Functor : Functor type.
		 * @template Args : Arguments types.
		 * @param functor : Reference to lambda.
		 * @param args : Arguments for the functor.
		 * @return : Type*
		 **/
		template<typename Functor, typename... Args>
		void Foreach( Functor&& functor, Args... args );

		/**
		 * Foreach function
		 * @author : ALVES Quentin
		 * @node : Append a new element.
		 * @template Functor : Functor type.
		 * @template Args : Arguments types.
		 * @param condition : Condition of the foreach.
		 * @param functor : Reference to lambda.
		 * @param args : Arguments for the functor.
		 * @return : Type*
		 **/
		template<typename Functor, typename... Args>
		void Foreach( bool& condition, Functor&& functor, Args... args );

	public:
		/**
		 * GetSize const function
		 * @author : ALVES Quentin
		 * @node : Get current list size.
		 * @return : const size_t
		 **/
		const size_t GetSize( ) const;

		/**
		 * At const function
		 * @author : ALVES Quentin
		 * @node : Get an element by index.
		 * @param query_id : Index of the query element.
		 * @return : Type*
		 **/
		Type* At( size_t query_id ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @node : Get an element by label.
		 * @param label : Label of the query element.
		 * @return : Type*
		 **/
		Type* Get( nString label ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @node : Get an element by label.
		 * @param label : Label of the query element.
		 * @return : Type*
		 **/
		Type* Get( const std::string& label ) const;

		/**
		 * begin function
		 * @author : ALVES Quentin
		 * @node : Begin list.
		 * @return : auto
		 **/
		inline auto begin( );

		/**
		 * end function
		 * @author : ALVES Quentin
		 * @node : End list.
		 * @return : auto
		 **/
		inline auto end( );

	public:
		/**
		 * Cast operator
		 * @author : ALVES Quentin
		 * @note : Convert list to boolean.
		 * @return : bool
		 **/
		operator bool( ) const;

		/**
		 * Cast operator
		 * @author : ALVES Quentin
		 * @note : Convert list to size_t.
		 * @return : size_t
		 **/
		operator size_t( ) const;

		/**
		 * [ ] operator
		 * @author : ALVES Quentin
		 * @note : Get an element by index.
		 * @param query_id : Index of the query element.
		 * @return : Type*
		 **/
		Type* operator[]( size_t query_id ) const;

		/**
		 * [ ] operator
		 * @author : ALVES Quentin
		 * @note : Get an element by label.
		 * @param label : Label of the query element.
		 * @return : Type*
		 **/
		Type* operator[]( nString label ) const;

		/**
		 * [ ] operator
		 * @author : ALVES Quentin
		 * @note : Get an element by label.
		 * @param label : Label of the query element.
		 * @return : Type*
		 **/
		Type* operator[]( const std::string& label ) const;

	};

	#include <Templates/NutList.hpp>

#endif
