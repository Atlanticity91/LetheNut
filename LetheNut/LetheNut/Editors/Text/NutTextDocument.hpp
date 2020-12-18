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
		std::string path;
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
		NutTextDocument( const std::string& name );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the new document.
		 * @param path : Path to the document file.
		 **/
		NutTextDocument( const std::string& name, const std::string& path );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutTextDocument( ) = default;

		/**
		 * SetPath method
		 * @author : ALVES Quentin
		 * @note : Set the current docuemtn path value.
		 * @param path : Query document path.
		 **/
		void SetPath( const std::string& path );

		/**
		 * SetCursor method
		 * @author : ALVES Quentin
		 * @note : Set the current cursor instance value.
		 * @param cursor : Cursor to save.
		 **/
		void SetCursor( const NutTextCursor& cursor );

		void Append( char character );

		void Append( const std::string& text );

		void AppendTo( char character, nUInt line );

		void AppendTo( const std::string& text, nUInt line );

		void Insert( char character, nUInt line, nUInt position );

		void Insert( const std::string& text, nUInt line, nUInt position );

		void Merge( nUInt start_line, nUInt stop_line );

		void NewLine( );

		void Delete( nUInt line, nUInt position );

		void Erase( nUInt line, nUInt position, nUInt size );

		void Erase( nUInt from_line, nUInt from_position, nUInt to_line, nUInt to_position );

		void DeleteLine( nUInt line_id );

	public:
		/**
		 * GetName const function
		 * @author : ALVES Quentin
		 * @note : Get the name of the document.
		 * @return : const std::string&
		 **/
		const std::string& GetName( ) const;

		const std::string& GetPath( ) const;

		const NutTextCursor& GetCursor( ) const;

		const nUInt GetLineCount( ) const;

		const Lines& GetLines( ) const;

		const nUInt GetLineSize( nUInt line_id ) const;

		const std::string& GetLine( nUInt line_id ) const;

		const char At( nUInt line, nUInt position );

	public:
		operator nString( ) const;

		operator const std::string& ( ) const;

		operator nUInt( ) const;

		operator const NutTextCursor&( ) const;

		operator const Lines&( ) const;

		NutTextDocument& operator=( const NutTextCursor& cursor );

		NutTextDocument& operator+=( const std::string& text );

		NutTextDocument& operator+=( const std::string&& text );

	};

#endif
