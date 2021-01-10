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

#include "__pch.hpp"

#include <LetheNut/NutFramework.hpp>
#include <LetheNut/UI/NutPanel.hpp>
#include <LetheNut/UI/NutStyle.hpp>
#include <LetheNut/UI/NutWindow.hpp>
#include <LetheNut/Vendor/ImGUI.hpp>
#include <Thirdparty/GLFW/glfw3.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
void Internal_Image( nULong texture, const ImVec2& offset, const ImVec2& size ) {
	auto* window = ImGui::GetCurrentWindow( );
	const auto win_pos = window->Pos;
	const auto win_size = window->Size;
	const auto texture_id = reinterpret_cast<ImTextureID>( texture );

	window->DrawList->AddImage( reinterpret_cast<ImTextureID>( texture ), win_pos, win_pos + win_size );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
ImGUI::ImCanvas::ImCanvas( float zoom_max )
	: zoom_level( 1.f ),
	zoom_max( zoom_max ),
	offset( ),
	curve_thickness( 5.f ),
	connection_indent( 1.f ),
	Size_Grid( 48.f ),
	Size_Pin( 24.f ),
	Size_Selection{ .2f, .2f },
	Rounding( 4.f ),
	Tiling( 1.f / 128.f ),
	Color_Background( 04, 04, 204, 255 ),
	Color_Grid( 208, 208, 208, 204 ),
	Color_Inner( 32, 32, 32, 204 ),
	Color_Selection( 242, 178, 13, 255 ),
	Color_Header( 255, 255, 255, 28 ),
	Color_Comment( 208, 208, 208, 255 )
{ }

void ImGUI::Setup( GLFW::Window& window ) {
	ImGui::CreateContext( );
	ImGui::StyleColorsDark( );

	auto& io = ImGui::GetIO( );
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	auto& style = ImGui::GetStyle( );
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		style.Colors[ ImGuiCol_WindowBg ].w = 1.f;

	ImGui_ImplGlfw_InitForOpenGL( (GLFWwindow*)window.handle, true );
	ImGui_ImplOpenGL3_Init( "#version 450" );
}

void ImGUI::DockSpace( ) {
	auto& io = ImGui::GetIO( );

	if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable ) {
		auto dockspace_id = ImGui::GetID( "Dockspace" );

		ImGui::DockSpace( dockspace_id, ImVec2( 0.f, 0.f ), ImGuiDockNodeFlags_None );
	}
}

void ImGUI::LoadFont( nString path, float size ) {
	if ( nHelper::GetIsValid( path ) )
		ImGui::GetIO( ).Fonts->AddFontFromFileTTF( path, size );
}

void ImGUI::SetFont( nInt font_id ) {
	auto& io = ImGui::GetIO( );

	if ( font_id < io.Fonts->Fonts.Size )
		io.FontDefault = io.Fonts->Fonts[ 0 ];
}

void ImGUI::SetStyle( NutStyle* style ) {
	if ( style ) {
		auto& imgui_style = ImGui::GetStyle( );

		for ( auto& color : style->GetColors( ) )
			imgui_style.Colors[ color.target ] = color.value;

		for ( auto& rule : style->GetRules( ) ) {
			switch ( rule.target ) {
				case ImGuiStyleVar_Alpha: imgui_style.Alpha = rule.value.x; break;
				case ImGuiStyleVar_WindowPadding: imgui_style.WindowPadding = rule.value; break;
				case ImGuiStyleVar_WindowRounding: imgui_style.WindowRounding = rule.value.x;  break;
				case ImGuiStyleVar_WindowBorderSize: imgui_style.WindowBorderSize = rule.value.x; break;
				case ImGuiStyleVar_WindowMinSize: imgui_style.WindowMinSize = rule.value; break;
				case ImGuiStyleVar_WindowTitleAlign: imgui_style.WindowTitleAlign = rule.value; break;
				case ImGuiStyleVar_ChildRounding: imgui_style.ChildRounding = rule.value.x; break;
				case ImGuiStyleVar_ChildBorderSize: imgui_style.ChildBorderSize = rule.value.x; break;
				case ImGuiStyleVar_PopupRounding: imgui_style.PopupRounding = rule.value.x; break;
				case ImGuiStyleVar_PopupBorderSize: imgui_style.PopupBorderSize = rule.value.x; break;
				case ImGuiStyleVar_FramePadding: imgui_style.FramePadding = rule.value; break;
				case ImGuiStyleVar_FrameRounding: imgui_style.FrameRounding = rule.value.x; break;
				case ImGuiStyleVar_FrameBorderSize: imgui_style.FrameBorderSize = rule.value.x; break;
				case ImGuiStyleVar_ItemSpacing: imgui_style.ItemSpacing = rule.value; break;
				case ImGuiStyleVar_ItemInnerSpacing: imgui_style.ItemInnerSpacing = rule.value; break;
				case ImGuiStyleVar_IndentSpacing: imgui_style.IndentSpacing = rule.value.x; break;
				case ImGuiStyleVar_ScrollbarSize: imgui_style.ScrollbarSize = rule.value.x; break;
				case ImGuiStyleVar_ScrollbarRounding: imgui_style.ScrollbarRounding = rule.value.x; break;
				case ImGuiStyleVar_GrabMinSize: imgui_style.GrabMinSize = rule.value.x; break;
				case ImGuiStyleVar_GrabRounding: imgui_style.GrabRounding = rule.value.x; break;
				case ImGuiStyleVar_TabRounding: imgui_style.TabRounding = rule.value.x; break;
				case ImGuiStyleVar_ButtonTextAlign: imgui_style.ButtonTextAlign = rule.value; break;
				case ImGuiStyleVar_SelectableTextAlign: imgui_style.SelectableTextAlign = rule.value; break;

				default: break;
			}
		}

		for ( auto& font : style->GetFonts( ) )
			ImGUI::LoadFont( font.path, font.size );

		ImGUI::SetFont( 0 );
	}
}

void ImGUI::Start( ) {
	ImGui_ImplOpenGL3_NewFrame( );
	ImGui_ImplGlfw_NewFrame( );

	ImGui::NewFrame( );
}

bool ImGUI::Window( NutWindow* window ) {
	if ( window ) {
		auto* viewport = ImGui::GetMainViewport( );

		ImGui::SetNextWindowPos( viewport->Pos );
		ImGui::SetNextWindowSize( viewport->Size );
		ImGui::SetNextWindowBgAlpha( 1.f );

		ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.f );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{ } );

		auto flags =	ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus;

		if ( window->GetHasMenu( ) )
			flags |= ImGuiWindowFlags_MenuBar;

		auto state = ImGui::Begin( window->GetLabel( ), window->GetState( ), flags );
		
		ImGui::PopStyleVar( 2 );

		return state;
	}

	return false;
}

bool ImGUI::Panel( NutPanel* panel ) {
	if ( panel ) {
		ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, panel->GetPadding( ) );
		auto state = ImGui::Begin( panel->GetLabel( ), panel->GetState( ), panel->GetFlags( ) );
		ImGui::PopStyleVar( );

		return state;
	}

	return false;
}

bool ImGUI::Tab( NutTextDocument& document ) {
	return ImGui::BeginTabItem( document.GetName( ).c_str( ), document.GetState( ), ImGuiTabItemFlags_UnsavedDocument );
}

void ImGUI::EndTab( ) { ImGui::EndTabItem( ); }

bool ImGUI::Modal( nString label ) { return ImGUI::Modal( label, true ); }

bool ImGUI::Modal( nString label, bool is_visible ) {
	if ( nHelper::GetIsValid( label ) ) {
		if ( is_visible && !ImGui::IsPopupOpen( label ) )
			ImGui::OpenPopup( label );

		return ImGui::BeginPopupModal( label, nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize );
	}

	return false;
}

bool ImGUI::ModalButton( nString label ) {
	return ImGUI::ModalButton( label, true );
}

bool ImGUI::ModalButton( nString label, bool close_modal ) {
	if ( nHelper::GetIsValid( label ) ) {
		auto state = ImGui::Button( label, ImVec2( 80, 0 ) );

		if ( state ) {
			if ( close_modal )
				ImGUI::CloseModal( );
			else
				ImGui::EndPopup( );
		}

		return state;
	}

	return false;
}

void ImGUI::CloseModal( ) {
	ImGui::CloseCurrentPopup( );
	ImGui::EndPopup( );
}

void ImGUI::EndModal( ) { ImGui::EndPopup( ); }

bool ImGUI::Canvas( ImCanvas& canvas ) {
	const auto size = ImGui::GetWindowSize( );

	return ImGUI::Canvas( canvas, ImVec2{ 0.f, 0.f }, size );
}

bool ImGUI::Canvas( ImCanvas& canvas, const ImVec2& offset, const ImVec2& size ) {
	if ( !ImGUI::GetIsSkiped( ) ) {
		auto position = ImGui::GetWindowPos( ) + offset;
		const auto grid = canvas.Size_Grid * canvas.zoom_level;

		auto* renderer = ImGui::GetWindowDrawList( );
		auto region = ImRect( position, position + size );

		ImGui::PushID( &canvas );
		ImGui::SetWindowFontScale( canvas.zoom_level );

		bool state = ImGui::ItemAdd( region, ImGui::GetID( &canvas ) );

		if ( state ) {
			renderer->AddRectFilled( region.Min, region.Max, canvas.Color_Background );

			for ( float x = fmodf( canvas.offset.x, grid ); x < size.x; ) {
				renderer->AddLine( ImVec2( x, 0 ) + position, ImVec2( x, size.y ) + position, canvas.Color_Grid );
				x += grid;
			}

			for ( float y = fmodf( canvas.offset.y, grid ); y < size.y; ) {
				renderer->AddLine( ImVec2( 0, y ) + position, ImVec2( size.x, y ) + position, canvas.Color_Grid );
				y += grid;
			}
		}

		return state;
	}

	return false;
}

void ImGUI::Zoom( ImCanvas& canvas, float offset ) {
	canvas.zoom_level += offset;

	nHelper::Clamp( canvas.zoom_level, 1.f, canvas.zoom_max );
}

void ImGUI::SetZoom( ImCanvas& canvas, float zoom_level ) {
	canvas.zoom_level += zoom_level;

	nHelper::Clamp( canvas.zoom_level, 1.f, canvas.zoom_max );
}

void ImGUI::EndCanvas( ImCanvas& canvas ) {
	ImGui::SetWindowFontScale( 1.f );
	ImGui::PopID( );
}

bool ImGUI::Tooltip( ) {
	auto min = ImGui::GetWindowContentRegionMin( );
	auto max = ImGui::GetWindowContentRegionMax( );

	return ImGUI::Tooltip( min, max );
}

bool ImGUI::Tooltip( const ImRect& hover ) { return ImGUI::Tooltip( hover.Min, hover.Max ); }

bool ImGUI::Tooltip( const ImVec2& min, const ImVec2& max ) {
	if ( ImGui::IsWindowFocused( ) && ImGui::IsMouseHoveringRect( min, max ) ) {
		ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{ 8.f, 2.f } );
		ImGui::BeginTooltip( );

		return true;
	}

	return false;
}

void ImGUI::EndTooltip( ) {
	ImGui::EndTooltip( );
	ImGui::PopStyleVar( );
}

void ImGUI::Rect( const ImVec2& start, const ImVec2& end, const ImVec4& color ) {
	ImGUI::Rect( start, end, ImColor{ color } );
}

void ImGUI::Rect( const ImVec2& start, const ImVec2& end, const ImColor& color ) {
	ImGui::GetWindowDrawList( )->AddRect( start, end, color );
}

void ImGUI::RectFilled( const ImVec2& start, const ImVec2& end, const ImVec4& color ) {
	ImGUI::RectFilled( start, end, ImColor{ color } );
}

void ImGUI::RectFilled( const ImVec2& start, const ImVec2& end, const ImColor& color ) {
	ImGui::GetWindowDrawList( )->AddRectFilled( start, end, color );
}

void ImGUI::Image( const OpenGL::Texture& texture ) {
	ImGUI::Image( texture, ImVec2{ }, ImVec2{ (float)texture.Width, (float)texture.Height } );
}

void ImGUI::Image( const OpenGL::Texture& texture, const ImVec2& offset ) {
	ImGUI::Image( texture, offset, ImVec2{ (float)texture.Width, (float)texture.Height } );
}

void ImGUI::Image( const OpenGL::Texture& texture, const ImVec2& offset, const ImVec2& size ) {
	if ( OpenGL::IsValid( texture ) && !ImGUI::GetIsSkiped( ) )
		Internal_Image( texture.ID, offset, size );
}

void ImGUI::Image( const OpenGL::Frame& frame ) {
	ImGUI::Image( frame, ImVec2{ }, ImVec2{ (float)frame.Width, (float)frame.Height } );
}

void ImGUI::Image( const OpenGL::Frame& frame, const ImVec2& offset ) {
	ImGUI::Image( frame, offset, ImVec2{ (float)frame.Width, (float)frame.Height } );
}

void ImGUI::Image( const OpenGL::Frame& frame, const ImVec2& offset, const ImVec2& size ) {
	if ( OpenGL::IsValid( frame ) && !ImGUI::GetIsSkiped( ) )
		Internal_Image( frame.color, offset, size );
}

bool ImGUI::Category( nString label ) { return ImGUI::Category( label, "" ); }

bool ImGUI::Category( nString label, nString description ) {
	if ( nHelper::GetIsValid( label ) ) {
		ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2{ 0.f, 1.f } );

		auto state = ImGui::CollapsingHeader( label, ImGuiTreeNodeFlags_DefaultOpen );

		if ( state )
			ImGUI::Tooltip( description );

		return state;
	}

	return false;
}

void ImGUI::EndCategory( ) { ImGui::PopStyleVar( ); }

void ImGUI::ItemHeader( ) {
	ImGui::BeginGroup( );
}

void ImGUI::ItemFooter( ) {
	ImGui::EndGroup( );

	auto size = ImGui::GetWindowSize( );
	auto* renderer = ImGui::GetWindowDrawList( );
	renderer->AddRectFilled( ImGui::GetCursorPos( ), ImGui::GetCursorPos( ) + ImVec2{ size.x, 16.f }, ImColor{ 255, 0, 0, 255 } );
}

void ImGUI::Stop( ) {
	ImGui::Render( );
	OpenGL::Clear( );

	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData( ) );
}

void ImGUI::Cleanup( ) {
	ImGui_ImplOpenGL3_Shutdown( );
	ImGui_ImplGlfw_Shutdown( );

	ImGui::DestroyContext( );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
const bool ImGUI::GetIsSkiped( ) {
	auto* window = ImGui::GetCurrentWindow( );

	if ( window )
		return window->SkipItems;

	return false;
}

const bool ImGUI::GetIsKeyPressed( ImGuiKey_ query_key ) {
	return ImGui::IsKeyPressed( ImGui::GetKeyIndex( query_key ) );
}

const bool ImGUI::GetIsShiftDown( ) {
	auto& io = ImGui::GetIO( );

	return io.KeyShift;
}

const bool ImGUI::GetIsCtrltDown( ) {
	auto& io = ImGui::GetIO( );

	return io.ConfigMacOSXBehaviors ? io.KeySuper : io.KeyCtrl;
}

const bool ImGUI::GetIsAltDown( ) {
	auto& io = ImGui::GetIO( );

	return io.ConfigMacOSXBehaviors ? io.KeyCtrl : io.KeyAlt;
}

const ImVec2 ImGUI::GetMouseRelPos( ) {
	return ImVec2{ ImGui::GetMousePos( ).x - ImGui::GetWindowPos( ).x, ImGui::GetMousePos( ).y - ImGui::GetWindowPos( ).y };
}

const ImVec2 ImGUI::GetMouseDelta( ) {
	auto& io = ImGui::GetIO( );

	return io.MouseDelta;
}

const float ImGUI::GetScrollWheelH( ) {
	auto& io = ImGui::GetIO( );

	return io.MouseWheelH;
}

const float ImGUI::GetScrollWheel( ) {
	auto& io = ImGui::GetIO( );

	return io.MouseWheel;
}

const float ImGUI::GetPenPressure( ) {
	auto& io = ImGui::GetIO( );

	return io.PenPressure;
}

const float ImGUI::GetLineHeight( ) {
	return GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
}

const ImVec2 ImGUI::GetTextSize( const std::string_view& text ) {
	if ( !text.empty( ) ) {
		char buffer[ 1024 ];
		strncpy_s( buffer, text.data( ), text.size( ) );

		return ImGui::CalcTextSize( buffer );
	}

	return ImVec2{ };
}
