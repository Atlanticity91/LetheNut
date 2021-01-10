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

#ifndef _IGS_NUT_MENU_HPP_
#define _IGS_NUT_MENU_HPP_

	#include <LetheNut/Vendor/ImGUI.hpp>

	#include "NutMenuItem.hpp"

	NUT_ELEMENT( NutMenu final ) {

	private:
		bool is_visible;
		bool is_locked;
		NutList<NutMenuItem> items;

	public:
		NutMenu( nString label, bool is_visible );

		~NutMenu( ) = default;

		void Append( );

		void Append( nString label, NutMenu* menu );

		void Append( nString label, nString shortcut, NutItemCallback on_click );

		void Append( nString label, bool state, NutItemCallback on_mark, NutItemCallback on_unmark );

		void Lock( );

		void UnLock( );

		void Lock( nString label );

		void UnLock( nString label );

		void OnRender( NutEditor* editor, NutWindow* window, NutPanel* parent );

	private:
		void OnRenderSubMenu( NutMenuItem& item, NutEditor* editor, NutWindow* window, NutPanel* parent );

		void OnRenderButton( NutMenuItem& item, NutEditor* editor, NutWindow* window, NutPanel* parent );

		void OnRenderCheckbox( NutMenuItem& item , NutEditor* editor, NutWindow* window, NutPanel* parent );

	public:
		template<typename OnClick>
		void Append( nString label, nString shortcut, OnClick&& on_click );

		template<typename OnMark>
		void Append( nString label, bool state, OnMark&& on_mark );

		template<typename OnMark, typename OnUnMark>
		void Append( nString label, bool state, OnMark&& on_mark, OnUnMark&& on_unmark );

	public:
		bool GetIsVisible( ) const;

	};

	#include <Templates/NutMenu.hpp>

#endif
