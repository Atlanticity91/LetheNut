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

	#include <LetheNut/NutBasic.hpp>
	#include "NutMenuItem.hpp"

	class NutPanel;

	/**
	 * NutMenu final class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Menu core class.
	 **/
	NUT_ELEMENT( NutMenu ) {

		friend class NutPanel;

	private:
		mutable std::vector< class NutMenuItem > items;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutMenu( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutMenu( ) = default;

		/**
		 * CreateButton function
		 * @author : ALVES Quentin
		 * @note : Create a button on the current menu.
		 * @template Callback : Lambda capture.
		 * @param name : Name of the button.
		 * @param shortcut : Shortcut of the button.
		 * @param callback : Current callback lambda.
		 * @return : class NutMenu*
		 **/
		template< typename Callback >
		NutMenu* CreateButton( nString name, nString shortcut, Callback&& callback );

		/**
		 * CreateCheckbox template function
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template Mark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 * @return : class NutMenu*
		 **/
		template< typename Mark >
		NutMenu* CreateCheckbox( nString label, bool state, Mark&& mark );

		/**
		 * CreateCheckbox template function
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template Mark : Lambda capture.
		 * @template UnMark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 * @param unmark : Current unmark lambda.
		 * @return : class NutMenu*
		 **/
		template< typename Mark, typename UnMark >
		NutMenu* CreateCheckbox( nString label, bool state, Mark&& mark, UnMark&& unmark );

		/**
		 * CreateSeparator function
		 * @author : ALVES Quentin
		 * @note : Create a separator on the current menu.
		 * @return : class NutMenu*
		 **/
		class NutMenu* CreateSeparator( );

	protected:
		/**
		 * OnRender virtual method
		 * @author : ALVES Quentin
		 * @note : Render the current menu.
		 * @param editor : Pointer to current editor.
		 * @param parent : Pointer to panel that own the menu.
		 **/
		virtual void OnRender( NutEditor* editor, NutPanel& parent );

	public:
		/**
		 * GetItem const function
		 * @author : ALVES Quentin
		 * @note : Get an item of the menu.
		 * @param label : Label of the item.
		 * @return : class NutMenuItem*
		 **/
		class NutMenuItem* GetItem( nString label ) const;

	};

	#include <Templates/NutMenu.hpp>

#endif
