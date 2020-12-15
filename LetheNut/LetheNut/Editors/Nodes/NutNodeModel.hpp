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

#ifndef _IGS_NUT_NODE_MODEL_HPP_
#define _IGS_NUT_NODE_MODEL_HPP_
	
	#include "NutNodePin.hpp"

	enum ENutNodeTypes : nUInt {

		ENT_FUNCTION,
		ENT_EVENT,
		ENT_CONSTANT,
		ENT_VARIABLE,
		ENT_BRANCH,
		ENT_SWITCH,
		ENT_OPERATION,

	};

	NUT_ELEMENT( NutNodeModel ) {

	public:
		using PinList = std::vector<NutNodePin>;

	private:
		ENutNodeTypes type;
		nString description;
		PinList inputs;
		PinList outputs;

	public:
		NutNodeModel( );

		NutNodeModel( const NutNodeModel& other );

		NutNodeModel( ENutNodeTypes type, nString name, nString description );

		virtual ~NutNodeModel( );

		virtual void AddIn( const NutNodePin& pin );

		inline void AddIn( const NutNodePin&& pin );

		inline void AddIn( bool is_array, ENutPinTypes type, nString name, nString description );

		void ConnectIn( nUInt query_id );

		void DisConnectIn( nUInt query_id );

		void ToggleIn( nUInt query_id );

		virtual void AddOut( const NutNodePin & pin );

		inline void AddOut( const NutNodePin && pin );

		inline void AddOut( bool is_array, ENutPinTypes type, nString name, nString description );

		void ConnectOut( nUInt query_id );

		void DisConnectOut( nUInt query_id );

		void ToggleOut( nUInt query_id );

	public:
		const ImVec2 GetPosition( ) const;

		ENutNodeTypes GetType( ) const;

		nString GetDescription( ) const;

		bool HasInPin( nUInt query_id ) const;

		const NutNodePin& GetInPin( nUInt query_id ) const;

		const PinList& GetInPins( ) const;

		bool HasOutPin( nUInt query_id ) const;

		const NutNodePin& GetOutPin( nUInt query_id ) const;

		const PinList& GetOutPins( ) const;

	};

#endif
