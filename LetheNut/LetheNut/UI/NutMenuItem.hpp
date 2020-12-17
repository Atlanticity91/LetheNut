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

#ifndef _IGS_NUT_MENU_ITEM_HPP_
#define _IGS_NUT_MENU_ITEM_HPP_

	#include <LetheNut/NutBasic.hpp>

	#define NO_SHORTCUT nullptr
	#define NO_CALLBACK nullptr

	/**
	 * NutItemCallback prototype
	 * @author : ALVES Quentin
	 * @note : Defined menu item callback.
	 * @param item : Reference of the item that use the callback.
	 * @param editor : Pointer to current editor.
	 * @param parent : Reference to the panel that contain the menu.
	 **/
	typedef void ( *NutItemCallback )( class NutMenuItem& item, class NutEditor* editor, class NutPanel& parent );

	/**
	 * NutMenuItem final class [ NutBasic ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Menu Item core class.
	 **/
	NUT_ELEMENT( NutMenuItem ) {

	private:
		std::bitset< 8 > type;
		nString shortcut;
		bool checkbox;
		NutItemCallback callback;
		NutItemCallback unmark;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @note : Use to create a separator.
		 **/
		NutMenuItem( );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @note : Use to create a button.
		 * @param name : Name of the button.
		 * @param shortcut : Shortcut of the button.
		 **/
		NutMenuItem( nString name, nString shortcut );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @note : Use to create a checkbox.
		 * @param name : Name of the button.
		 * @param state : Default state of the checkbox.
		 * @param mark : Current mark callback.
		 **/
		NutMenuItem( nString name, bool state );

		/**
		 * SetCallback function
		 * @author : ALVES Quentin
		 * @note : Set the callback of the current menu item.
		 * @param callback : Nullptr to make no callback or callback address.
		 * @return : class NutMenuItem*
		 **/
		class NutMenuItem* SetCallback( NutItemCallback callback );

		/**
		 * SetMark function
		 * @author : ALVES Quentin
		 * @note : Set the mark callback of the current menu item.
		 * @param callback : Nullptr to make no callback or callback address.
		 * @return : class NutMenuItem*
		 **/
		class NutMenuItem* SetMark( NutItemCallback callback );

		/**
		 * SetUnMark function
		 * @author : ALVES Quentin
		 * @note : Set the unmark callback of the current menu item.
		 * @param callback : Nullptr to make no callback or callback address.
		 * @return : class NutMenuItem*
		 **/
		class NutMenuItem* SetUnMark( NutItemCallback callback );

		/**
		 * Process method
		 * @author : ALVES Quentin
		 * @note : Process the callback of the current menu item.
		 * @param editor : Pointer to current editor.
		 * @param parent : Reference to the panel that contain the menu.
		 **/
		void Process( NutEditor* editor, class NutPanel& parent );

	public:
		/**
		 * SetCallback template function
		 * @author : ALVES Quentin
		 * @note : Set the callback of the current menu item.
		 * @template Callback : Lambda capture type.
		 * @param callback : Lambda that represent the item callback.
		 * @return : NutMenuItem*
		 **/
		template< typename Callback >
		NutMenuItem* SetCallback( Callback&& callback );

		/**
		 * SetMark template function
		 * @author : ALVES Quentin
		 * @note : Set the mark callback of the current menu item.
		 * @template Callback : Lambda capture type.
		 * @param callback : Lambda that represent the item callback.
		 * @return : NutMenuItem*
		 **/
		template< typename Callback >
		NutMenuItem* SetMark( Callback&& callback );

		/**
		 * SetUnMark template function
		 * @author : ALVES Quentin
		 * @note : Set the unmark callback of the current menu item.
		 * @template Callback : Lambda capture type.
		 * @param callback : Lambda that represent the item callback.
		 * @return : NutMenuItem*
		 **/
		template< typename Callback >
		NutMenuItem* SetUnMark( Callback && callback );

	public:
		/**
		 * IsSeparator inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current menu item is a separator.
		 * @return : bool
		 **/
		inline bool IsSeparator( ) const;

		/**
		 * IsButton inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current menu item is a button.
		 * @return : bool
		 **/
		inline bool IsButton( ) const;

		/**
		 * IsCheckbox inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current menu item is a checkbox.
		 * @return : bool
		 **/
		 inline bool IsCheckbox( ) const;

		/**
		 * GetType inline const function
		 * @author : ALVES Quentin
		 * @note : Get the type of the current menu item.
		 * @return : std::bitset< 8 >
		 **/
		 inline std::bitset< 8 > GetType( ) const;

		/**
		 * GetShortcut inline const function
		 * @author : ALVES Quentin
		 * @note : Get the shortcut of the current menu item.
		 * @return : nString
		 **/
		 inline nString GetShortcut( ) const;

		/**
		 * GetState inline const function
		 * @author : ALVES Quentin
		 * @note : Get the state of the current menu item.
		 * @return : bool
		 **/
		 inline bool GetState( ) const;

		/**
		 * GetState inline function
		 * @author : ALVES Quentin
		 * @note : Get the reference of state boolean from the current menu item.
		 * @return : bool*
		 **/
		 inline bool& GetState( );

		/**
		 * HasCallback inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current menu item has a callback.
		 * @return : bool
		 **/
		 inline bool HasCallback( ) const;

		/**
		 * Get inline const function
		 * @author : ALVES Quentin
		 * @note : Get the current menu item callback.
		 * @return : NutItemCallback
		 **/
		 inline NutItemCallback Get( ) const;

		 inline NutItemCallback GetMark( ) const;

		 inline NutItemCallback GetUnMark( ) const;

	};

	#include <Templates/NutMenuItem.hpp>

#endif
