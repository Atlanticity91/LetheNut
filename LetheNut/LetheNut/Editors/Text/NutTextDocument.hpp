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

#ifndef _IGS_NUT_TEXT_DOCUMENT_HPP_
#define _IGS_NUT_TEXT_DOCUMENT_HPP_

	#include <LetheNut/Core.hpp>

	/**
	 * NutTextCursor struct
	 * @author : ALVES Quentin
	 * @note : Defined nut text editor cursor.
	 **/
	struct NutTextCursor {

		nUInt line;
		nUInt position;

	};

	/**
	 * NutTextDocument final class
	 * @author : ALVES Quentin
	 * @note : Defined nut text document core class.
	 **/
	class NUT_API NutTextDocument final {

		using Line = std::string;
		using Lines = std::vector<Line>;

	private:
		std::string name;
		mutable NutTextCursor cursor;
		mutable Lines lines;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutTextDocument( ) = default;

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the new document.
		 **/
		NutTextDocument( nString name );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the new document.
		 **/
		NutTextDocument( const std::string& name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutTextDocument( );

		/**
		 * SetCursor method
		 * @author : ALVES Quentin
		 * @note : Set the current cursor instance value.
		 * @param cursor : Cursor to save.
		 **/
		void SetCursor( const NutTextCursor& cursor );

		/**
		 * Append method
		 * @author : ALVES Quentin
		 * @note : Add a character to the end of a line.
		 * @param character : The character to add.
		 * @param line : Index of the query line.
		 **/
		void Append( char character, nUInt line );

		/**
		 * Append method
		 * @author : ALVES Quentin
		 * @note : Add a string to the end of a line.
		 * @param string : The string to add.
		 * @param line : Index of the query line.
		 **/
		void Append( const std::string& string, nUInt line );

		/**
		 * Insert method
		 * @author : ALVES Quentin
		 * @note : Insert a character to a line.
		 * @param character : The character to add.
		 * @param cursor : Current text cursor position.
		 **/
		void Insert( char character, NutTextCursor& cursor );

		/**
		 * Insert method
		 * @author : ALVES Quentin
		 * @note : Insert a string to a line.
		 * @param string : The string to add.
		 * @param cursor : Current text cursor position.
		 **/
		void Insert( const std::string& string, NutTextCursor& cursor );

		/**
		 * Insert method
		 * @author : ALVES Quentin
		 * @note : Insert a character to a line.
		 * @param character : The character to add.
		 * @param line : Index of the query line.
		 * @param postion : Position where character the string on the line.
		 **/
		void Insert( char character, nUInt line, nUInt position );

		/**
		 * Insert method
		 * @author : ALVES Quentin
		 * @note : Insert a string to a line.
		 * @param string : The string to add.
		 * @param line : Index of the query line.
		 * @param postion : Position where insert the string on the line.
		 **/
		void Insert( const std::string& string, nUInt line, nUInt position );

		/**
		 * Delete method
		 * @author : ALVES Quentin
		 * @note : Delete a character from a line.
		 * @param line : Index of the query line.
		 * @param position : Position of the character on the line.
		 **/
		void Delete( nUInt line, nUInt position );

		/**
		 * Delete method
		 * @author : ALVES Quentin
		 * @note : Delete a string from a line.
		 * @param line : Index of the query line.
		 * @param position : Position of the first character on the line.
		 * @param length : Length of the deleted string.
		 **/
		void Delete( nUInt line, nUInt position, nUInt length );

	private:
		/** 
		 * CreateLine function
		 * @author : ALVES Quentin
		 * @note : Create a new line after the last line, this will automaticly add empty lines.
		 * @param string : The query line text.
		 * @parma line : Index of the query new line.
		 * @return : NutTextDocument& 
		 **/
		NutTextDocument& CreateLine( const std::string& string, nUInt line );

	public:
		/**
		 * GetName const function
		 * @author : ALVES Quentin
		 * @note : Get the name of the document.
		 * @return : const std::string&
		 **/
		const std::string& GetName( ) const;

		/**
		 * GetSize const function
		 * @author : ALVES Quentin
		 * @note : Get the current document size.
		 * @return : const nUInt
		 **/
		const nUInt GetSize( ) const;

		/**
		 * GetCursor const function
		 * @author : ALVES Quentin
		 * @note : Get the saved cursor of the document.
		 * @return : const NutTextCursor&
		 **/
		const NutTextCursor& GetCursor( ) const;

		/**
		 * GetLine const function
		 * @author : ALVES Quentin
		 * @note : Get a line of the document or the last if index is out of bound.
		 * @param query_id : index of the query line.
		 * @return : const NutTextCursor&
		 **/
		Line& GetLine( nUInt query_id ) const;

		/**
		 * GetLines const function
		 * @author : ALVES Quentin
		 * @note : Get all lines of the docuement.
		 * @return : const Lines&
		 **/
		const Lines& GetLines( ) const;

		/**
		 * GetLineSize const function
		 * @author : ALVES Quentin
		 * @note : Get the size if a line.
		 * @return : const nUInt 
		 **/
		const nUInt GetLineSize( nUInt query_id ) const;

	public:
		/**
		 * operator nString const
		 * @author : ALVES Quentin
		 * @note : Conversion operator for nString.
		 * @return : nString
		 **/
		operator nString( ) const;

		/**
		 * operator const NutTextCursor& const
		 * @author : ALVES Quentin
		 * @note : Conversion operator for const NutTextCursor&.
		 * @return : const NutTextCursor&
		 **/
		operator const NutTextCursor&( ) const;

		/**
		 * operator const nUInt const
		 * @author : ALVES Quentin
		 * @note : Conversion operator for const nUInt.
		 * @return : const nUInt
		 **/
		operator const nUInt( ) const;

		/**
		 * operator const Lines& const
		 * @author : ALVES Quentin
		 * @note : Conversion operator for const Lines&.
		 * @return : const Lines&
		 **/
		operator const Lines&( ) const;

		/**
		 * operator[] const
		 * @author : ALVES Quentin
		 * @note : Get a line of the document or the last if index is out of bound.
		 * @param query_id : index of the query line.
		 * @return : Line&
		 **/
		Line& operator[]( nUInt query_id ) const;

		/**
		 * operator+=
		 * @author : ALVES Quentin
		 * @note : Add a new line on the end of the document.
		 * @param string : New line content.
		 * @return : NutTextDocument&
		 **/
		NutTextDocument& operator+=( nString string );

		/**
		 * operator+=
		 * @author : ALVES Quentin
		 * @note : Add a new line on the end of the document.
		 * @param string : New line content.
		 * @return : NutTextDocument&
		 **/
		NutTextDocument& operator+=( const std::string& string );

	};

#endif
