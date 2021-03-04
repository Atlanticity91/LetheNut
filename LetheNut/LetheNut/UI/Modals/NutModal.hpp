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
 * Copyright (C) 2021 ALVES Quentin.
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

#ifndef _IGS_NUT_MODAL_HPP_
#define _IGS_NUT_MODAL_HPP_

	#include <LetheNut/Utils/NutList.hpp>
	#include <LetheNut/Vendor/ImGUI.hpp>

	typedef void (*NutModalContent)( NutEditor*, NutWindow*, NutPanel* );
	typedef bool (*NutModalOnClick)( NutEditor*, NutWindow*, NutPanel* );

	/**
	 * NutModalButton struct
	 * @author : ALVES Quentin
	 * @note : Defined Nut Modal Button struct.
	 **/
	struct NUT_API NutModalButton {

		nString label;
		bool prevent_close;
		NutModalOnClick on_click;

	};

	/**
	 * NutModal final class [ NutElement ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Modal core class.
	 **/
	NUT_ELEMENT( NutModal final ) {

	private:
		NutModalContent content;
		std::vector<NutModalButton> buttons;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the style.
		 **/
		NutModal( nString label );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutModal( ) = default;

		/**
		 * SetContent method
		 * @author : ALVES Quentin
		 * @note : Set the modal content.
		 * @param content : Current modal content.
		 **/
		void SetContent( NutModalContent content );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a button.
		 * @param label : Label of the button.
		 * @param prevent_close : True to prevent the modal to close.
		 * @param on_click : Callback when button is clicked.
		 **/
		void Create( nString label, bool prevent_close, NutModalOnClick on_click );

	public:
		/**
		 * SetContent method
		 * @author : ALVES Quentin
		 * @note : Set the modal content.
		 * @template Content : Lambda capture.
		 * @param content : Current modal content.
		 **/
		template<typename Content>
		void SetContent( Content&& content );

		/**
		 * Create method
		 * @author : ALVES Quentin
		 * @note : Create a button.
		 * @template on_click : Lambda capture.
		 * @param label : Label of the button.
		 * @param prevent_close : True to prevent the modal to close.
		 * @param on_click : Callback when button is clicked.
		 **/
		template<typename OnClick>
		void Create( nString label, bool prevent_close, OnClick&& on_click );

	public:
		/**
		 * OnRender function
		 * @author : ALVES Quentin
		 * @note : On modal render.
		 * @param editor : Current editor pointer.
		 * @param window : Current modal window.
		 * @param parent : Current modal panel.
		 * @return : bool
		 **/
		bool OnRender( NutEditor* editor, NutWindow* window, NutPanel* parent );

	public:
		/**
		 * GetIsValid const function
		 * @author : ALVES Quentin
		 * @note : Get if the current modal is valid.
		 * @return : bool
		 **/
		bool GetIsValid( ) const;

	};

	#include <Templates/NutModal.hpp>

#endif
