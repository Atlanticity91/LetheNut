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

#ifndef _IGS_NUT_NODE_HPP_
#define _IGS_NUT_NODE_HPP_

	#include "NutNodeModel.hpp"

	/**
	 * NutNode final class
	 * @author : ALVES Quentin
	 * @note : Defined Nut Node class.
	 **/
	class NUT_API NutNode final {

	public:
		using PinList = NutNodeModel::PinList;

	private:
		ImVec2 position;
		NutNodeModel model;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param position : Position of the node.
		 * @param model : Current node model.
		 **/
		NutNode( ImVec2 position, const NutNodeModel& model );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutNode( );

		inline void ConnectIn( nUInt query_id );

		inline void DisConnectIn( nUInt query_id );

		inline void ToggleIn( nUInt query_id );

		inline void ConnectOut( nUInt query_id );

		inline void DisConnectOut( nUInt query_id );

		inline void ToggleOut( nUInt query_id );

	public:
		inline const ImVec2 GetPosition( ) const;

		inline ENutNodeTypes GetType( ) const;

		inline nString GetName( ) const;

		inline nString GetDescription( ) const;

		inline bool HasInPin( nUInt query_id ) const;

		inline const NutNodePin& GetInPin( nUInt query_id ) const;

		inline const PinList& GetInPins( ) const;

		inline bool HasOutPin( nUInt query_id ) const;

		inline const NutNodePin& GetOutPin( nUInt query_id ) const;

		inline const PinList& GetOutPins( ) const;

	};

#endif
