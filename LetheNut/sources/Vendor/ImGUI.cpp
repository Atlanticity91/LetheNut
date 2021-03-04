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
#include <Thirdparty/ImGui/imgui_impl_opengl3.h>
#include <Thirdparty/ImGui/imgui_impl_glfw.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
void Internal_NodeCirclePin( const ImGUI::ImNodeStyle& style, bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( ) - style.Var_PinOffset;
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + style.Var_PinSize, cursor.y + style.Var_PinSize } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * .5f, ( rect.Min.y + rect.Max.y ) * .5f );
	const auto outline_scale = rect_w / 24.f;
	const auto extra_segments = static_cast<int>( 2 * outline_scale );

	if ( !is_connected ) {
		const auto r = .5f * rect_w / 2.f - .5f;

		if ( style.Color_Inner & 0xFF000000 )
			renderer->AddCircleFilled( rect_center, r, style.Color_Inner, 12 + extra_segments );

		renderer->AddCircle( rect_center, r, color, 12 + extra_segments, 2.f * outline_scale );
	} else
		renderer->AddCircleFilled( rect_center, .5f * rect_w / 2.f, color, 12 + extra_segments );
}

void Internal_NodeSquarePin( const ImGUI::ImNodeStyle& style, bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( ) - style.Var_PinOffset;
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + style.Var_PinSize, cursor.y + style.Var_PinSize } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * .5f, ( rect.Min.y + rect.Max.y ) * .5f );
	const auto outline_scale = rect_w / 24.f;
	const auto extra_segments = static_cast<int>( 2 * outline_scale );

	if ( is_connected ) {
		const auto r = .5f * rect_w / 2.f;
		const auto p0 = rect_center - ImVec2( r, r );
		const auto p1 = rect_center + ImVec2( r, r );

		renderer->AddRectFilled( p0, p1, color, 0, 15 + extra_segments );
	} else {
		const auto r = .5f * rect_w / 2.f - .5f;
		const auto p0 = rect_center - ImVec2( r, r );
		const auto p1 = rect_center + ImVec2( r, r );

		if ( style.Color_Inner & 0xFF000000 )
			renderer->AddRectFilled( p0, p1, style.Color_Inner, 0, 15 + extra_segments );

		renderer->AddRect( p0, p1, color, 0, 15 + extra_segments, 2.f * outline_scale );
	}
}

void Internal_NodeDiamondPin( const ImGUI::ImNodeStyle& style, bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( ) - style.Var_PinOffset;
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + style.Var_PinSize, cursor.y + style.Var_PinSize } );
	auto rect_w = rect.Max.x - rect.Min.x;
	const auto rect_center = ImVec2( ( rect.Min.x + rect.Max.x ) * .5f, ( rect.Min.y + rect.Max.y ) * .5f );
	const auto outline_scale = rect_w / 24.f;

	if ( is_connected ) {
		const auto r = 0.607f * rect_w / 2.f;
		const auto c = rect_center;

		renderer->PathLineTo( c + ImVec2( 0, -r ) );
		renderer->PathLineTo( c + ImVec2( r, 0 ) );
		renderer->PathLineTo( c + ImVec2( 0, r ) );
		renderer->PathLineTo( c + ImVec2( -r, 0 ) );
		renderer->PathFillConvex( color );
	} else {
		const auto r = 0.607f * rect_w / 2.f - .5f;
		const auto c = rect_center;

		renderer->PathLineTo( c + ImVec2( 0, -r ) );
		renderer->PathLineTo( c + ImVec2( r, 0 ) );
		renderer->PathLineTo( c + ImVec2( 0, r ) );
		renderer->PathLineTo( c + ImVec2( -r, 0 ) );

		if ( style.Color_Inner & 0xFF000000 )
			renderer->AddConvexPolyFilled( renderer->_Path.Data, renderer->_Path.Size, style.Color_Inner );

		renderer->PathStroke( color, true, 2.f * outline_scale );
	}
}

void Internal_NodeArrayPin( const ImGUI::ImNodeStyle& style, bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( ) - style.Var_PinOffset;
	auto renderer = ImGui::GetWindowDrawList( );

	auto rect = ImRect( cursor, ImVec2{ cursor.x + style.Var_PinSize, cursor.y + style.Var_PinSize } );
	auto rect_w = rect.Max.x - rect.Min.x;
	auto rect_center_x = ( rect.Min.x + rect.Max.x ) * .5f;
	auto rect_center_y = ( rect.Min.y + rect.Max.y ) * .5f;
	auto triangleStart = rect_center_x + 0.32f * rect_w;

	const auto r = .5f * rect_w / 2.f;
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

void Internal_NodeTrianglePin( const ImGUI::ImNodeStyle& style, bool is_connected, const ImColor& color ) {
	auto cursor = ImGui::GetCursorScreenPos( ) - style.Var_PinOffset;
	auto renderer = ImGui::GetWindowDrawList( );
	auto rect = ImRect( cursor, ImVec2{ cursor.x + style.Var_PinSize, cursor.y + style.Var_PinSize } );
	auto rect_w = rect.Max.x - rect.Min.x;

	const auto origin_scale = rect_w / 24.0f;
	const auto offset_x = 1.0f * origin_scale;
	const auto offset_y = 0.f * origin_scale;
	const auto margin = ( is_connected ? 2.f : 2.f ) * origin_scale;
	const auto rounding = 0.1f * origin_scale;
	const auto tip_round = 0.7f;
	const auto canvas = ImRect(
		rect.Min.x + margin + offset_x,
		rect.Min.y + margin + offset_y,
		rect.Max.x - margin + offset_x,
		rect.Max.y - margin + offset_y
	);
	const auto canvas_x = canvas.Min.x;
	const auto canvas_y = canvas.Min.y;
	const auto canvas_w = canvas.Max.x - canvas.Min.x;
	const auto canvas_h = canvas.Max.y - canvas.Min.y;

	const auto left = canvas_x + canvas_w * .5f * 0.3f;
	const auto right = canvas_x + canvas_w - canvas_w * .5f * 0.3f;
	const auto top = canvas_y + canvas_h * .5f * 0.2f;
	const auto bottom = canvas_y + canvas_h - canvas_h * .5f * 0.2f;
	const auto center_y = ( top + bottom ) * .5f;
	const auto tip_top = ImVec2( canvas_x + canvas_w * .5f, top );
	const auto tip_right = ImVec2( right, center_y );
	const auto tip_bottom = ImVec2( canvas_x + canvas_w * .5f, bottom );

	renderer->PathLineTo( ImVec2( left, top ) + ImVec2( 0, rounding ) );
	renderer->PathBezierCurveTo(
		ImVec2( left, top ),
		ImVec2( left, top ),
		ImVec2( left, top ) + ImVec2( rounding, 0 )
	);
	renderer->PathLineTo( tip_top );
	renderer->PathLineTo( tip_top + ( tip_right - tip_top ) * tip_round );
	renderer->PathBezierCurveTo(
		tip_right,
		tip_right,
		tip_bottom + ( tip_right - tip_bottom ) * tip_round
	);
	renderer->PathLineTo( tip_bottom );
	renderer->PathLineTo( ImVec2( left, bottom ) + ImVec2( rounding, 0 ) );
	renderer->PathBezierCurveTo(
		ImVec2( left, bottom ),
		ImVec2( left, bottom ),
		ImVec2( left, bottom ) - ImVec2( 0, rounding )
	);

	if ( !is_connected ) {
		if ( style.Color_Inner & 0xFF000000 )
			renderer->AddConvexPolyFilled( renderer->_Path.Data, renderer->_Path.Size, style.Color_Inner );

		renderer->PathStroke( color, true, 2.f * origin_scale );
	} else
		renderer->PathFillConvex( color );
}

void Internal_Image( nULong texture, const ImVec2& offset, const ImVec2& size ) {
	auto* window = ImGui::GetCurrentWindow( );
	const auto win_pos = window->Pos;
	const auto win_size = window->Size;
	const auto texture_id = reinterpret_cast<ImTextureID>( texture );

	// TODO : [Internal_Image] Clamp width and height to always render on the current window.

	window->DrawList->AddImage( texture_id, win_pos, win_pos + win_size );
}

void Internal_Sprite( ImTextureID sprite, const ImVec4& coords, const ImVec2& offset, const ImVec2& size ) {
	auto* window = ImGui::GetCurrentWindow( );

	const auto win_pos = window->Pos;
	const auto win_size = window->Size;
	const auto uv_min = ImVec2{ coords.x, coords.y };
	const auto uv_max = ImVec2{ coords.z, coords.w };

	// TODO : [Internal_Sprite] Clamp width and height to always render on the current window.

	window->DrawList->AddImage( sprite, offset, offset + size, uv_min, uv_max );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
ImGUI::ImSprite::ImSprite( ) 
	: sprite( 0 ),
	columns( 0 ),
	rows( 0 ),
	offset{ 1.f, 1.f }
{ }

ImGUI::ImSprite::ImSprite( ImTextureID sprite, nUByte columns, nUByte rows )
	: sprite( sprite ),
	columns( columns ),
	rows( rows ),
	offset{ 1.f / columns, 1.f / rows }
{ }

ImGUI::ImSprite::ImSprite( const OpenGL::Texture& texture, nUByte columns, nUByte rows )
	: columns( columns ),
	rows( rows ),
	offset{ 1.f / columns, 1.f / rows }
{ 
	nULong tmp = texture.ID;
	this->sprite = reinterpret_cast<ImTextureID>( tmp );
}

ImGUI::ImSprite::ImSprite( const OpenGL::Frame& frame, nUByte columns, nUByte rows )
	: columns( columns ),
	rows( rows ),
	offset{ 1.f / columns, 1.f / rows }
{
	nULong tmp = frame.color;
	this->sprite = reinterpret_cast<ImTextureID>( tmp );
}

bool ImGUI::ImSprite::GetIndices( nUByte& column, nUByte& row, nInt index ) const {
	if ( index < this->columns * this->rows ) {
		column = index / this->columns;
		row = index % this->rows;

		return true;
	}

	return false;
}

bool ImGUI::ImSprite::GetIsValid( ) const { return this->sprite > 0; }

ImVec4 ImGUI::ImSprite::GetCoords( nInt index ) const {
	nUByte column;
	nUByte row;

	if ( this->GetIndices( column, row, index ) )
		return this->GetCoords( column, row );

	return this->GetCoords( 0, 0 );
}

ImVec4 ImGUI::ImSprite::GetCoords( nUByte column, nUByte row ) const {
	float x = 0.f;
	float y = 0.f;

	if ( column > 0 && column < this->columns ) 
		x = column * this->offset.x;

	if ( row > 0 && row < this->rows )
		y = row * this->offset.y;

	return ImVec4{ x, y, this->offset.x, this->offset.y };
}

ImGUI::ImCanvasStyle::ImCanvasStyle( )
	: Size_Grid( 48.f ),
	Size_Selection{ .2f, .2f },
	Tiling( 1.f / 128.f ),
	Color_Background( 42, 42, 42, 255 ),
	Color_Grid( 52, 52, 52, 204 )
{ }

ImGUI::ImNodeStyle::ImNodeStyle( )
	: Var_PinSize( 24.f ),
	Var_Rounding( 4.f ),
	Var_SelectionSize{ 1.f, 1.f },
	Var_ImageSize{ 64.f, 64.f },
	Var_PinOffset{ Var_PinSize * .5f, 0.f },
	Var_PinTextOffset{ 0.f, 5.f },
	Var_Header( 0 ),
	Var_Icons( ),
	Color_Background{ 27, 28, 27, 255 },
	Color_Selection{ 239, 172, 0, 255 },
	Color_Comment{ 208, 208, 208, 255 },
	Color_Inner{ 32, 32, 32, 204 }
{ }

void ImGUI::ImNodeStyle::SetHeader( const OpenGL::Texture& texture ) {
	if ( OpenGL::IsValid( texture ) ) {
		nULong tmp = texture.ID;

		this->Var_Header = reinterpret_cast<ImTextureID>( tmp );
	}
}

void ImGUI::ImNodeStyle::SetIcons( const OpenGL::Texture& texture, nUByte columns, nUByte rows ) {
	if ( OpenGL::IsValid( texture ) )
		this->Var_Icons = ImGUI::ImSprite( texture, columns, rows );
}

ImGUI::ImCanvas::ImCanvas( float zoom_max )
	: zoom_level( 1.f ),
	zoom_max( zoom_max ),
	offset( ),
	curve_thickness( 5.f ),
	connection_indent( 1.f ),
	style( ),
	node_style( )
{ }

void ImGUI::ImCanvas::SetStyle( const ImGUI::ImCanvasStyle* style ) {
	if ( style ) {
#ifdef _WIN64
		memcpy_s( &this->style, sizeof( ImGUI::ImCanvasStyle ), style, sizeof( ImGUI::ImCanvasStyle ) );
#else
		memcpy( &this->style, style, sizeof( ImGUI::ImCanvasStyle ) );
#endif
	}
}

void ImGUI::ImCanvas::SetStyle( const ImGUI::ImCanvasStyle& style ) {
#ifdef _WIN64
	memcpy_s( &this->style, sizeof( ImGUI::ImCanvasStyle ), &style, sizeof( ImGUI::ImCanvasStyle ) );
#else
	memcpy( &this->style, &style, sizeof( ImGUI::ImCanvasStyle ) );
#endif
}

void ImGUI::ImCanvas::SetStyle( const ImNodeStyle* style ) {
	if ( style ) {
#ifdef _WIN64
		memcpy_s( &this->node_style, sizeof( ImGUI::ImNodeStyle ), style, sizeof( ImGUI::ImNodeStyle ) );
#else
		memcpy( &this->node_style, style, sizeof( ImGUI::ImNodeStyle ) );
#endif
	}
}

void ImGUI::ImCanvas::SetStyle( const ImNodeStyle& style ) {
#ifdef _WIN64
	memcpy_s( &this->node_style, sizeof( ImGUI::ImNodeStyle ), &style, sizeof( ImGUI::ImNodeStyle ) );
#else
	memcpy( &this->node_style, &style, sizeof( ImGUI::ImNodeStyle ) );
#endif
}

ImGUI::ImNode::ImNode( )
	: ImNode( "", "", false, ImColor{ 255, 255, 255, 255 }, 0, 0 )
{ }

ImGUI::ImNode::ImNode( nString label, nString description, bool is_centered, ImColor color )
	: ImNode( label, description, is_centered, color, 0, 0 )
{ }

ImGUI::ImNode::ImNode( nString label, nString description, bool is_centered, ImColor color, nUByte column, nUByte row )
	: label( label ),
	description( description ),
	is_centered( is_centered ),
	has_icon( true ),
	color( color ),
	column( column ),
	row( row )
{ }

ImGUI::ImNodePin::ImNodePin( ) 
	: ImNodePin( EImNodePinTypes::EPT_CIRCLE, "", ImColor{ 255, 255, 255, 255 } )
{ }

ImGUI::ImNodePin::ImNodePin( EImNodePinTypes type, nString label, ImColor color )
	: type( type ),
	label( label ),
	color( color )
{ }

void ImGUI::Setup( GLFW::Window& window, ImGuiContext*& context ) {
	context = ImGui::CreateContext( );
	ImGui::StyleColorsDark( );

	auto& io = ImGui::GetIO( );
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	auto& style = ImGui::GetStyle( );
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		style.Colors[ ImGuiCol_WindowBg ].w = 1.f;

	ImGui_ImplGlfw_InitForOpenGL( (GLFWwindow*)window.handle, true );
	ImGui_ImplOpenGL3_Init( "#version 450" );

	for ( int idx = 0; idx < ImGUI::PaletteSize; idx++ ) {
		ImGui::ColorConvertHSVtoRGB( idx / 31.0f, 0.8f, 0.8f, ImGUI::Palette[ idx ].x, ImGUI::Palette[ idx ].y, ImGUI::Palette[ idx ].z );
		ImGUI::Palette[ idx ].w = 1.0f;
	}
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

void ImGUI::SetPaletteColor( nUByte query_id, const ImColor& color ) {
	if ( query_id < ImGUI::PaletteSize )
		ImGUI::Palette[ query_id ] = color;
}

void ImGUI::Start( ImGuiContext* context ) {
	ImGui::SetCurrentContext( context );
	
	ImGui_ImplOpenGL3_NewFrame( );
	ImGui_ImplGlfw_NewFrame( );

	ImGui::NewFrame( );
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

bool ImGUI::TabBar( nString label, ImGuiTabBarFlags flags, float spacing ) {
	auto state = ImGui::BeginTabBar( label, flags );

	if ( state ) 
		ImGui::PushStyleVar( ImGuiStyleVar_ItemInnerSpacing, ImVec2{ spacing, 0.f } );

	return state;
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

void ImGUI::Sprite( const ImSprite& sprite, nInt index ) {
	ImGUI::Sprite( sprite, index, ImVec2{ }, ImVec2{ } );
}

void ImGUI::Sprite( const ImSprite& sprite, nUByte column, nUByte row ) {
	ImGUI::Sprite( sprite, column, row, ImVec2{ }, ImVec2{ } );
}

void ImGUI::Sprite( const ImSprite& sprite, nInt index, const ImVec2& offset ) {
	ImGUI::Sprite( sprite, index, offset, ImVec2{ } );
}

void ImGUI::Sprite( const ImSprite& sprite, nUByte column, nUByte row, const ImVec2& offset ) {
	ImGUI::Sprite( sprite, column, row, offset, ImVec2{ } );
}

void ImGUI::Sprite( const ImSprite& sprite, nInt index, const ImVec2& offset, const ImVec2& size ) {
	if ( sprite.GetIsValid( ) && !ImGUI::GetIsSkiped( ) ) {
		const auto coords = sprite.GetCoords( index );

		Internal_Sprite( sprite.sprite, coords, offset, size );
	}
}

bool ImGUI::Canvas( const ImCanvas& canvas ) {
	const auto size = ImGui::GetWindowSize( );

	return ImGUI::Canvas( canvas, ImVec2{ 0.f, 0.f }, size );
}

void ImGUI::Sprite( const ImSprite& sprite, nUByte column, nUByte row, const ImVec2& offset, const ImVec2& size ) {
	if ( sprite.GetIsValid( ) && !ImGUI::GetIsSkiped( ) ) {
		const auto coords = sprite.GetCoords( column, row );

		Internal_Sprite( sprite.sprite, coords, offset, size );
	}
}

bool ImGUI::Canvas( const ImCanvas& canvas, const ImVec2& offset, const ImVec2& size ) {
	if ( !ImGUI::GetIsSkiped( ) ) {
		auto position = ImGui::GetWindowPos( ) + offset;
		const auto grid = canvas.style.Size_Grid * canvas.zoom_level;

		auto* renderer = ImGui::GetWindowDrawList( );
		auto region = ImRect( position, position + size );

		ImGui::PushID( &canvas );
		ImGui::SetWindowFontScale( canvas.zoom_level );

		bool state = ImGui::ItemAdd( region, ImGui::GetID( &canvas ) );

		if ( state ) {
			renderer->AddRectFilled( region.Min, region.Max, canvas.style.Color_Background );

			for ( float x = fmodf( canvas.offset.x, grid ); x < size.x; ) {
				renderer->AddLine( ImVec2( x, 0 ) + position, ImVec2( x, size.y ) + position, canvas.style.Color_Grid );
				x += grid;
			}

			for ( float y = fmodf( canvas.offset.y, grid ); y < size.y; ) {
				renderer->AddLine( ImVec2( 0, y ) + position, ImVec2( size.x, y ) + position, canvas.style.Color_Grid );
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

void ImGUI::EndCanvas( const ImCanvas& canvas ) {
	ImGui::SetWindowFontScale( 1.f );
	ImGui::PopID( );
}

bool ImGUI::Node( const ImCanvas& canvas, const ImNodeStyle& style, const ImNode& node, const ImVec2& position ) {
	auto* renderer = ImGui::GetWindowDrawList( );
	auto pos = ImGui::GetWindowPos( ) + position * canvas.zoom_level + canvas.offset;

	renderer->ChannelsSplit( 2 );

	ImGui::SetCursorScreenPos( pos );
	ImGui::PushID( node.label );
	ImGui::BeginGroup( );

	renderer->ChannelsSetCurrent( 1 );

	if ( !node.is_centered ) {
		if ( node.has_icon && style.Var_Icons.GetIsValid( ) ) {
			ImGUI::Sprite( style.Var_Icons, node.column, node.row, pos, ImVec2{ 14.f * canvas.zoom_level, 14.f * canvas.zoom_level } );
			ImGui::SetCursorScreenPos( pos + ImVec2{ 18.f * canvas.zoom_level, 0.f } );
		}

		ImGui::TextUnformatted( node.label );
	}

	ImGui::Dummy( ImVec2{ 0.f, style.Var_PinSize * .25f } );

	return true;
}

void ImGUI::NodeInputPin( const ImNodeStyle& style, const ImNodePin& pin, bool has_link ) {
	switch ( pin.type ) {
		case EImNodePinTypes::EPT_TRIANGLE	: Internal_NodeTrianglePin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_SQUARE	: Internal_NodeSquarePin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_ARRAY		: Internal_NodeArrayPin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_DIAMOND	: Internal_NodeDiamondPin( style, has_link, pin.color ); break;

		default : Internal_NodeCirclePin( style, has_link, pin.color ); break;
	}

	const auto cursor = ImGui::GetCursorScreenPos( );

	ImGui::SetCursorScreenPos( cursor + style.Var_PinOffset + style.Var_PinTextOffset );
	ImGui::Text( pin.label );
}

void ImGUI::NodeOutputputPin( const ImNodeStyle& style, const ImNodePin& pin, bool has_link ) {
	ImGui::Text( pin.label );
	ImGui::SameLine( );

	const auto cursor = ImGui::GetCursorScreenPos( );

	ImGui::SetCursorScreenPos( cursor + ImVec2{ 4.f, -5.f } );

	switch ( pin.type ) {
		case EImNodePinTypes::EPT_TRIANGLE	: Internal_NodeTrianglePin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_SQUARE	: Internal_NodeSquarePin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_ARRAY		: Internal_NodeArrayPin( style, has_link, pin.color ); break;
		case EImNodePinTypes::EPT_DIAMOND	: Internal_NodeDiamondPin( style, has_link, pin.color ); break;

		default: Internal_NodeCirclePin( style, has_link, pin.color ); break;
	}

	ImGui::SetCursorScreenPos( cursor + ImVec2{ 0.f, style.Var_PinSize } );
}

void ImGUI::NodeContent( const ImNodeStyle& style ) {
	const auto cursor = ImGui::GetCursorScreenPos( );

	ImGui::SetCursorScreenPos( cursor + style.Var_PinTextOffset );
	ImGui::BeginGroup( );
}

void ImGUI::EndNodeContent( ) { ImGui::EndGroup( ); }

void ImGUI::NodeImage( const ImNodeStyle& style, const OpenGL::Texture& texture ) {
	if ( OpenGL::IsValid( texture ) ) {
		const auto cursor = ImGui::GetCursorScreenPos( );

		Internal_Image( texture.ID, cursor + style.Var_PinTextOffset, style.Var_ImageSize );
	}
}

void ImGUI::NodeImage( const ImNodeStyle& style, const OpenGL::Frame& frame ) {
	if ( OpenGL::IsValid( frame ) ) {
		const auto cursor = ImGui::GetCursorScreenPos( );
	
		Internal_Image( frame.color, cursor + style.Var_PinTextOffset, style.Var_ImageSize );
	}
}

void ImGUI::NodeSprite( const ImNodeStyle& style, const ImSprite& sprite, nInt index ) {
	if ( sprite.GetIsValid( ) ) {
		const auto cursor = ImGui::GetCursorScreenPos( );
		const auto coords = sprite.GetCoords( index );

		Internal_Sprite( sprite.sprite, coords, cursor + style.Var_PinTextOffset, style.Var_ImageSize );
	}
}

void ImGUI::NodeSprite( const ImNodeStyle& style, const ImSprite& sprite, nUByte column, nUByte row ) {
	if ( sprite.GetIsValid( ) ) {
		const auto cursor = ImGui::GetCursorScreenPos( );
		const auto coords = sprite.GetCoords( column, row );

		Internal_Sprite( sprite.sprite, coords, cursor + style.Var_PinTextOffset, style.Var_ImageSize );
	}
}

void ImGUI::EndNode( const ImCanvas& canvas, const ImNodeStyle& n_style, const ImNode& node, const ImVec2& position, bool is_selected ) {
	auto& style = ImGui::GetStyle( );
	auto* renderer = ImGui::GetWindowDrawList( );
	auto color_bg = ImColor( style.Colors[ ImGuiCol_Border ] );
	auto pos = ImGui::GetWindowPos( ) + position * canvas.zoom_level + canvas.offset;

	ImGui::EndGroup( );

	const auto node_rect = ImRect{
		ImGui::GetItemRectMin( ) - style.ItemInnerSpacing * canvas.zoom_level,
		( ImGui::GetItemRectMax( ) + ImVec2{ n_style.Var_PinSize, 0.f } ) + style.ItemInnerSpacing * canvas.zoom_level
	};

	const auto header_size = ImVec2{
		ImGui::GetItemRectSize( ).x + ( n_style.Var_PinSize - n_style.Var_Rounding ) + 14.f + style.ItemInnerSpacing.x * canvas.zoom_level,
		ImGUI::GetTextSize( node.label ).y + 3.f
	};

	if ( node.is_centered ) {
		auto name_pos = pos + ImVec2{ ( header_size.x - ImGUI::GetTextSize( node.label ).x ) * .5f, 0 };

		if ( node.has_icon && n_style.Var_Icons.GetIsValid( ) ) {
			ImGUI::Sprite( n_style.Var_Icons, node.column, node.row, name_pos, ImVec2{ 14.f * canvas.zoom_level, 14.f * canvas.zoom_level } );

			name_pos.x += 18.f;
		}

		renderer->AddText( name_pos, ImGUI::DEFAULT_COLOR, node.label );
	}

	renderer->ChannelsSetCurrent( 0 );
	renderer->AddRectFilled( node_rect.Min, node_rect.Max, n_style.Color_Background, n_style.Var_Rounding );

	if ( is_selected ) {
		auto rect_min = node_rect.Min - n_style.Var_SelectionSize;
		auto rect_max = node_rect.Max + n_style.Var_SelectionSize;

		renderer->AddRect( rect_min, rect_max, n_style.Color_Selection, n_style.Var_Rounding, 15, 2.f );
	} else 
		renderer->AddRect( node_rect.Min, node_rect.Max, color_bg, n_style.Var_Rounding );

	renderer->AddRectFilled( node_rect.Min, node_rect.Min + ImVec2{ header_size.x, 2.f * header_size.y }, node.color, n_style.Var_Rounding );
	renderer->ChannelsMerge( );

	ImGui::PopID( );
}

void ImGUI::NodeLink( const ImCanvas& canvas, const ImVec2& node_a, const ImVec2& node_b, const ImColor& color ) {
	auto* renderer = ImGui::GetWindowDrawList( );

	if ( renderer ) {
		auto thickness = canvas.curve_thickness * canvas.zoom_level;
		auto p2 = node_a - ImVec2{ 100 * canvas.zoom_level, 0 };
		auto p3 = node_b + ImVec2{ 100 * canvas.zoom_level, 0 };

		renderer->AddBezierCurve( node_a, p2, p3, node_b, color, thickness );
	}
}

void ImGUI::NodeLink( const ImCanvas& canvas, const ImVec2& node_a, const ImVec2& node_b, const ImColor& color_a, const ImColor& color_b ) {
	auto* renderer = ImGui::GetWindowDrawList( );

	if ( renderer ) {
		auto thickness = canvas.curve_thickness * canvas.zoom_level;
		auto p2 = node_a - ImVec2{ 100 * canvas.zoom_level, 0 };
		auto p3 = node_b + ImVec2{ 100 * canvas.zoom_level, 0 };

		renderer->AddBezierCurve( node_a, p2, p3, node_b, color_a, thickness );
	}
}

bool ImGUI::Category( nString label ) { return ImGUI::Category( label, "" ); }

bool ImGUI::Category( nString label, nString description ) {
	if ( nHelper::GetIsValid( label ) ) {
		ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2{ 0.f, 1.f } );

		auto state = ImGui::CollapsingHeader( label, ImGuiTreeNodeFlags_DefaultOpen );

		if ( state )
			ImGUI::Tooltip( description );

		ImGui::Dummy( ImVec2{ .0f, ImGUI::ItemSpacer } );

		return state;
	}

	return false;
}

void ImGUI::EndCategory( ) { ImGui::PopStyleVar( ); }

bool ImGUI::Item( nString label ) {
	if ( nHelper::GetIsValid( label ) ) {
		if ( ImGui::BeginTable( label, 2, ImGuiTableFlags_BordersV ) ) {
			ImGui::TableNextRow( );
			ImGui::TableSetColumnIndex( 0 );
			ImGui::Text( label );
			ImGui::TableSetColumnIndex( 1 );
			ImGui::PushItemWidth( ImGui::GetColumnWidth( ) );

			return true;
		}
	}

	return false;
}

void ImGUI::EndItem( ) {
	ImGui::PopItemWidth( );
	ImGui::EndTable( );
	ImGui::Dummy( ImVec2{ .0f, ImGUI::ItemSpacer } );
}

void ImGUI::ItemString( nString label, const nUInt length, char* text ) {
	if ( ImGUI::Item( label ) && text ) {
		ImGui::InputText( "", text, length );

		ImGUI::EndItem( );
	}
}

bool ImGUI::ItemCheckbox( nString label, bool& state ) {
	if ( ImGUI::Item( label ) ) {
		bool old_state = state;

		ImGui::Checkbox( "", &state );
		ImGUI::EndItem( );

		return state != old_state;
	}

	return false;
}

bool ImGUI::ItemDropList( nString label, nUInt& current_id, const nUInt count, nString* list ) {
	if ( ImGUI::Item( label ) && count > 0 && list ) {
		const nUInt old_id = current_id;

		ImGui::PushItemWidth( ImGui::GetColumnWidth( ) );

		if ( ImGui::BeginCombo( "", list[ current_id ], 0 ) ) {
			for ( nUInt idx = 0; idx < count; idx++ ) {
				const bool is_selected = ( idx == current_id );

				if ( ImGui::Selectable( list[ idx ], is_selected ) )
					current_id = idx;

				if ( is_selected )
					ImGui::SetItemDefaultFocus( );
			}

			ImGui::EndCombo( );
		}

		ImGUI::EndItem( );

		return current_id != old_id;
	}

	return false;
}

bool ImGUI::ItemDropList( nString label, nUInt& current_id, const std::vector<nString>& list ) {
	if ( ImGUI::Item( label ) && list.size( ) > 0 ) {
		const nUInt old_id = current_id;

		if ( ImGui::BeginCombo( "", list[ current_id ], 0 ) ) {
			for ( nUInt idx = 0; idx < list.size( ); idx++ ) {
				const bool is_selected = ( idx == current_id );

				if ( ImGui::Selectable( list[ idx ], is_selected ) )
					current_id = idx;

				if ( is_selected )
					ImGui::SetItemDefaultFocus( );
			}

			ImGui::EndCombo( );
		}

		ImGUI::EndItem( );

		return current_id != old_id;
	}

	return false;
}

void ImGUI::ItemPicker( nString label, ImVec4& color ) {
	if ( ImGUI::Item( label ) ) {
		ImGui::BeginGroup( );

		static ImVec4 backup_color;
		if ( ImGui::ColorButton( "##3c", color, ImGuiColorEditFlags_AlphaPreview ) ) {
			backup_color = color;
				ImGui::OpenPopup( "PickerUI" );
		}

		ImGui::SameLine( );
		ImGui::Dummy( ImVec2{ 2.f, 0.f } );
		ImGui::SameLine( );
		
		int i[ 4 ] = { IM_F32_TO_INT8_UNBOUND( color.x ), IM_F32_TO_INT8_UNBOUND( color.y ), IM_F32_TO_INT8_UNBOUND( color.z ), IM_F32_TO_INT8_UNBOUND( color.w ) };
		char buf[ 64 ];
		ImFormatString( buf, IM_ARRAYSIZE( buf ), "#%02X%02X%02X%02X",  i[ 0 ], i[ 1 ], i[ 2 ], i[ 3 ] );

		if ( ImGui::Button( buf, ImVec2{ ImGui::CalcItemWidth( ), ImGui::GetFrameHeight( ) } ) ) {
			backup_color = color;
			ImGui::OpenPopup( "PickerUI" );
		}

		ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2{ 2.f, 2.f } );
		if ( ImGui::BeginPopup( "PickerUI" ) ) {
			ImGui::Text( "Color Picker" );
			ImGui::Separator( );
			ImGui::ColorPicker4( "##picker", (float*)&color, ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview );
			ImGui::SameLine( );

			ImGui::BeginGroup( );
			ImGui::Text( "Current" );
			ImGui::ColorButton( "##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2( 60, 40 ) );
			ImGui::Text( "Previous" );
			if ( ImGui::ColorButton( "##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2( 60, 40 ) ) )
				color = backup_color;
			ImGui::Separator( );
			ImGui::Text( "Palette" );

			for ( int n = 0; n < ImGUI::PaletteSize; n++ ) {
				ImGui::PushID( n );
				if ( ( n % 8 ) != 0 )
					ImGui::SameLine( 0.0f, ImGui::GetStyle( ).ItemSpacing.y );

				ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
				if ( ImGui::ColorButton( "##palette", ImGUI::Palette[ n ], palette_button_flags, ImVec2( 20, 20 ) ) )
					color = ImVec4( ImGUI::Palette[ n ].x, ImGUI::Palette[ n ].y, ImGUI::Palette[ n ].z, color.w );

				if ( ImGui::BeginDragDropTarget( ) ) {
					if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( IMGUI_PAYLOAD_TYPE_COLOR_3F ) )
						memcpy( (float*)&ImGUI::Palette[ n ], payload->Data, sizeof( float ) * 3 );
					if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( IMGUI_PAYLOAD_TYPE_COLOR_4F ) )
						memcpy( (float*)&ImGUI::Palette[ n ], payload->Data, sizeof( float ) * 4 );
					ImGui::EndDragDropTarget( );
				}

				ImGui::PopID( );
			}

			ImGui::EndGroup( );
			ImGui::EndPopup( );
		}

		ImGui::PopStyleVar( );
		ImGui::EndGroup( );
		ImGUI::EndItem( );
	}
}

void ImGUI::ItemPicker( nString label, ImColor& color ) { 
	ImGUI::ItemPicker( label, color.Value );
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
		buffer[ text.length( ) ] = '\0';
		strncpy_s( buffer, text.data( ), text.size( ) );

		return ImGui::CalcTextSize( buffer );
	}

	return ImVec2{ };
}
