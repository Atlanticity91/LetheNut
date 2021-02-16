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

#ifndef _IGS_NUT_ELEMENT_HPP_
#define _IGS_NUT_ELEMENT_HPP_

	#include <LetheNut/NutCore.hpp>

	/**
	 * NUT_ELEMENT macro
	 * @author : ALVES Quentin
	 * @node : Helper for child class of NutElement.
	 * @param NAME : Name of the new class.
	 * @usage : 
	 *		NUT_ELEMENT( Test ) { ... };
	 * 
	 *	-> Create a Test class inherit from NutElement.
	 **/
	#define NUT_ELEMENT( NAME ) class NUT_API NAME : public NutElement

	class NutEditor;
	class NutModule;
	class NutLibrary;
	class NutWindow;
	class NutPanel;

	/**
	 * Nut_Element struct
	 * @author : ALVES Quentin
	 * @node : Defined core struct for NutElement struct.
	 **/
	struct NUT_API Nut_Element {

		nString label;
		NutHash hash;

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the element.
		 **/
		Nut_Element( nString label );

		/**
		 * GetHash const function
		 * @author : ALVES Quentin
		 * @note : Get Hash of the element.
		 * @return : NutHash
		 **/
		NutHash GetHash( ) const;

	};

	/**
	 * NutElement class
	 * @author : ALVES Quentin
	 * @node : Defined core class for NutElement class.
	 **/
	class NUT_API NutElement {

	private:
		NutHash hash;
		nString label;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param label : Label of the element.
		 **/
		NutElement( nString label );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutElement( ) = default;

	public:
		/**
		 * GetHash const function
		 * @author : ALVES Quentin
		 * @note : Get Hash of the element.
		 * @return : NutHash
		 **/
		NutHash GetHash( ) const;

		/**
		 * GetName const function
		 * @author : ALVES Quentin
		 * @note : Get name of the current element.
		 *		   Same as label but useful for name consistency.
		 * @return : nString
		 **/
		nString GetName( ) const;

		/**
		 * GetLabel const function
		 * @author : ALVES Quentin
		 * @note : Get label of the current element.
		 * @return : nString
		 **/
		nString GetLabel( ) const;

	};

#endif
