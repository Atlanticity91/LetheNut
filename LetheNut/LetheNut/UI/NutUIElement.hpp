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

#ifndef _IGS_NUT_UI_ELEMENT_HPP_
#define _IGS_NUT_UI_ELEMENT_HPP_

	#include <LetheNut/Utils/NutContext.hpp>
	#include <LetheNut/Utils/NutElement.hpp>

	#include "Menus/NutMenuManager.hpp"
	#include "Modals/NutModalManager.hpp"

	#define NUT_UI_ELEMENT( NAME ) class NUT_API NAME : public NutUIElement

	/**
	 * NutUIElement class [ NutMenuManager, NutModalManager ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut UI Element core class.
	 **/
	NUT_ELEMENT( NutUIElement ), public NutMenuManager, public NutModalManager {

		friend class NutWindow;
		friend class NutEditor;

	private:
		bool is_open;
		NutContext* context;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the element.
		 **/
		NutUIElement( nString label );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutUIElement( ) = default;

		/**
		 * Reset method
		 * @author : ALVES Quentin
		 * @note : Reset the current element state. 
		 **/
		void Reset( );

		/**
		 * SetContext method
		 * @author : ALVES Quentin
		 * @note : Set current element context.
		 * @param context : New context value.
		 **/
		void SetContext( NutContext* context );

	protected:
		/**
		 * OnCreateMenus method
		 * @author : ALVES Quentin
		 * @note : Create menus of the element.
		 **/
		virtual void OnCreateMenus( );

		/**
		 * OnCreateModals method
		 * @author : ALVES Quentin
		 * @note : Create modals of the element.
		 **/
		virtual void OnCreateModals( );

	private:
		/**
		 * OnCreateUI  method
		 * @author : ALVES Quentin
		 * @note : Create current element menus and modals.
		 **/
		void OnCreateUI( );

	public:
		/**
		 * GetIsOpen const function
		 * @author : ALVES Quentin
		 * @note : Get current element is open.
		 * @return : bool
		 **/
		bool GetIsOpen( ) const;
		
		/**
		 * GetContext const function
		 * @author : ALVES Quentin
		 * @note : Get current element context.
		 * @return : NutContext*
		 **/
		NutContext* GetContext( ) const;

	protected:
		/**
		 * GetState const function
		 * @author : ALVES Quentin
		 * @note : Get current element state.
		 * @return : bool*
		 **/
		bool* GetState( );

	};

#endif
