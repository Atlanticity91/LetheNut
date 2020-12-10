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
#include <Thirdparty/ImGUI/imgui_internal.h>
#include <Thirdparty/ImGUI/imgui_impl_glfw.h>
#include <Thirdparty/ImGUI/imgui_impl_opengl3.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
void internal_Image( const nULong texture, const ImVec2& position, const ImVec2& size ) {
	const auto region = ImGui::GetContentRegionAvail( );

	if ( position.x < region.x && position.y < region.y) {
		auto* renderer = ImGui::GetWindowDrawList( );
		const auto cursor = ImGui::GetCursorPos( );

		ImGui::SetCursorScreenPos( position );

		if ( size.x > 0.f && size.y > 0.f )
			renderer->AddImage( reinterpret_cast<ImTextureID>( texture ), position, size );
		else if ( size.x <= 0.f && size.y > 0.f )
			renderer->AddImage( reinterpret_cast<ImTextureID>( texture ), position, ImVec2{ region.x, size.y } );
		else if ( size.x > 0.f && size.y <= 0.f )
			renderer->AddImage( reinterpret_cast<ImTextureID>( texture ), position, ImVec2{ size.x, region.y } );
		else if ( size.x <= 0.f && size.y <= 0.f )
			renderer->AddImage( reinterpret_cast<ImTextureID>( texture ), position, region );

		ImGui::SetCursorScreenPos( cursor );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
ImGUI::ImCanvas::ImCanvas( float zoom_min, float zoom_max )
	: zoom( 1.f ),
	offset( ),
	curve_thickness( 5.f ),
	connection_indent( 1.f ),
	zoom_min( zoom_min ),
	zoom_max( zoom_max )
{ }

void ImGUI::Initialize( nPointer& window ) {
	auto* handle = (struct GLFWwindow*)window;

	glfwMakeContextCurrent( handle );

	ImGui::CreateContext( );

	auto& io = ImGui::GetIO( );
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	//io.Fonts->AddFontFromFileTTF( "Assets/Fonts/OpenSans-Regular.ttf", 18.f );
	//io.Fonts->AddFontFromFileTTF( "Assets/Fonts/OpenSans-Bold.ttf", 18.f );

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

void ImGUI::LoadFont( nString path, float size ) { ImGui::GetIO( ).Fonts->AddFontFromFileTTF( path, size ); }

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

const float ImGUI::GetLineHeight( ) {
	return GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
}

const ImVec2 ImGUI::GetTextSize( nString text ) {
	return ImGui::GetFont( )->CalcTextSizeA( ImGui::GetFontSize( ), FLT_MAX, -1.0f, text, nullptr, nullptr );
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

void ImGUI::BeginCanvas( ImCanvas& canvas ) {
	const auto* window = ImGui::GetCurrentWindow( );
	const auto pos = ImGui::GetWindowPos( );
	const auto size = ImGui::GetWindowSize( );
	const auto grid = 48.f * canvas.zoom;

	auto& style = ImGui::GetStyle( );
	auto* renderer = ImGui::GetWindowDrawList( );

	ImGui::PushID( &canvas );
	ImGui::ItemAdd( window->ContentRegionRect, ImGui::GetID( "canvas" ) );
	ImGui::SetWindowFontScale( canvas.zoom );

	ImU32 grid_color = ImColor( style.Colors[ ImGuiCol_Separator ] );
	for ( float x = fmodf( canvas.offset.x, grid ); x < size.x;) {
		renderer->AddLine( ImVec2( x, 0 ) + pos, ImVec2( x, size.y ) + pos, grid_color );
		x += grid;
	}

	for ( float y = fmodf( canvas.offset.y, grid ); y < size.y;) {
		renderer->AddLine( ImVec2( 0, y ) + pos, ImVec2( size.x, y ) + pos, grid_color );
		y += grid;
	}
}

void ImGUI::BeginNode( const ImCanvas& canvas, nString title, const ImVec2& position ) {
	auto* renderer = ImGui::GetWindowDrawList( );
	auto pos = ImGui::GetWindowPos( ) + position * canvas.zoom + canvas.offset;

	renderer->ChannelsSplit( 2 );

	ImGui::SetCursorScreenPos( pos );
	ImGui::PushID( title );
	ImGui::BeginGroup( );

	renderer->ChannelsSetCurrent( 1 );

	ImGui::TextUnformatted( title );
}

void ImGUI::Spacer( const ImVec2& spacing ) { ImGui::Dummy( spacing ); }

void ImGUI::Spacer( const ImVec2&& spacing ) { ImGUI::Spacer( spacing ); }

void ImGUI::Spacer( const float x, const float y ) {  ImGUI::Spacer( ImVec2{ x, y } ); }

void ImGUI::NodeLink( const ImCanvas& canvas, const ImVec2& source, const ImVec2& destination, const ImColor& color ) {
	auto* renderer = ImGui::GetWindowDrawList( );
	auto thickness = canvas.curve_thickness * canvas.zoom;
	auto p2 = source - ImVec2{ 100 * canvas.zoom, 0 };
	auto p3 = destination + ImVec2{ 100 * canvas.zoom, 0 };

	renderer->AddBezierCurve( source, p2, p3, destination, color, thickness );
}

void ImGUI::NodeLink( const ImCanvas& canvas, const ImVec2&& source, const ImVec2&& destination, const ImColor&& color ) {
	ImGUI::NodeLink( canvas, source, destination, color );
}

void ImGUI::NodeCirclePin( const bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( );
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + ImGUI::NODE_PIN_SIZE } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * 0.5f, ( rect.Min.y + rect.Max.y ) * 0.5f );
	const auto outline_scale = rect_w / 24.0f;
	const auto extra_segments = static_cast<int>( 2 * outline_scale );

	if ( !is_connected ) {
		const auto r = 0.5f * rect_w / 2.0f - 0.5f;

		if ( ImGUI::NODE_PIN_INNER &0xFF000000 )
			renderer->AddCircleFilled( rect_center, r, ImGUI::NODE_PIN_INNER, 12 + extra_segments );

		renderer->AddCircle( rect_center, r, color, 12 + extra_segments, 2.0f * outline_scale );
	} else
		renderer->AddCircleFilled( rect_center, 0.5f * rect_w / 2.0f, color, 12 + extra_segments );
}

void ImGUI::NodeCirclePin( const bool is_connected, const ImColor&& color ) { 
	ImGUI::NodeCirclePin( is_connected, color );
}

void ImGUI::NodeSquarePin( const bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( );
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + ImGUI::NODE_PIN_SIZE } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * 0.5f, ( rect.Min.y + rect.Max.y ) * 0.5f );
	const auto outline_scale = rect_w / 24.0f;
	const auto extra_segments = static_cast<int>( 2 * outline_scale );

	if ( is_connected ) {
		const auto r = 0.5f * rect_w / 2.0f;
		const auto p0 = rect_center - ImVec2( r, r );
		const auto p1 = rect_center + ImVec2( r, r );

		renderer->AddRectFilled( p0, p1, color, 0, 15 + extra_segments );
	} else {
		const auto r = 0.5f * rect_w / 2.0f - 0.5f;
		const auto p0 = rect_center - ImVec2( r, r );
		const auto p1 = rect_center + ImVec2( r, r );

		if ( ImGUI::NODE_PIN_INNER & 0xFF000000 )
			renderer->AddRectFilled( p0, p1, ImGUI::NODE_PIN_INNER, 0, 15 + extra_segments );

		renderer->AddRect( p0, p1, color, 0, 15 + extra_segments, 2.0f * outline_scale );
	}
}

void ImGUI::NodeSquarePin( const bool is_connected, const ImColor&& color ) {
	ImGUI::NodeSquarePin( is_connected, color );
}

void ImGUI::NodeDiamondPin( const bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( );
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + ImGUI::NODE_PIN_SIZE } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * 0.5f, ( rect.Min.y + rect.Max.y ) * 0.5f );
	const auto outline_scale = rect_w / 24.0f;

	if ( is_connected ) {
		const auto r = 0.607f * rect_w / 2.0f;
		const auto c = rect_center;

		renderer->PathLineTo( c + ImVec2(  0, -r ) );
		renderer->PathLineTo( c + ImVec2(  r,  0 ) );
		renderer->PathLineTo( c + ImVec2(  0,  r ) );
		renderer->PathLineTo( c + ImVec2( -r,  0 ) );
		renderer->PathFillConvex( color );
	} else {
		const auto r = 0.607f * rect_w / 2.0f - 0.5f;
		const auto c = rect_center;

		renderer->PathLineTo( c + ImVec2( 0, -r ) );
		renderer->PathLineTo( c + ImVec2( r, 0 ) );
		renderer->PathLineTo( c + ImVec2( 0, r ) );
		renderer->PathLineTo( c + ImVec2( -r, 0 ) );

		if ( ImGUI::NODE_PIN_INNER & 0xFF000000 )
			renderer->AddConvexPolyFilled( renderer->_Path.Data, renderer->_Path.Size, ImGUI::NODE_PIN_INNER );

		renderer->PathStroke( color, true, 2.0f * outline_scale );
	}
}

void ImGUI::NodeDiamondPin( const bool is_connected, const ImColor&& color ) {
	ImGUI::NodeDiamondPin( is_connected, color );
}

void ImGUI::NodeArrayPin( const bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( );
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + ImGUI::NODE_PIN_SIZE, cursor.y + ImGUI::NODE_PIN_SIZE } );
	auto rect_w = rect.Max.x - rect.Min.x;
	auto rect_center_x = ( rect.Min.x + rect.Max.x ) * 0.5f;
	auto rect_center_y = ( rect.Min.y + rect.Max.y ) * 0.5f;
	auto triangleStart = rect_center_x + 0.32f * rect_w;

	const auto r = 0.5f * rect_w / 2.0f;
	const auto w = ceilf( r / 3.0f );

	const auto baseTl = ImVec2( floorf( rect_center_x - w * 2.5f ), floorf( rect_center_y - w * 2.5f ) );
	const auto baseBr = ImVec2( floorf( baseTl.x + w ), floorf( baseTl.y + w ) );

	auto tl = baseTl;
	auto br = baseBr;

	for ( int i = 0; i < 3; ++i ) {
		tl.x = baseTl.x;
		br.x = baseBr.x;
		renderer->AddRectFilled( tl, br, color );

		tl.x += w * 2;
		br.x += w * 2;

		if ( i != 1 || is_connected )
			renderer->AddRectFilled( tl, br, color );

		tl.x += w * 2;
		br.x += w * 2;

		renderer->AddRectFilled( tl, br, color );

		tl.y += w * 2;
		br.y += w * 2;
	}

	triangleStart = br.x + w + 1.0f / 24.0f * rect_w;
}

void ImGUI::NodeArrayPin( const bool is_connected, const ImColor&& color ) {
	ImGUI::NodeArrayPin( is_connected, color );
}

void ImGUI::Text( const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground ) {
	auto renderer = ImGui::GetWindowDrawList( );

	ImGUI::Text( renderer, position, text, background, foreground );
}

void ImGUI::Text( const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground ) {
	ImGUI::Text( position, text, background, foreground );
}

void ImGUI::Text( ImDrawList* renderer, const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground ) {
	if ( renderer ) {
		auto size = ImGUI::GetTextSize( text );
		auto end = ImVec2{ position.x + size.x, position.y + size.y };

		renderer->AddRectFilled( position, end, background );
		renderer->AddText( position, foreground, text );
	}
}

void ImGUI::Text( ImDrawList* renderer, const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground ) {
	ImGUI::Text( renderer, position, text, background, foreground );
}

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

void ImGUI::EndNode( const ImCanvas& canvas, nString title, const ImVec2& position, const ImColor& color ) {
	auto& style = ImGui::GetStyle( );
	auto* renderer = ImGui::GetWindowDrawList( );
	auto color_sep = ImColor( style.Colors[ ImGuiCol_Separator ] );
	auto color_bg = ImColor( style.Colors[ ImGuiCol_Border ] );
	auto pos = ImGui::GetWindowPos( ) + position * canvas.zoom + canvas.offset;

	ImGui::EndGroup( );

	auto node_rect = ImRect{
		ImGui::GetItemRectMin( ) - style.ItemInnerSpacing * canvas.zoom,
		( ImGui::GetItemRectMax( ) + ImVec2{ ImGUI::NODE_PIN_SIZE, 0.f } ) + style.ItemInnerSpacing * canvas.zoom
	};

	auto header_size = ImVec2{
		ImGui::GetItemRectSize( ).x + ( ImGUI::NODE_PIN_SIZE - ImGUI::NODE_ROUNDING ) + style.ItemInnerSpacing.x * canvas.zoom,
		ImGUI::GetTextSize( title ).y + 3.f
	};

	renderer->ChannelsSetCurrent( 0 );
	renderer->AddRectFilled( node_rect.Min, node_rect.Max, color, ImGUI::NODE_ROUNDING );
	renderer->AddRect( node_rect.Min, node_rect.Max, color_bg, ImGUI::NODE_ROUNDING );
	renderer->AddLine( pos + ImVec2{ 0, header_size.y }, pos + header_size, color_sep );
	renderer->ChannelsMerge( );

	ImGui::PopID( );
}

void ImGUI::EndNode( const ImCanvas& canvas, nString title, const ImVec2& position, const ImColor&& color ) {
	ImGUI::EndNode( canvas, title, position, color );
}

void ImGUI::EndCanvas( ) {
	ImGui::SetWindowFontScale( 1.f );
	ImGui::PopID( );
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
