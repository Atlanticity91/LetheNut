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

#ifndef _IGS_NUT_NODE_HPP_
#define _IGS_NUT_NODE_HPP_

	#include <LetheNut/Vendor/ImGUI.hpp>

	template<size_t Inputs, size_t Outputs>
	class NutNode {

	private:
		ImGUI::ImNode data;
		ImGUI::ImNodePin inputs[ Inputs ];
		ImGUI::ImNodePin outputs[ Outputs ];

	public:
		NutNode( nString label, nString description, ImColor color )
			: NutNode( label, description, false, color, 0, 0 )
		{ }

		NutNode( nString label, nString description, bool is_centered, ImColor color ) 
			: NutNode( label, description, is_centered, color, 0, 0 )
		{ }

		NutNode( nString label, nString description, bool is_centered, ImColor color, nUByte column, nUByte row ) 
			: data( label, description, is_centered, color, column, row )
		{ 
			this->OnCreate( ); 

			for ( int i = 0; i < Inputs; i++ )
				this->inputs[ i ] = ImGUI::ImNodePin( ImGUI::EImNodePinTypes::EPT_TRIANGLE, "Test", ImColor{ 255, 32, 32, 255 } );

			for ( int i = 0; i < Outputs; i++ )
				this->outputs[ i ] = ImGUI::ImNodePin( ImGUI::EImNodePinTypes::EPT_TRIANGLE, "Test", ImColor{ 255, 32, 32, 255 } );
		}

		virtual ~NutNode( ) = default;

		virtual void OnRender( ImGUI::ImCanvas& canvas, ImGUI::ImNodeStyle& node_style, const ImVec2& position, bool is_selected ) {
			if ( ImGUI::Node( canvas, node_style, this->data, position ) ) {
				ImGui::BeginGroup( );
				for ( int idx = 0; idx < Inputs; idx++ )
					ImGUI::NodeInputPin( node_style, this->inputs[ idx ], false );
				ImGui::EndGroup( );
				ImGui::SameLine( );

				ImGui::BeginGroup( );
				for ( int odx = 0; odx < Outputs; odx++ )
					ImGUI::NodeOutputputPin( node_style, this->outputs[ odx ], true );
				ImGui::EndGroup( );

				ImGUI::EndNode( canvas, node_style, this->data, position, is_selected );
			}
		}

	protected:
		virtual void OnCreate( ) { };

	};

#endif
