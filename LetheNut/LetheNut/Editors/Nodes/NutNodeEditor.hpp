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

#ifndef _IGS_NUT_NODE_EDITOR_HPP_
#define _IGS_NUT_NODE_EDITOR_HPP_


	// TODO : [NutNodeEditor] Create Style for node editor.


	#include <LetheNut/Tools/NutTool.hpp>

	#include "NutNodeParser.hpp"
	#include "NutNodeStyle.hpp"

	NUT_TOOL( NutNodeEditor ) {

	private:
		ImGUI::ImCanvas canvas;
		NutNodeStyle* style;
		NutNodeParser* parser;
		std::vector<NutNode*> nodes;
		std::vector<NutNodeLink> links;

	public:
		NutNodeEditor( );

		virtual ~NutNodeEditor( );

		inline void CreateVar( ImVec2 position, ENutNodeTypes type, bool is_array, nString name );

		void CreateVar( ImVec2 position, nUInt type, bool is_array, nString name );

		void CreateLink( const NutNodeLink& link );

		void CreateLink( const NutNodeLink&& link );

		void CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin );

		void CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin, const ImVec4& color );

		void CreateLink( nUInt source_node, nUInt source_pin, nUInt destination_node, nUInt destination_pin, const ImVec4&& color );

	protected:
		virtual void Initialize( NutEditor* editor ) override;

		/**
		 * OnEditorProcess virtual method
		 * @author : ALVES Quentin
		 * @note : Process the current tool during rendering phase.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorProcess( NutEditor* editor ) override;

		/**
		 * OnEditorRender override method
		 * @author : ALVES Quentin
		 * @note : Called once a frame to render ImGUI stuff.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorRender( NutEditor* editor ) override;

		virtual void InternalDraw( const NutNode* node, ImTextureID node_bg );

		virtual void InternalDraw( const NutNode::PinList& pins, bool is_out, const float out_length );

		virtual void InternalDraw( const NutNodePin& pin, bool is_out, const float out_length );

		virtual void InternalDraw( const NutNodePin& pin, ImColor color );

		virtual void InternalDraw( const NutNodeLink& link );

	public:
		template< typename Type = class NutNodeStyle >
		void SetStyle( );

		template< typename Type = class NutNodeParser >
		void SetParser( );

	public:
		const NutNodeStyle* GetStyle( ) const;

	protected:
		virtual const ImVec2 GetPinPosition( bool is_output, nUInt node_id, nUInt pin_id ) const;

		virtual const ImColor GetPinColor( nUInt node_id, nUInt pin_id ) const;

	};

	#include <Templates/NutNodeEditor.hpp>

#endif
