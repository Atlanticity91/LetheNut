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

#ifndef _IGS_NUT_TOOL_HPP_
#define _IGS_NUT_TOOL_HPP_

	#include <LetheNut/UI/NutPanel.hpp>

	#define NUT_TOOL( NAME, ... ) NUT_CLASS( NAME, NutTool, __VA_ARGS__ )

	/**
	 * NutTool class [ NutPanel ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut tool core class.
	 **/
	class NUT_API NutTool : public NutPanel {

		friend class NutPopup;
		friend class NutEditor;

	protected:
		bool is_running;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current tool.
		 **/
		NutTool( nString name );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current tool.
		 * @param padding : Current padding value.
		 **/
		NutTool( nString name, const ImVec2& padding );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current tool.
		 * @param padding : Current padding value.
		 **/
		NutTool( nString name, const ImVec2&& padding );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutTool( ) = default;

	protected:
		/**
		 * Process virtual method
		 * @author : ALVES Quentin
		 * @note : Process the current tool.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void Process( class NutEditor* editor );

	public:
		/**
		 * GetIsRunning inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the current tool is running.
		 * @return : bool
		 **/
		inline bool GetIsRunning( ) const;

	};

#endif
