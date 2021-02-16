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

	#include "NutElement.hpp"
	#include "NutPlatformLib.hpp"

	class NutEditor;

	/**
	 * NutModule class
	 * @author : ALVES Quentin
	 * @node : Defined NutModule core class.
	 **/
	NUT_ELEMENT( NutModule ) {

		friend class NutEditor;

	private:
		bool is_active;
		NutPlatformLib* importer;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param importer : Pointer to current module importer.
		 * @param name : Name of the current module.
		 **/
		NutModule( NutPlatformLib* importer, nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutModule( ) = default;

		/**
		 * Enable method
		 * @author : ALVES Quentin
		 * @node : Enable the current module.
		 * @param editor : Pointer to current editor.
		 **/
		void Enable( NutEditor* editor );

		/**
		 * Disable method
		 * @author : ALVES Quentin
		 * @node : Disable the current module.
		 * @param editor : Pointer to current editor.
		 **/
		void Disable( NutEditor* editor );

	protected:
		/**
		 * OnCreate pure-virtual method
		 * @author : ALVES Quentin
		 * @node : Called once when the module is created.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnCreate( NutEditor* editor ) = 0;

		/**
		 * OnEnable pure-virtual method
		 * @author : ALVES Quentin
		 * @node : Called every time the module is enabled.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEnable( NutEditor* editor ) = 0;

		/**
		 * OnDisable pure-virtual method
		 * @author : ALVES Quentin
		 * @node : Called every time the module is disable.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnDisable( NutEditor* editor ) = 0;

		/**
		 * OnDestroy pure-virtual method
		 * @author : ALVES Quentin
		 * @node : Called once when the module is destoyed.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnDestroy( NutEditor* editor ) = 0;

		/**
		 * Process pure-virtual method
		 * @author : ALVES Quentin
		 * @node : Called every tick of the editor when the module is enabled.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Process( NutEditor* editor ) = 0;

	public:
		/**
		 * GetState virtual const function
		 * @author : ALVES Quentin
		 * @node : Get state of the current module.
		 * @return : bool
		 **/
		virtual bool GetState( ) const;

		/**
		 * GetImporter const function
		 * @author : ALVES Quentin
		 * @node : Get current library importer.
		 * @return : NutPlatformLib*
		 **/
		NutPlatformLib* GetImporter( ) const;

	public:
		/**
		 * cast operator
		 * @author : ALVES Quentin
		 * @node : Cast the module to boolean aka get state 
				   of the current module.
		 * @return : bool
		 **/
		operator bool( ) const;

	};

#endif
