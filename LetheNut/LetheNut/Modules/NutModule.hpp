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

#ifndef _IGS_NUT_MODULE_HPP_
#define _IGS_NUT_MODULE_HPP_

	#include <LetheNut/NutBasic.hpp>

	#define NUT_MODULE( NAME, ... ) NUT_CLASS( NAME, NutModule, __VA_ARGS__ )

	/**
	 * NutModule class [ NutBasic ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Module module core class.
	 **/
	NUT_ELEMENT( NutModule ) {

		friend class NutEditor;
		friend class NutKernel;

	protected:
		bool is_active;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current module.
		 **/
		NutModule( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutModule( ) = default;

		/**
		 * Enable virtual method
		 * @author : ALVES Quentin
		 * @note : Enable the current panel.
		 **/
		virtual void Enable( );

		/**
		 * Disable virtual method
		 * @author : ALVES Quentin
		 * @note : Disable the current panel.
		 **/
		virtual void Disable( );

	protected:
		/**
		 * Initialize pure-virtual method
		 * @author : ALVES Quentin
		 * @note : Initialize the current kernel module.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Initialize( NutEditor* editor ) = 0;

		/**
		 * OnCreate virtual method
		 * @author : ALVES Quentin
		 * @note : On create the current module
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnCreate( NutEditor* editor ) = 0;

		/**
		 * Process virtual method
		 * @author : ALVES Quentin
		 * @note : Process the current module
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Process( NutEditor* editor ) = 0;

	public:
		/**
		 * GetIsActive inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current module is active.
		 * @return : bool
		 **/
		inline bool GetIsActive( ) const;

	private:
		/**
		 * GetActive inline const function
		 * @author : ALVES Quentin
		 * @note : Get reference to module is active.
		 * @return : const bool&
		 **/
		inline const bool& GetActive( ) const;

	};

#endif
