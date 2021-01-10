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

#ifndef _IGS_NUT_IMGUI_HPP_
#define _IGS_NUT_IMGUI_HPP_

	#ifndef IMGUI_DEFINE_MATH_OPERATORS
		#define IMGUI_DEFINE_MATH_OPERATORS
	#endif

	#include <ImGui/imgui.h>
	#include <ImGui/imgui_internal.h>

	#include "GLFW.hpp"
	#include "JSON.hpp"
	#include "OpenAL.hpp"
	#include "OpenGL.hpp"

	class NutStyle;
	class NutPanel;
	class NutWindow;
	class NutTextDocument;

	namespace ImGUI {

		struct ImCanvas {

			// Canvas Data
			float zoom_level;
			float zoom_max;
			ImVec2 offset;
			float curve_thickness;
			float connection_indent;

			// Canvas Style
			float Size_Grid;
			float Size_Pin;
			ImVec2 Size_Selection;
			float Rounding;
			float Tiling;
			ImColor Color_Background;
			ImColor Color_Grid;
			ImColor Color_Inner;
			ImColor Color_Selection;
			ImColor Color_Header;
			ImColor Color_Comment;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param zoom_max : Maximum zoom level of the canvas.
			 **/
			ImCanvas( float zoom_max );

		};

		void Setup( GLFW::Window& window );

		NUT_API void DockSpace( );

		/**
		 * LoadFont method
		 * @author : ALVES Quentin
		 * @note : Load a font from disk.
		 * @param path : Path to query font TTF file.
		 * @param size : Default font size.
		 **/
		NUT_API void LoadFont( nString path, float size );

		/**
		 * SetFont method
		 * @author : ALVES Quentin
		 * @note : Set current ImGui font.
		 * @param font_id : Index of the query font.
		 **/
		NUT_API void SetFont( nInt font_id );

		NUT_API void SetStyle( NutStyle* style );

		NUT_API void Start( );

		/**
		 * DequeueCharacters template method
		 * @author : ALVES Quentin
		 * @note : Dequeue characters from keyboard input.
		 * @template Callback : Capture lambda function.
		 * @template Args : Capture lambda function argumrnts types.
		 * @param callback :
		 * @param args :
		 **/
		template< typename Callback, typename... Args >
		void DequeueCharacters( Callback&& callback, Args... args );

		NUT_API bool Window( NutWindow* window );

		NUT_API bool Panel( NutPanel* panel );

		NUT_API bool Tab( NutTextDocument& document );

		NUT_API void EndTab( );

		NUT_API bool Modal( nString label );

		NUT_API bool Modal( nString label, bool is_visible );

		NUT_API bool ModalButton( nString label );

		NUT_API bool ModalButton( nString label, bool close_modal );

		NUT_API void CloseModal( );

		NUT_API void EndModal( );

		NUT_API bool Canvas( ImCanvas& canvas );

		NUT_API bool Canvas( ImCanvas& canvas, const ImVec2& offset, const ImVec2& size );

		NUT_API void Zoom( ImCanvas& canvas, float offset );

		NUT_API void SetZoom( ImCanvas& canvas, float zoom_level );

		NUT_API void EndCanvas( ImCanvas& canvas );

		NUT_API bool Tooltip( );

		NUT_API bool Tooltip( const ImRect& hover );

		NUT_API bool Tooltip( const ImVec2& min, const ImVec2& max );

		NUT_API void EndTooltip( );

		template<typename... Args>
		void Tooltip( nString format, Args... args );

		template<typename... Args>
		void Tooltip( const ImColor& foreground, nString format, Args... args );

		NUT_API void Rect( const ImVec2& start, const ImVec2& end, const ImVec4& color );

		NUT_API void Rect( const ImVec2& start, const ImVec2& end, const ImColor& color );

		NUT_API void RectFilled( const ImVec2& start, const ImVec2& end, const ImVec4& color );

		NUT_API void RectFilled( const ImVec2& start, const ImVec2& end, const ImColor& color );

		NUT_API void Image( const OpenGL::Texture& texture );

		NUT_API void Image( const OpenGL::Texture& texture, const ImVec2& offset );

		NUT_API void Image( const OpenGL::Texture& texture, const ImVec2& offset, const ImVec2& size );

		NUT_API void Image( const OpenGL::Frame& frame );

		NUT_API void Image( const OpenGL::Frame& frame, const ImVec2& offset );

		NUT_API void Image( const OpenGL::Frame& frame, const ImVec2& offset, const ImVec2& size );

		template<typename... Args>
		void Text( const ImVec4& foreground, const std::string_view& text );

		template<typename... Args>
		void Text( const ImVec4& foreground, const ImVec4& background, const std::string_view& text );

		template<typename... Args>
		void Text( const ImColor& foreground, const std::string_view& text );

		template<typename... Args>
		void Text( const ImColor& foreground, const ImColor& background, const std::string_view& text );

		template<typename... Args>
		void Text( const ImVec4& foreground, nString format, Args... args );

		template<typename... Args>
		void Text( const ImColor& foreground, nString format, Args... args );

		template<typename... Args>
		void Text( const ImVec4& foreground, const ImVec4& background, nString format, Args... args );

		template<typename... Args>
		void Text( const ImColor& foreground, const ImColor& background, nString format, Args... args );

		template<typename OnClick, typename... Args>
		void Button( nString label, const ImVec2& size, OnClick&& on_click, Args... args );

		NUT_API bool Category( nString label );

		NUT_API bool Category( nString label, nString description );

		NUT_API void EndCategory( );

		NUT_API void ItemHeader( );

		NUT_API void ItemFooter( );

		NUT_API void Stop( );

		void Cleanup( );

		/**
		 * GetIsSkiped function
		 * @author : ALVES Quentin
		 * @note : Get if the current window is skipped during rendering.
		 * @return : const bool
		 **/
		NUT_API const bool GetIsSkiped( );

		/**
		 * IsKeyPressed function
		 * @author : ALVES Quentin
		 * @note : Wrapper for ImGui::IsKeyPressed.
		 * @param query_key : Query key as ImGuiKey_.
		 * @return : const bool
		 **/
		NUT_API const bool GetIsKeyPressed( ImGuiKey_ query_key );

		/**
		 * GetIsShiftDown function
		 * @author : ALVES Quentin
		 * @note : Get if shift key is pressed.
		 * @return : const bool
		 **/
		NUT_API const bool GetIsShiftDown( );

		/**
		 * GetIsCtrltDown function
		 * @author : ALVES Quentin
		 * @note : Get if control key is pressed.
		 * @return : const bool
		 **/
		NUT_API const bool GetIsCtrltDown( );

		/**
		 * GetIsAltDown function
		 * @author : ALVES Quentin
		 * @note : Get if alt key is pressed.
		 * @return : const bool
		 **/
		NUT_API const bool GetIsAltDown( );

		/**
		 * GetMouseRelPos function
		 * @author : ALVES Quentin
		 * @note : Get the real mouse position on window.
		 * @return : const ImVec2
		 **/
		NUT_API const ImVec2 GetMouseRelPos( );

		/**
		 * GetMouseDelta function
		 * @author : ALVES Quentin
		 * @note : Get current mouse delta value.
		 * @return : const ImVec2
		 **/
		NUT_API const ImVec2 GetMouseDelta( );

		/**
		 * GetScrollWheel function
		 * @author : ALVES Quentin
		 * @note : Get current mouse horizontal scroll wheel value.
		 * @return : const float
		 **/
		NUT_API const float GetScrollWheelH( );

		/**
		 * GetScrollWheel function
		 * @author : ALVES Quentin
		 * @note : Get current mouse scroll wheel value.
		 * @return : const float
		 **/
		NUT_API const float GetScrollWheel( );

		/**
		 * GetPenPressure function
		 * @author : ALVES Quentin
		 * @note : Get current pen pressure value.
		 * @return : const float
		 **/
		NUT_API const float GetPenPressure( );

		/**
		 * GetLineHeight const function
		 * @author : ALVES Quentin
		 * @note : Get current ImGui line height.
		 * @return : const float
		 **/
		NUT_API const float GetLineHeight( );

		NUT_API const ImVec2 GetTextSize( const std::string_view& text );

		template<typename... Args>
		const ImVec2 GetTextSize( nString format, Args... args );

	};

	#include <Templates/ImGUI.hpp>

#endif
