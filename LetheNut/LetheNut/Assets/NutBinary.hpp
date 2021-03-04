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

#ifndef _IGS_NUT_ASSET_BINARY_HPP_
#define _IGS_NUT_ASSET_BINARY_HPP_

	#include "NutAsset.hpp"
	/**
	 * NutBinary class [ NutAsset ]
	 * @author : ALVES Quentin
	 * @node : Defined Nut Binary core class.
	 **/
	NUT_ASSET( NutBinary ) {

	private:
		nPointer data;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param alias : Alias of the asset.
		 **/
		NutBinary( nString alias );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutBinary( ) = default;

		/**
		 * Load function
		 * @author : ALVES Quentin
		 * @note : Load the current asset.
		 * @param editor : Pointer to current editor.
		 * @param path : Path to the query asset.
		 * @return : bool
		 **/
		virtual bool Load( NutEditor* editor, nString path ) override;

		/**
		 * Write function
		 * @author : ALVES Quentin
		 * @note : Write the current asset.
		 * @param editor : Pointer to current editor.
		 * @param path : Path to the query asset.
		 * @return : bool
		 **/
		virtual bool Write( NutEditor* editor, nString path ) override;

		/**
		 * Cleanup method
		 * @author : ALVES Quentin
		 * @note : Cleanup the current asset.
		 **/
		virtual void Cleanup( ) override;

	public:
		/**
		 * Get const function
		 * @author : ALVES Quentin
		 * @note : Get current binary pointer.
		 * @return : nPointer
		 **/
		nPointer Get( ) const;

	};

#endif
