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

#ifndef _IGS_NUT_VENDOR_IMGUI_IMP_HPP_
#define _IGS_NUT_VENDOR_IMGUI_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      INTERNAL 
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Type >
	void Internal_Vect( const char axe, const ImVec4& normal, const ImVec4& hovered, Type& value, Type reset ) {
		char axe_str[ 2 ] = { axe, '\0' };
		auto lineHeight = ImGUI::GetLineHeight( );
		auto buttonSize = ImVec2{ lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor( ImGuiCol_Button, normal );
		ImGui::PushStyleColor( ImGuiCol_ButtonHovered, hovered );
		ImGui::PushStyleColor( ImGuiCol_ButtonActive, normal );

		if ( ImGui::Button( axe_str, buttonSize ) )
			value = reset;

		ImGui::PopStyleColor( 3 );

		ImGui::SameLine( );

		char drag_str[ 4 ] = { '#', '#', axe, '\0' };
		if constexpr ( std::is_floating_point<Type>::value )
			ImGui::DragFloat( drag_str, &value, 0.1f, 0.0f, 0.0f, "%.2f" );
		else
			ImGui::DragInt( drag_str, &value, 0.1f, 0.0f, 0.0f, "%.2f" );
	}

	template< typename Type >
	void Internal_Slide( char axe, const ImVec4& normal, const ImVec4& hovered, Type& value, Type min, Type max ) {
		char axe_str[ 2 ] = { axe, '\0' };

		nHelper::Clamp( value, min, max );

		auto lineHeight = ImGUI::GetLineHeight( );
		auto buttonSize = ImVec2{ lineHeight + 3.0f, lineHeight };

		ImGui::PushID( &value );
		ImGui::PushStyleColor( ImGuiCol_Button, normal );
		ImGui::PushStyleColor( ImGuiCol_ButtonHovered, hovered );
		ImGui::PushStyleColor( ImGuiCol_ButtonActive, normal );

		if ( ImGui::Button( axe_str, buttonSize ) )
			value = min;

		ImGui::SameLine( );

		if constexpr ( std::is_floating_point<Type>::value )
			ImGui::SliderFloat( ImGUI::NO_STRING, &value, min, max );
		 else
			ImGui::SliderInt( ImGUI::NO_STRING, &value, min, max );
		

		ImGui::SameLine( );
		
		axe_str[ 0 ] = toupper( axe );

		if ( ImGui::Button( axe_str, buttonSize ) )
			value = max;

		ImGui::PopStyleColor( 3 );
		ImGui::PopID( );
	}

	template< typename Type >
	inline void Internal_Slide( char axe, const ImVec4&& normal, const ImVec4&& hovered, Type& value, Type min, Type max ) {
		Internal_Slide<Type>( axe, normal, hovered, value, min, max );
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC
	///////////////////////////////////////////////////////////////////////////////////////////
	template< typename Callback, typename... Args >
	void ImGUI::DequeueCharacters( Callback&& callback, Args... args ) {
		auto& io = ImGui::GetIO( );

		if ( !io.InputQueueCharacters.empty( ) ) {
			for ( int i = 0; i < io.InputQueueCharacters.Size; i++ ) {
				auto c = io.InputQueueCharacters[ i ];

				if ( c != 0 && ( c == '\n' || c >= 32 ) && c < 0x80 )
					callback( (char)c, args... );
			}

			io.InputQueueCharacters.resize( 0 );
		}
	}


	template< typename Content, typename... Args >
	void ImGUI::CreateModal( nString label, ImVec2& size, float border_size, bool* is_open, Content&& content, Args... args ) {
		auto& io = ImGui::GetIO( );

		ImGui::SetNextWindowSizeConstraints( { 480, 260 }, { io.DisplaySize.x, io.DisplaySize.y } );
		ImGui::SetNextWindowPos( { io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f }, ImGuiCond_Appearing, ImVec2( 0.5f, 0.5f ) );
		ImGui::SetNextWindowSize( size, ImGuiCond_Appearing );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, border_size );

		if ( ImGui::BeginPopupModal( label, is_open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize ) ) {
			content( args... );

			ImGui::EndPopup( );
		}

		ImGui::PopStyleVar( );
	}

	template< typename Content, typename... Args >
	void ImGUI::CreateModal( nString name, ImVec2&& size, float border_size, bool* is_open, Content&& content, Args... args ) {
		ImGUI::CreateModal( name, size, border_size, is_open, content, args... );
	}

	template< typename Content >
	void ImGUI::MenurBar( nString label, Content&& content ) {
		if ( nHelper::GetIsValid( label ) && ImGui::BeginMenuBar( ) ) {
			ImGui::PushStyleColor( ImGuiCol_Header, ImVec4{ .76f, .31f, .0f, 1.f } );

			if ( ImGui::BeginMenu( label ) ) {
				content( );

				ImGui::EndMenu( );
			}

			ImGui::PopStyleColor( );
			ImGui::EndMenuBar( );
		}
	}

	template< typename Callback >
	void ImGUI::MenuButton( nString label, nString shortcut, bool is_active, Callback&& callback ) {
		if ( nHelper::GetIsValid( label ) && ImGui::MenuItem( label, shortcut, nullptr, is_active ) )
			callback( );
	}

	template< typename... Args >
	void ImGUI::Text( const ImColor& color, nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) ) {
			ImGui::PushStyleColor( ImGuiCol_Text, color.Value );
			ImGui::Text( format, args... );
			ImGui::PopStyleColor( );
		}
	}

	template< typename... Args >
	void ImGUI::Text( const ImColor&& color, nString format, Args... args ) {
		ImGUI::Text( color, format, args... );
	}

	template< typename... Args >
	void ImGUI::ToolTip( nString format, Args... args ) {
		ImGUI::ToolTip( ImGUI::DEFAULT_COLOR, format, args... );
	}

	template< typename... Args >
	void ImGUI::ToolTip( const ImColor& color, nString format, Args... args ) {
		if ( nHelper::GetIsValid( format ) && ImGui::IsMousePosValid( ) && ImGui::IsItemHovered( ) ) {
			ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{ 8.f, 2.f } );
			ImGui::BeginTooltip( );
				ImGUI::Text( color, format, args... );
			ImGui::EndTooltip( );
			ImGui::PopStyleVar( );
		}
	}

	template< typename... Args >
	void ImGUI::ToolTip( const ImColor&& color, nString format, Args... args ) { 
		ImGUI::ToolTip( color, format, args... );
	}

	template< typename Content, typename... Args >
	void ImGUI::ToolTip( Content&& content, Args... args ) {
		if ( ImGui::IsMousePosValid( ) && ImGui::IsItemHovered( ) ) {
			auto mouse_pos = ImGUI::GetMouseRelPos( );

			ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{ 8.f, 2.f } );
			ImGui::BeginTooltip( );

				content( mouse_pos, args... );

			ImGui::EndTooltip( );
			ImGui::PopStyleVar( );
		}
	}

	template< typename Callback >
	void ImGUI::Button( nString label, const ImVec2& size, Callback&& callback ) {
		if ( nHelper::GetIsValid( label ) && ImGui::Button( label, size ) )
			callback( );
	}

	template< typename Callback >
	void ImGUI::Button( nString label, const ImVec2&& size, Callback&& callback ) {
		ImGUI::Button( label, size, callback );
	}

	template< typename Mark >
	void ImGUI::Checkbox( nString label, bool& state, Mark&& mark ) {
		ImGUI::Checkbox( label, nullptr, state, mark );
	}

	template< typename Mark >
	void ImGUI::Checkbox( nString label, nString description, bool& state, Mark&& mark ) {
		if ( nHelper::GetIsValid( label ) ) {
			bool old = state;

			ImGUI::Internal_StyleHeader( label, 1 );

			if ( description && strlen( description ) > 0 )
				ImGUI::ToolTip( [ & ]( const ImVec2& mouse_pos ) { ImGui::Text( description ); } );

			ImGui::Checkbox( "", &state );

			if ( old != state && state )
				mark( );

			ImGUI::Internal_StyleFooter( );
		}
	}

	template< typename Mark, typename UnMark >
	void ImGUI::Checkbox( nString label, bool& state, Mark&& mark, UnMark&& unmark ) {
		ImGUI::Checkbox( label, nullptr, state, mark, unmark );
	}

	template< typename Mark, typename UnMark >
	void ImGUI::Checkbox( nString label, nString description, bool& state, Mark&& mark, UnMark&& unmark ) {
		if ( nHelper::GetIsValid( label ) ) {
			bool old = state;

			ImGUI::Internal_StyleHeader( label, 1 );

			if ( description && strlen( description ) > 0 )
				ImGUI::ToolTip( [ & ]( const ImVec2& mouse_pos ) { ImGui::Text( description ); } );

			ImGui::Checkbox( "", &state );

			if ( old != state ) {
				if ( state )
					mark( );
				else
					unmark( );
			}

			ImGUI::Internal_StyleFooter( );
		}
	}

	template< size_t Length, typename Type >
	void ImGUI::Vector( nString label, Type* data, Type reset ) {
		ImGUI::Vector< Length >( label, nullptr, data, reset );
	}

	template< size_t Length, typename Type >
	void ImGUI::Vector( nString label, nString description, Type* data, Type reset ) {
		if constexpr ( std::is_arithmetic<Type>::value && Length > 0 ) {
			if ( nHelper::GetIsValid( label ) && data ) {
				ImGUI::Internal_StyleHeader( label, 4 );

				if ( description && strlen( description ) > 0 )
					ImGUI::ToolTip( [ & ]( const ImVec2& pos ) { ImGUI::Text( ImGUI::DEFAULT_COLOR, description ); } );

				Internal_Vect(
					'X', ImGUI::AxeX_Normal, ImGUI::AxeX_Hovered,
					data[ 0 ], reset
				);

				if constexpr ( Length > 1 ) {
					ImGui::SameLine( );

					Internal_Vect(
						'Y', ImGUI::AxeY_Normal, ImGUI::AxeY_Hovered,
						data[ 1 ], reset
					);

					if constexpr ( Length > 2 ) {
						ImGui::SameLine( );

						Internal_Vect(
							'Z', ImGUI::AxeZ_Normal, ImGUI::AxeZ_Hovered,
							data[ 2 ], reset
						);

						if constexpr ( Length > 3 ) {
							ImGui::SameLine( );

							Internal_Vect(
								'W', ImGUI::AxeW_Normal, ImGUI::AxeW_Hovered,
								data[ 3 ], reset
							);
						}
					}
				}

				ImGUI::Internal_StyleFooter( );
			}
		} else
			ImGUI::Text( label, ImGUI::DEFAULT_COLOR );
	}

	template< size_t Length, typename Type >
	void ImGUI::Slider( nString label, Type* data, Type min, Type max ) {
		if constexpr ( std::is_arithmetic<Type>::value && Length > 0 ) {
			if ( nHelper::GetIsValid( label ) && data ) {
				ImGUI::Internal_StyleHeader( label, 1 );

				Internal_Slide( 
					'x', ImGUI::AxeX_Normal, ImGUI::AxeX_Hovered,
					data[ 0 ], min, max 
				);

				if constexpr ( Length > 1 ) {
					ImGUI::Spacer( ImVec2{ .0f, 2.f } );

					Internal_Slide( 
						'y', ImGUI::AxeY_Normal, ImGUI::AxeY_Hovered,
						data[ 1 ], min, max 
					);

					if constexpr ( Length > 2 ) {
						ImGUI::Spacer( ImVec2{ .0f, 2.f } );

						Internal_Slide(
							'z', ImGUI::AxeZ_Normal, ImGUI::AxeZ_Hovered,
							data[ 2 ], min, max 
						);

						if constexpr ( Length > 3 ) {
							ImGUI::Spacer( ImVec2{ .0f, 2.f } );

							Internal_Slide( 
								'w', ImGUI::AxeW_Normal, ImGUI::AxeW_Hovered,
								data[ 3 ], min, max 
							);
						}
					}
				}

				ImGUI::Internal_StyleFooter( );
			}
		} else
			ImGUI::Text( label, ImGUI::DEFAULT_COLOR );
	}

	template< size_t Length, typename Type, typename OnChange >
	void ImGUI::DropList( nString label, nString& previous, nString* list, Type& data, OnChange&& on_change ) {
		if ( nHelper::GetIsValid( label ) ) {
			ImGUI::Internal_StyleHeader( label, 1 );

			if ( ImGui::BeginCombo( ImGUI::NO_STRING, previous ) ) {
				for ( auto idx = 0; idx < Length; idx++ ) {
					auto isSelected = previous == list[ idx ];

					ImGui::PushStyleColor( ImGuiCol_Header, ImVec4{ .76f, .31f, .0f, 1.f } );
					if ( ImGui::Selectable( list[ idx ], isSelected ) ) {
						previous = list[ idx ];

						on_change( previous, idx, data );
					}
					ImGui::PopStyleColor( );

					if ( isSelected )
						ImGui::SetItemDefaultFocus( );
				}

				ImGui::EndCombo( );
			}

			ImGUI::Internal_StyleFooter( );
		}
	}

	template< typename Content, typename... Args >
	void ImGUI::Tree( nString label, Content&& content, Args... args ) {
		ImGUI::Tree( label, nullptr, ImGUI::TREE_FLAGS, content, args... );
	}

	template< typename Content, typename... Args >
	void ImGUI::Tree( nString label, ImGuiTreeNodeFlags flags, Content&& content, Args... args ) {
		ImGUI::Tree( label, nullptr, ImGUI::TREE_FLAGS, content, args... );
	}

	template< typename Content, typename... Args >
	void ImGUI::Tree( nString label, nString description, Content&& content, Args... args ) {
		ImGUI::Tree( label, description, ImGUI::TREE_FLAGS, content, args... );
	}

	template< typename Content, typename... Args >
	void ImGUI::Tree( nString label, nString description, ImGuiTreeNodeFlags flags, Content&& content, Args... args ) {
		if ( nHelper::GetIsValid( label ) ) {
			ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 } );
			ImGui::Separator( );

			auto open = ImGui::TreeNodeEx( label, flags, label );

			ImGui::PopStyleVar( );

			if ( open ) {
				ImGUI::ToolTip( description );

					content( args... );

				ImGui::TreePop( );
			}
		}
	}

	template< typename Content >
	void ImGUI::RightClickPanel( bool over_items, Content&& content ) {
		if ( ImGui::BeginPopupContextWindow( 0, 1 | ( over_items ? 0 : ImGuiPopupFlags_NoOpenOverItems ) ) ) {
			content( );

			ImGui::EndPopup( );
		}
	}

#endif
