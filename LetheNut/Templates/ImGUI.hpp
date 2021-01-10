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

#ifndef _IGS_NUT_IMGUI_IMP_HPP_
#define _IGS_NUT_IMGUI_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename... Args>
	void ImGUI::Tooltip( nString format, Args... args ) {
		auto color = ImColor{ ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] };

		ImGUI::Tooltip( color, format, args... );
	}

	template<typename... Args>
	void ImGUI::Tooltip( const ImColor& foreground, nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) && !ImGUI::GetIsSkiped( ) && ImGui::IsMousePosValid( ) && ImGui::IsItemHovered( ) ) {
			ImGUI::Tooltip( );
			ImGUI::Text( foreground, format, args... );
			ImGUI::EndTooltip( );
		}
	}

	template<typename... Args>
	void ImGUI::Text( const ImVec4& foreground, const std::string_view& text ) {
		ImGUI::Text( ImColor{ foreground }, text );
	}

	template<typename... Args>
	void ImGUI::Text( const ImVec4& foreground, const ImVec4& background, const std::string_view& text ) {
		ImGUI::Text( ImColor{ foreground }, ImColor{ background }, text );
	}

	template<typename... Args>
	void ImGUI::Text( const ImColor& foreground, const std::string_view& text ) {
		if ( !text.empty( ) && !ImGUI::GetIsSkiped( ) ) {
			char buffer[ 1024 ];
			strncpy_s( buffer, text.data( ), text.size( ) );

			ImGui::PushStyleColor( ImGuiCol_Text, foreground.Value );
			ImGui::Text( buffer );
			ImGui::PopStyleColor( );
		}
	}

	template<typename... Args>
	void ImGUI::Text( const ImColor& foreground, const ImColor& background, const std::string_view& text ) {
		if ( !text.empty( ) && !ImGUI::GetIsSkiped( ) ) {
			char buffer[ 1024 ];
			strncpy_s( buffer, text.data( ), text.size( ) );

			const auto pos = ImGui::GetCursorScreenPos( );
			const auto size = ImGUI::GetTextSize( buffer );

			ImGui::GetWindowDrawList( )->AddRectFilled( pos, pos + size, background );
			ImGui::PushStyleColor( ImGuiCol_Text, foreground.Value );
			ImGui::Text( buffer );
			ImGui::PopStyleColor( );
		}
	}

	template<typename... Args>
	void ImGUI::Text( const ImVec4& foreground, nString format, Args... args ) {
		ImGUI::Text( ImColor{ foreground }, format, args... );
	}

	template<typename... Args>
	void ImGUI::Text( const ImColor& foreground, nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) && !ImGUI::GetIsSkiped( ) ) {
			ImGui::PushStyleColor( ImGuiCol_Text, foreground.Value );
			ImGui::Text( format, args... );
			ImGui::PopStyleColor( );
		}
	}

	template<typename... Args>
	void ImGUI::Text( const ImVec4& foreground, const ImVec4& background, nString format, Args... args ) {
		ImGUI::Text( ImColor{ foreground }, ImColor{ background }, format, args... );
	}

	template<typename... Args>
	void ImGUI::Text( const ImColor& foreground, const ImColor& background, nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) && !ImGUI::GetIsSkiped( ) ) {
			const auto pos = ImGui::GetCursorScreenPos( );
			const auto size = ImGUI::GetTextSize( format, args... );

			ImGui::GetWindowDrawList( )->AddRectFilled( pos, pos + size, background );
			ImGui::PushStyleColor( ImGuiCol_Text, foreground.Value );
			ImGui::Text( format, args... );
			ImGui::PopStyleColor( );
		}
	}

	template<typename OnClick, typename... Args>
	void ImGUI::Button( nString label, const ImVec2& size, OnClick&& on_click, Args... args ) {
		if ( nHelper::GetIsValid( label ) && !ImGUI::GetIsSkiped( ) ) {
			if ( ImGui::Button( label, size ) )
				on_click( args... );
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC GET
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename... Args>
	const ImVec2 ImGUI::GetTextSize( nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) ) {
			char buffer[ 1024 ];
			sscanf_s( buffer, format, args... );

			return ImGui::CalcTextSize( buffer );
		}

		return ImVec2{ };
	}

#endif
