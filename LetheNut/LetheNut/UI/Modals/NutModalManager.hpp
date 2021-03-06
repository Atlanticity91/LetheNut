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

#ifndef _IGS_NUT_MODAL_MANAGER_HPP_
#define _IGS_NUT_MODAL_MANAGER_HPP_

	#include "NutModal.hpp"

	/**
	 * NutModalManager class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Modal Manager core class.
	 **/
	class NUT_API NutModalManager {

	private:
		NutList<NutModal> modals;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutModalManager( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutModalManager( ) = default;

	protected:
		/**
		 * CreateModal function
		 * @author : ALVES Quentin
		 * @note : Create a new modal.
		 * @param label : Label of the new modal.
		 * @return : NutModal*
		 **/
		NutModal* CreateModal( nString label );

		/**
		 * OnRenderModal function
		 * @author : ALVES Quentin
		 * @note : Render a modal.
		 * @param editor : Current editor pointer.
		 * @param window : Current modal window.
		 * @param parent : Current modal panel.
		 * @param label : Query modal label.
		 * @return : bool
		 **/
		bool OnRenderModal( NutEditor* editor, NutWindow* window, NutPanel* parent, nString label );

	public:
		/**
		 * GetModal const function
		 * @author : ALVES Quentin
		 * @note : Get a modal.
		 * @param label : Label of the modal.
		 * @return : NutModal*
		 **/
		const NutModal* GetModal( nString label ) const;

	};

#endif
