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

#include "__ui.hpp"

#include <LetheNut/UI/NutStyle.hpp>
#include <Thirdparty/GLFW/glfw3.h>
#include <Thirdparty/ImGUI/imgui.h>
#include <Thirdparty/ImGUI/imgui_impl_glfw.h>
#include <Thirdparty/ImGUI/imgui_impl_opengl3.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
void internal_Image( const nULong texture, const ImVec2& position, const ImVec2& size ) {
	const auto region = ImGui::GetContentRegionAvail( );

	if ( position.x < region.x && position.y < region.y ) {
		const auto cursor = ImGui::GetCursorPos( );

		ImGui::SetCursorPos( position );

		if ( size.x > 0.f && size.y > 0.f )
			ImGui::Image( reinterpret_cast<ImTextureID>( texture ), size );
		else if ( size.x <= 0.f && size.y > 0.f )
			ImGui::Image( reinterpret_cast<ImTextureID>( texture ), ImVec2{ region.x, size.y } );
		else if ( size.x > 0.f && size.y <= 0.f )
			ImGui::Image( reinterpret_cast<ImTextureID>( texture ), ImVec2{ size.x, region.y } );
		else if ( size.x <= 0.f && size.y <= 0.f )
			ImGui::Image( reinterpret_cast<ImTextureID>( texture ), region );

		ImGui::SetCursorPos( cursor );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
void ImGUI::Initialize( nPointer& window ) {
	auto* handle = (struct GLFWwindow*)window;

	glfwMakeContextCurrent( handle );

	ImGui::CreateContext( );

	auto& io = ImGui::GetIO( );
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	io.Fonts->AddFontFromFileTTF( "Assets/Fonts/OpenSans-Regular.ttf", 18.f );
	io.Fonts->AddFontFromFileTTF( "Assets/Fonts/OpenSans-Bold.ttf", 18.f );

	if ( io.Fonts->Fonts.Size > 0 )
		io.FontDefault = io.Fonts->Fonts[ ImGUI::FONT_DEFAULT ];

	ImGui::StyleColorsDark( );

	auto& style = ImGui::GetStyle( );
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
		style.WindowPadding = ImVec2( 10.f, 10.f );
		style.WindowRounding = .0f;
		style.ChildRounding = .0f;
		style.FramePadding = ImVec2( 5.f, 4.f );
		style.FrameRounding = 5.f;
		style.ItemSpacing = ImVec2( 5.f, 5.f );
		style.ItemInnerSpacing = ImVec2( 10.f, 10.f );
		style.IndentSpacing = 15.f;
		style.ScrollbarSize = 16.f;
		style.ScrollbarRounding = 2.f;
		style.GrabMinSize = 7.f;
		style.GrabRounding = 2.f;

		style.Colors[ ImGuiCol_WindowBg ].w = 1.f;
	}

	ImGui_ImplGlfw_InitForOpenGL( handle, true );
	ImGui_ImplOpenGL3_Init( "#version 450" );
}

void ImGUI::LoadFont( nString path, float size ) {
	ImGui::GetIO( ).Fonts->AddFontFromFileTTF( path, size );
}

void ImGUI::SetFont( nInt font_id ) {
	auto& io = ImGui::GetIO( );

	if ( font_id < io.Fonts->Fonts.Size )
		io.FontDefault = io.Fonts->Fonts[ ImGUI::FONT_DEFAULT ];
}

void ImGUI::ApplyStyle( NutStyle& style ) {
	auto& imgui_style = ImGui::GetStyle( );

	for ( auto& color : style.GetColors( ) )
		imgui_style.Colors[ color.target ] = color.value;

	for ( auto& rule : style.GetRules( ) ) {
		switch ( rule.target ) {
			case ImGuiStyleVar_Alpha				: imgui_style.Alpha					= rule.value.x; break;
			case ImGuiStyleVar_WindowPadding		: imgui_style.WindowPadding			= rule.value; break;
			case ImGuiStyleVar_WindowRounding		: imgui_style.WindowRounding		= rule.value.x;  break;
			case ImGuiStyleVar_WindowBorderSize		: imgui_style.WindowBorderSize		= rule.value.x; break;
			case ImGuiStyleVar_WindowMinSize		: imgui_style.WindowMinSize			= rule.value; break;
			case ImGuiStyleVar_WindowTitleAlign		: imgui_style.WindowTitleAlign		= rule.value; break;
			case ImGuiStyleVar_ChildRounding		: imgui_style.ChildRounding			= rule.value.x; break;
			case ImGuiStyleVar_ChildBorderSize		: imgui_style.ChildBorderSize		= rule.value.x; break;
			case ImGuiStyleVar_PopupRounding		: imgui_style.PopupRounding			= rule.value.x; break;
			case ImGuiStyleVar_PopupBorderSize		: imgui_style.PopupBorderSize		= rule.value.x; break;
			case ImGuiStyleVar_FramePadding			: imgui_style.FramePadding			= rule.value; break;
			case ImGuiStyleVar_FrameRounding		: imgui_style.FrameRounding			= rule.value.x; break;
			case ImGuiStyleVar_FrameBorderSize		: imgui_style.FrameBorderSize		= rule.value.x; break;
			case ImGuiStyleVar_ItemSpacing			: imgui_style.ItemSpacing			= rule.value; break;
			case ImGuiStyleVar_ItemInnerSpacing		: imgui_style.ItemInnerSpacing		= rule.value; break;
			case ImGuiStyleVar_IndentSpacing		: imgui_style.IndentSpacing			= rule.value.x; break;
			case ImGuiStyleVar_ScrollbarSize		: imgui_style.ScrollbarSize			= rule.value.x; break;
			case ImGuiStyleVar_ScrollbarRounding	: imgui_style.ScrollbarRounding		= rule.value.x; break;
			case ImGuiStyleVar_GrabMinSize			: imgui_style.GrabMinSize			= rule.value.x; break;
			case ImGuiStyleVar_GrabRounding			: imgui_style.GrabRounding			= rule.value.x; break;
			case ImGuiStyleVar_TabRounding			: imgui_style.TabRounding			= rule.value.x; break;
			case ImGuiStyleVar_ButtonTextAlign		: imgui_style.ButtonTextAlign		= rule.value; break;
			case ImGuiStyleVar_SelectableTextAlign	: imgui_style.SelectableTextAlign	= rule.value; break;

			default : break;
		}
	}
}

void ImGUI::Internal_StyleHeader( nString label, int components ) {
	ImGui::PushID( label );
	ImGui::Columns( 2 );
	ImGui::SetColumnWidth( 0, 100.f );
	ImGui::Text( label );
	ImGui::NextColumn( );
	ImGui::PushMultiItemsWidths( components, ImGui::CalcItemWidth( ) );
	ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 } );
}

void ImGUI::Internal_StyleFooter( ) {
	ImGui::PopStyleVar( );
	ImGui::PopItemWidth( );
	ImGui::Columns( 1 );
	ImGui::PopID( );
	ImGUI::Spacer( ImVec2{ .0f, .75f } );
}

const float ImGUI::GetLineHeight( ) {
	return GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
}

void ImGUI::Begin( ) {
	ImGui_ImplOpenGL3_NewFrame( );
	ImGui_ImplGlfw_NewFrame( );

	ImGui::NewFrame( );
}

void ImGUI::BeginPopup( nString label, ImGuiWindowFlags flags, ImVec2& size, float border_size, bool* is_open ) {
	auto* viewport = ImGui::GetMainViewport( );

	if ( size.x == 0.f || size.y == 0.f ) {
		ImGui::SetNextWindowPos( viewport->Pos );
		ImGui::SetNextWindowSize( viewport->Size );
	} else {
		ImVec2 pos = viewport->Pos;

		pos.x += ( viewport->Size.x - size.x ) * 0.5f;
		pos.y += ( viewport->Size.y - size.y ) * 0.5f;

		ImGui::SetNextWindowPos( pos );
		ImGui::SetNextWindowSize( size );
	}

	ImGui::SetNextWindowViewport( viewport->ID );
	ImGui::SetNextWindowBgAlpha( 1.f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, border_size );

	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
	ImGui::Begin( label, is_open, flags );
	ImGui::PopStyleVar( );
	ImGui::PopStyleVar( 1 );
}

void ImGUI::BeginDockspace( ) {
	auto& io = ImGui::GetIO( );

	if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable ) {
		auto dockspace_id = ImGui::GetID( "Dockspace" );

		ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), ImGuiDockNodeFlags_None );
	}
}

void ImGUI::BeginPanel( nString label, const ImVec2& padding ) {
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, padding );
	ImGui::Begin( label );
}

void ImGUI::BeginPanel( nString label, const ImVec2&& padding ) {
	ImGUI::BeginPanel( label, padding );
}

void ImGUI::Spacer( const ImVec2& spacing ) { ImGui::Dummy( spacing ); }

void ImGUI::Spacer( const ImVec2&& spacing ) { ImGUI::Spacer( spacing); }

void ImGUI::Spacer( const float x, const float y ) { 
	ImGUI::Spacer( ImVec2{ x, y } );
}

void ImGUI::Spring( nInt value ) {

}

void ImGUI::Spring( ) { ImGUI::Spring( 0 ); }

void ImGUI::Image( const OpenGL::Texture& texture ) {
	ImGUI::Image( texture, ImVec2{ 0, 0 }, ImVec2{ 0, 0 } );
}

void ImGUI::Image( const OpenGL::Texture& texture, const ImVec2& position, const ImVec2& size ) {
	if ( OpenGL::IsValid( texture ) )
		internal_Image( texture.ID, position, size );
}

void ImGUI::Image( const OpenGL::Texture& texture, const ImVec2&& position, const ImVec2&& size ) {
	ImGUI::Image( texture, position, size ); 
}

void ImGUI::Image( const OpenGL::Frame& frame ) {
	ImGUI::Image( frame, ImVec2{ 0, 0 }, ImVec2{ 0, 0 } );
}

void ImGUI::Image( const OpenGL::Frame& frame, const ImVec2& position, const ImVec2& size ) {
	if ( OpenGL::IsValid( frame ) )
		internal_Image( frame.color, position, size );
}

void ImGUI::Image( const OpenGL::Frame& frame, const ImVec2&& position, const ImVec2&& size ) {
	ImGUI::Image( frame, position, size );
}

void ImGUI::EndPanel( ) {
	ImGui::End( );
	ImGui::PopStyleVar( );
}

void ImGUI::EndPopup( ) { ImGui::End( ); }

void ImGUI::End( ) {
	ImGui::Render( );

	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData( ) );
}

void ImGUI::Destroy( ) {
	ImGui_ImplOpenGL3_Shutdown( );
	ImGui_ImplGlfw_Shutdown( );

	ImGui::DestroyContext( );
}
