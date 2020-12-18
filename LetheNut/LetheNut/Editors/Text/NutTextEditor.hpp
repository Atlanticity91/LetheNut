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

#ifndef _IGS_NUT_TEXT_EDITOR_HPP_
#define _IGS_NUT_TEXT_EDITOR_HPP_

	#include <LetheNut/Tools/NutTool.hpp>

	#include "NutTextDocument.hpp"
	#include "NutTextParser.hpp"

	/**
	 * NutTextContext struct
	 * @author : ALVES Quentin
	 * @note : Defined nut text editor renderer.
	 **/
	struct NutTextContext {

		NutTextCursor Cursor;
		nTimePoint Record;
		char LineNumbers[ 16 ];
		float LeftPadding;
		ImVec2 Region;
		ImVec2 FontSize;
		ImVec2 CharAdvance;
		ImVec2 SpaceAdvance;

	};

	/**
	 * NutTextEditor class [ NutTool ]
	 * @author : ALVES Quentin
	 * @note : Defined nut text editor core class.
	 **/
	NUT_TOOL( NutTextEditor ) {

		using DocumentList = std::vector<NutTextDocument>;

	private:
		nUInt document_id;
		NutTextStyle* style;
		NutTextParser* parser;
		mutable NutTextContext renderer;
		mutable DocumentList documents;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutTextEditor( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutTextEditor( );

		/**
		 * Create virtual method
		 * @author : ALVES Quentin
		 * @note : Create a new document.
		 **/
		virtual void Create( const std::string& name );

		/**
		 * Prev virtual method
		 * @author : ALVES Quentin
		 * @note : Make the previous document on the list as current or the last.
		 **/
		virtual void Prev( );

		/**
		 * Next virtual method
		 * @author : ALVES Quentin
		 * @note : Make the next document on the list as current or the first.
		 **/
		virtual void Next( );

		/**
		 * MoveUp virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor up.
		 **/
		virtual void MoveUp( );

		/**
		 * MoveUp virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor down.
		 **/
		virtual void MoveDown( );

		/**
		 * MoveLeft virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor left.
		 **/
		virtual void MoveLeft( );

		/**
		 * MoveRight virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor right.
		 **/
		virtual void MoveRight( );

		/**
		 * MoveTop virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor top.
		 **/
		virtual void MoveTop( );

		/**
		 * MoveBottom virtual method
		 * @author : ALVES Quentin
		 * @note : Move the cursor bottom.
		 **/
		virtual void MoveBottom( );

		/**
		 * SelectAll virtual method
		 * @author : ALVES Quentin
		 * @note : Select the entire document.
		 **/
		virtual void SelectAll( );

		/**
		 * Copy virtual method
		 * @author : ALVES Quentin
		 * @note : Copy the current selection.
		 **/
		virtual void Copy( );

		/**
		 * Cut virtual method
		 * @author : ALVES Quentin
		 * @note : Cut the current selection.
		 **/
		virtual void Cut( );

		/**
		 * Paste virtual method
		 * @author : ALVES Quentin
		 * @note : Paste the current selection.
		 **/
		virtual void Paste( );

		/**
		 * Undo virtual method
		 * @author : ALVES Quentin
		 * @note : Undo the current modification.
		 **/
		virtual void Undo( );

		/**
		 * Redo virtual method
		 * @author : ALVES Quentin
		 * @note : Redo the current modification.
		 **/
		virtual void Redo( );

	protected:
		virtual void Insert( char character );

		virtual void Delete( );

		/**
		 * InternalInputKeyboard virtual method
		 * @author : ALVES Quentin
		 * @note : Process current keyboard input.
		 **/
		virtual void InternalInputKeyboard( );

		/**
		 * InternalInputMouse virtual method
		 * @author : ALVES Quentin
		 * @note : Process current mouse input.
		 **/
		virtual void InternalInputMouse( );

		/**
		 * OnEditorRender override method
		 * @author : ALVES Quentin
		 * @note : Called once a frame to render ImGUI stuff.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorRender( NutEditor* editor ) override;

		/**
		 * InternalPrepare virtual method
		 * @author : ALVES Quentin
		 * @note : Prepare for rendering.
		 **/
		virtual void InternalPrepare( );

		/**
		 * InternalDraw virtual method
		 * @author : ALVES Quentin
		 * @note : Draw the current line indicateur and cursor.
		 * @param renderer : Current renderer.
		 * @param position : Position where rendering start.
		 **/
		virtual void InternalDraw( ImDrawList* renderer, ImVec2 position );

		/**
		 * InternalDraw virtual method
		 * @author : ALVES Quentin
		 * @note : Draw the current line indicateur and cursor.
		 * @param renderer : Current renderer.
		 * @param position : Position where rendering start.
		 * @param query_var : Query style variable.
		 * @param text : Text to display.
		 **/
		virtual void InternalDraw( ImDrawList* renderer, ImVec2 position, ENutTextStyleVars query_var, nString text );

		/**
		 * InternalDraw virtual method
		 * @author : ALVES Quentin
		 * @note : Draw the current line index.
		 * @param renderer : Current renderer.
		 * @param position : Position where rendering start.
		 * @param line_id : Index of the line to draw.
		 **/
		virtual void InternalDraw( ImDrawList* renderer, ImVec2 position, nUInt line_id );

		/**
		 * InternalDraw virtual method
		 * @author : ALVES Quentin
		 * @note : Draw the current line text.
		 * @param renderer : Current renderer.
		 * @param position : Position where rendering start.
		 * @param text : Text of the line to draw.
		 **/
		virtual void InternalDraw( ImDrawList* renderer, ImVec2 position, const std::string& text );

	private:
		/**
		 * Replace method
		 * @author : ALVES Quentin
		 * @note : Replace the current cursor on the end of the line.
		 **/
		void Replace( );

	public:
		/**
		 * SetStyle template method
		 * @author : ALVES Quentin
		 * @note : Set current editor style.
		 * @template Style : Query style instance.
		 **/
		template< typename Style = NutTextStyle >
		void SetStyle( );

		/**
		 * SetParser template method
		 * @author : ALVES Quentin
		 * @note : Set current editor style.
		 * @template Parser : Query parser instance.
		 **/
		template< typename Parser = NutTextParser >
		void SetParser( );

	public:
		/**
		 * GetStyle const function
		 * @author : ALVES Quentin
		 * @note : Get current nut text editor style.
		 * @return : const NutTextStyle*
		 **/
		const NutTextStyle* GetStyle( ) const;

		/**
		 * GetParser const function
		 * @author : ALVES Quentin
		 * @note : Get current nut text editor parser.
		 * @return : const NutTextParser*
		 **/
		const NutTextParser* GetParser( ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get a document by index.
		 * @param query_id : Index of the query document.
		 * @return : bool
		 **/
		bool Get( NutTextDocument& document, nUInt query_id ) const;

		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get a document by name.
		 * @param name : Name of the query document.
		 * @return : bool
		 **/
		bool Get( NutTextDocument& document, const std::string& query_name ) const;

	private:
		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get the current document.
		 * @return : NutTextDocument&
		 **/
		NutTextDocument& Get( ) const;

	public:
		/**
		 * operator[ ] const
		 * @author : ALVES Quentin
		 * @note : Get an open document from the editor.
		 * @param query_id : Index of the query document.
		 * @return : NutTextDocument*
		 **/
		NutTextDocument* operator[ ]( nUInt query_id ) const;

		/**
		 * operator[ ] const
		 * @author : ALVES Quentin
		 * @note : Get an open document by name from the editor.
		 * @param name : Query document name.
		 * @return : NutTextDocument*
		 **/
		NutTextDocument* operator[ ]( nString name ) const;

		/**
		 * operator[ ] const
		 * @author : ALVES Quentin
		 * @note : Get an open document by name from the editor.
		 * @param name : Query document name.
		 * @return : NutTextDocument*
		 **/
		NutTextDocument* operator[ ]( const std::string& name ) const;

		/**
		 * operator++
		 * @author : ALVES Quentin
		 * @note : Equivalent to calling Next.
		 * @return : NutTextEditor&
		 **/
		NutTextEditor& operator++( );

		/**
		 * operator--
		 * @author : ALVES Quentin
		 * @note : Equivalent to calling Prev.
		 * @return : NutTextEditor&
		 **/
		NutTextEditor& operator--( );

	};

	#include <Templates/NutTextEditor.hpp>

#endif
