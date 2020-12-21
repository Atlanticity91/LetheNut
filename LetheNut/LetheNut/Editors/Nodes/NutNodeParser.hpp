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

#ifndef _IGS_NUT_NODE_PARSER_HPP_
#define _IGS_NUT_NODE_PARSER_HPP_

	#include "NutNode.hpp"

	#define NUT_NODE_PARSER( NAME, ... ) NUT_CLASS( NAME,NutNodeParser, __VA_ARGS__ ) 

	enum ETypeMatches : nUInt {

		ETM_MATCH = 0,
		ETM_NONE,
		ETM_DOWNCAST,
		ETM_UPCAST

	};

	/**
	 * NutNodeParser class [ NutBasic ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Node Parser core class.
	 **/
	NUT_ELEMENT( NutNodeParser ) {

		using NodeList = std::vector<NutNode*>;

	protected:
		mutable std::vector<NutNodeModel> models;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutNodeParser( );
		
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the node parser.
		 **/
		NutNodeParser( nString name );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutNodeParser( );

		/**
		 * Initialize virtual method
		 * @author : ALVES Quentin
		 * @note : Initialize current node parser.
		 **/
		virtual void Initialize( );

		virtual void CreateVar( ENutPinTypes type, bool is_array, nString name );

		virtual void Parse( const NodeList& nodes );

	protected:
		/**
		 * Create virtual function
		 * @author : ALVES Quentin
		 * @note : Create a new node model.
		 * @param type : Type of the new node model.
		 * @param name : Name of the new node model.
		 * @param description : Description of the new node model.
		 * @return : NutNodeModel*
		 **/
		virtual NutNodeModel* Create( ENutNodeTypes type, nString name, nString description );

		/**
		 * Create virtual function
		 * @author : ALVES Quentin
		 * @note : Create a new node model.
		 * @param name : Name of the new node model.
		 * @param description : Description of the new node model.
		 * @return : NutNodeModel*
		 **/
		inline NutNodeModel* Create( nString name, nString description );

		virtual void CreateOperation( ENutPinTypes type, nString name, nString description );

		virtual void CreateClamp( ENutPinTypes type, nString name );

		virtual void CreateSplit( nString name, ENutPinTypes in, ENutPinTypes out, std::vector<nString> out_names );

		virtual void CreateLerp( ENutPinTypes type, nString name );

		virtual void CreateForeach( ENutPinTypes type, nString name );

	public:
		virtual const ETypeMatches TypeMatch( ENutPinTypes left, ENutPinTypes right ) const;

		/**
		 * GetModelCount const function
		 * @author : ALVES Quentin
		 * @note : Get current parser model count.
		 * @return : const nUInt
		 **/
		const nUInt GetModelCount( ) const;

		/**
		 * GetModel const function
		 * @author : ALVES Quentin
		 * @note : Get a node model from current parser.
		 * @param query_id : Index of the query model.
		 * @return : const NutNodeModel*
		 **/
		const NutNodeModel* GetModel( nUInt query_id ) const;

	};

#endif
