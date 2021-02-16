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

	#include <LetheNut/UI/NutPanel.hpp>

	#include "NutTextDocument.hpp"
	#include "NutTextStyle.hpp"

	NUT_PANEL( NutTextEditor ) {

	private:
		size_t document_id;
		NutTextParser* parser;
		NutTextStyle* style;
		mutable NutList<NutTextDocument> documents;
		mutable NutList<NutTextStyle*> styles;

	public:
		NutTextEditor( );

		virtual ~NutTextEditor( ) = default;

		virtual void SetStyle( nString name );

		inline void SetStyle( const std::string& name );

		virtual void Create( const std::string& name );

		virtual void Open( NutEditor* editor, const std::string& path );

		inline void Save( NutEditor* editor, NutTextDocument* document );

		virtual void Save( NutEditor* editor, NutTextDocument& document );

		virtual void SaveAll( );

		virtual void Close( NutEditor* editor, const std::string& name );

		virtual void Undo( );

		virtual void Redo( );

		virtual void Copy( );

		virtual void Cut( );

		virtual void Paste( );

	public:
		static void OnOpen( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnSave( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnSaveAs( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnExit( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnUndo( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnRedo( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnCopy( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnCut( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

		static void OnPaste( const NutMenuItem& button, NutEditor* editor, NutWindow* window, NutPanel* panel );

	public:
		template<typename Type = NutTextStyle>
		void SetStyle( );

	protected:
		virtual void OnCreateMenus( ) override;

		virtual void OnCreateModals( ) override;

		virtual void OnCreate( NutEditor* editor, NutWindow* parent ) override;

		virtual bool OnDestroy( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnProcess( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnRender( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnKeyPressed( );

		virtual void OnMousePressed( );

		virtual void OnRender( NutTextDocument& document );

	public:
		NutList<NutTextStyle*>& GetStyles( ) const;

		NutTextStyle* GetStyle( ) const;

		NutList<NutTextDocument>& GetDocuments( ) const;

		NutTextDocument* GetDocument( const std::string& name ) const;

		NutTextDocument* GetCurrent( ) const;

	};

	#include <Templates/NutTextEditor.hpp>

#endif
