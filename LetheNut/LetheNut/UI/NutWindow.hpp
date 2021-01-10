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

#ifndef _IGS_NUT_WINDOW_HPP_
#define _IGS_NUT_WINDOW_HPP_

	#include <LetheNut/Vendor/GLFW.hpp>

	#include "NutPanel.hpp"

	#define NUT_WINDOW( NAME ) class NUT_API NAME : public NutWindow

	NUT_UI_ELEMENT( NutWindow ) {

		friend bool ImGUI::Window( NutWindow* );
		friend class NutEditor;

	private:
		mutable GLFW::Window handle;
		mutable NutList<NutPanel*> panels;

	public:
		NutWindow( nString name, const nInt width, const nInt height );

		virtual ~NutWindow( );

		void Enable( NutEditor* editor, nString panel );

		void Disable( NutEditor* editor, nString panel );

		void Destroy( NutEditor* editor, nString panel );

	protected:
		bool Open( );

		virtual void OnCreate( NutEditor* editor ) = 0;

		virtual bool OnDestroy( NutEditor* editor );

		virtual void OnRender( NutEditor* editor );

	public:
		template<typename Type = NutPanel, typename... Args>
		Type* Create( NutEditor* editor, Args... args );

	public:
		GLFW::Window& GetHandle( ) const;

		bool ShouldRun( ) const;

		NutList<NutPanel*>& GetPanels( ) const;

		NutPanel* GetPanel( nString name ) const;

	public:
		template<typename Type = NutPanel>
		Type* GetPanel( nString panel );

	};

	#include <Templates/NutWindow.hpp>

#endif
