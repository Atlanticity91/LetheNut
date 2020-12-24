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

#ifndef _IGS_NUT_VENDOR_IMGUI_HPP_
#define _IGS_NUT_VENDOR_IMGUI_HPP_

	#ifndef IMGUI_DEFINE_MATH_OPERATORS
		#define IMGUI_DEFINE_MATH_OPERATORS
	#endif

	#include "OpenGL.hpp"
	#include <ImGui/imgui.h>
	#include <ImGui/imgui_internal.h>

	#define REG_VAR( TYPE, NAME, ... ) const TYPE NAME = __VA_ARGS__
	#define REG_VEC( QUERY, NAME, ... ) REG_VAR( QUERY, NAME, QUERY{ __VA_ARGS__ } )
	#define REG_VEC2( NAME, X, Y ) REG_VEC( ImVec2, NAME, X, Y )
	#define REG_VEC3( NAME, X, Y, Z ) REG_VEC( ImVec3, NAME, X, Y, Z )
	#define REG_VEC4( NAME, X, Y, Z, W ) REG_VEC( ImVec4, NAME, X, Y, Z, W )
	#define REG_COLOR( NAME, R, G, B, A ) REG_VAR( ImColor, NAME, { R, G, B, A } )

	class NutStyle;

	/**
	 * ImGUI namspace
	 * @author : ALVES Quentin
	 * @note : Contain ImGui code wrapper.
	 **/
	namespace ImGUI {

		REG_VAR( nString, NO_STRING, "" );
		REG_VAR( uint32_t, FONT_DEFAULT, 0 );
		REG_VAR( uint32_t, FONT_BOLD, 1 );
		REG_VAR( ImGuiTreeNodeFlags, TREE_FLAGS, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding );
		REG_VEC2( NO_PADDING, 0.f, 0.f );
		REG_VEC2( DEFAULT_PADDING, 1.f, 1.f );
		REG_COLOR( DEFAULT_COLOR, .8f, .8f, .8f, 1.f );
		REG_VEC2( UV_MIN, 0.f, 0.f );
		REG_VEC2( UV_MAX, 1.f, 1.f );
		REG_COLOR( WHITE, 255, 255, 255, 255 );

		REG_VAR( float, NODE_GRID_SIZE, 48.f );
		REG_VAR( float, NODE_ROUNDING, 4.f );
		REG_VAR( float, NODE_PIN_SIZE, 24.f );
		REG_VAR( float, NODE_TILING, 1.f / 128.f );
		REG_VEC2( NODE_SELECTION_SIZE, .2f, .2f );
		REG_COLOR( NODE_PIN_INNER, 32, 32, 32, 204 );
		REG_COLOR( NODE_SELECTION_COLOR, 242, 178, 13, 255 );
		REG_COLOR( NODE_HEADER_COLOR, 255, 255, 255, 28 );
		REG_COLOR( NODE_COMMENT_COLOR, 208, 208, 208, 255 );

		// Internal colors
		REG_COLOR( AxeX_Normal, .8f, .1f, .15f, 1.f );
		REG_COLOR( AxeX_Hovered, .9f, .2f, .2f,  1.f );
		REG_COLOR( AxeY_Normal, .2f, .7f, .2f, 1.f );
		REG_COLOR( AxeY_Hovered, .3f, .8f, .3f, 1.f );
		REG_COLOR( AxeZ_Normal, .1f, .25f, .8f, 1.f );
		REG_COLOR( AxeZ_Hovered, .2f, .35f, .9f, 1.f );
		REG_COLOR( AxeW_Normal, .95f, .7f, .053f, 1.f );
		REG_COLOR( AxeW_Hovered, 1.f, .8f, .063f, 1.f );

		/**
		 * ImCanvas struct
		 * @author : ALVES Quentin
		 * @note : Defined canvas struct.
		 **/
		struct ImCanvas {

			float zoom;
			ImVec2 offset;
			float curve_thickness;
			float connection_indent;

			float zoom_min;  
			float zoom_max;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImCanvas( float zoom_min, float zoom_max );

		};

		/**
		 * ImNodeContext struct
		 * @author : ALVES Quentin
		 * @note : Defined node context struct.
		 **/
		struct ImNodeContext {

			nString name;
			nString description;
			ImVec2 position;
			bool is_selected;
			bool is_centered;

		};

		/**
		 * ImNodeStyle struct
		 * @author : ALVES Quentin
		 * @note : Defined node node style struct.
		 **/
		struct ImNodeStyle {

			ImColor background;
			ImColor separator;
			ImTextureID texture;

		};

		/**
		 * Initialize method
		 * @author : ALVES Quentin
		 * @note : Initialize the current ImGUI instance.
		 * @param window : Pointer to current window handle.
		 **/
		void Initialize( nPointer& window );

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

		/**
		 * ApplyStyle method
		 * @author : ALVES Quentin
		 * @note : Apply a style to ImGui.
		 * @param style : Reference to query style to apply.
		 **/
		NUT_API void ApplyStyle( NutStyle& style );

		/**
		 * Internal_StyleHeader method
		 * @author : ALVES Quentin
		 * @note : Internal ImGui custom widget header.
		 * @param label : Label of the widget.
		 * @param components : Count of element inside the widget.
		 **/
		NUT_API void Internal_StyleHeader( nString label, int components );

		/**
		 * Internal_StyleFooter method
		 * @author : ALVES Quentin
		 * @note : Internal ImGui custom widget footer.
		 **/
		NUT_API void Internal_StyleFooter( );

		NUT_API const bool GetIsSkiped( );

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

		/**
		 * IsKeyPressed function
		 * @author : ALVES Quentin
		 * @note : Wrapper for ImGui::IsKeyPressed.
		 * @param query_key : Query key as ImGuiKey_.
		 * @return : const bool
		 **/
		NUT_API const bool IsKeyPressed( ImGuiKey_ query_key );

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

		/**
		 * GetTextSize const function
		 * @author : ALVES Quentin
		 * @note : Get the size of a text with current font.
		 * @param text : The text you wan't size.
		 * @return : const ImVec2
		 **/
		NUT_API const ImVec2 GetTextSize( nString text );

		/**
		 * Begin method
		 * @author : ALVES Quentin
		 * @note : Begin ImGui context.
		 **/
		NUT_API void Begin( );

		/**
		 * BeginPopup method
		 * @author : ALVES Quentin
		 * @note : Begin a popup context.
		 * @param label : Name of the new popup.
		 * @param flags : Flags of the new popup.
		 * @param size : Size of the new popup.
		 * @param border_size : Size of the popup frame border
		 * @param is_open : Pointer to boolean that hold the popup state.
		 **/
		NUT_API void BeginPopup( nString label, ImGuiWindowFlags flags, ImVec2& size, float border_size, bool* is_open );

		/**
		 * CreateModal template method
		 * @author : ALVES Quentin
		 * @note : Begin a popup context.
		 * @template Content : Lambda capture.
		 * @template Args : Aguments type capture.
		 * @param label : Label of the modal.
		 * @param size : Size of the modal.
		 * @param border_size : Size of modal border.
		 * @param is_open : Pointer of modal state.
		 * @param content : Current content lambda.
		 * @param args : Value for arguments.
		 **/
		template< typename Content, typename... Args >
		void CreateModal( nString label, ImVec2& size, float border_size, bool* is_open, Content&& content, Args... args );

		/**
		 * CreateModal template method
		 * @author : ALVES Quentin
		 * @note : Begin a popup context.
		 * @template Content : Lambda capture.
		 * @template Args : Aguments type capture.
		 * @param label : Label of the modal.
		 * @param size : Size of the modal.
		 * @param border_size : Size of modal border.
		 * @param is_open : Pointer of modal state.
		 * @param content : Current content lambda.
		 * @param args : Value for arguments.
		 **/
		template< typename Content, typename... Args >
		void CreateModal( nString label, ImVec2&& size, float border_size, bool* is_open, Content&& content, Args... args );

		/**
		 * BeginDockspace method
		 * @author : ALVES Quentin
		 * @note : Begin a dockspace context.
		 **/
		NUT_API void BeginDockspace( );

		/**
		 * BeginPanel method
		 * @author : ALVES Quentin
		 * @note : Begin a panel.
		 * @param label : Label of the menu button.
		 * @param padding : Padding of content on axes.
		 **/
		NUT_API void BeginPanel( nString label, const ImVec2& padding );

		/**
		 * BeginPanel method
		 * @author : ALVES Quentin
		 * @note : Begin a panel.
		 * @param label : Label of the menu button.
		 * @param padding : Padding of content on axes.
		 **/
		NUT_API void BeginPanel( nString label, const ImVec2&& padding );

		/**
		 * BeginCanvas method
		 * @author : ALVES Quentin
		 * @note : Begin a canvas.
		 * @param canvas : Query canvas context.
		 **/
		NUT_API void BeginCanvas( ImCanvas& canvas );

		/**
		 * BeginCanvas method
		 * @author : ALVES Quentin
		 * @note : Begin a canvas.
		 * @param canvas : Query canvas context.
		 * @param position : Position of the canvas on the current window.
		 * @param size : Size of the canvas.
		 **/
		NUT_API void BeginCanvas( ImCanvas& canvas, const ImVec2& position, const ImVec2& size );

		/**
		 * BeginCanvas method
		 * @author : ALVES Quentin
		 * @note : Begin a canvas.
		 * @param canvas : Query canvas context.
		 * @param position : Position of the canvas on the current window.
		 * @param size : Size of the canvas.
		 **/
		NUT_API void BeginCanvas( ImCanvas& canvas, const ImVec2&& position, const ImVec2&& size );

		/**
		 * BeginNode method
		 * @author : ALVES Quentin
		 * @note : Create a node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Current node context.
		 **/
		NUT_API void BeginNode( const ImCanvas& canvas, const ImNodeContext& node );

		/**
		 * MenurBar template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for MenurBar.
		 * @template Content : Lambda capture.
		 * @param label : Label of the menu bar.
		 * @param content : Current content lambda.
		 **/
		template< typename Content >
		void MenurBar( nString label, Content&& content );

		/**
		 * Spacer method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spacer.
		 * @param spacing : Value for x and y spacing.
		 **/
		NUT_API void Spacer( const ImVec2& spacing );

		/**
		 * Spacer method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spacer.
		 * @param spacing : Value for x and y spacing.
		 **/
		NUT_API void Spacer( const ImVec2&& spacing );

		/**
		 * Spacer method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spacer.
		 * @param x : Spacing x value.
		 * @param y : Spacing y value.
		 **/
		NUT_API void Spacer( const float x, const float y );

		/**
		 * Link method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Link using Bézier curve's.
		 * @param canvas : Current node canvas.
		 * @param source : Source point of the link.
		 * @param destination : Destination point of the link.
		 * @param color : Color of the link.
		 **/
		NUT_API void NodeLink( const ImCanvas& canvas, const ImVec2& source, const ImVec2& destination, const ImColor& color );

		/**
		 * Link method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Link using Bézier curve's.
		 * @param canvas : Current node canvas.
		 * @param source : Source point of the link.
		 * @param destination : Destination point of the link.
		 * @param color : Color of the link.
		 **/
		NUT_API void NodeLink( const ImCanvas& canvas, const ImVec2&& source, const ImVec2&& destination, const ImColor&& color );

		/**
		 * NodeCirclePin method
		 * @author : ALVES Quentin
		 * @note : Create a node circle pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeCirclePin( const bool is_connected, const ImColor& color );

		/**
		 * NodeCirclePin method
		 * @author : ALVES Quentin
		 * @note : Create a node circle pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeCirclePin( const bool is_connected, const ImColor&& color );

		/**
		 * NodeSquarePin method
		 * @author : ALVES Quentin
		 * @note : Create a node square pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeSquarePin( const bool is_connected, const ImColor& color );

		/**
		 * NodeSquarePin method
		 * @author : ALVES Quentin
		 * @note : Create a node square pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeSquarePin( const bool is_connected, const ImColor&& color );

		/**
		 * NodeDiamondPin method
		 * @author : ALVES Quentin
		 * @note : Create a node diamond pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeDiamondPin( const bool is_connected, const ImColor& color );

		/**
		 * NodeDiamondPin method
		 * @author : ALVES Quentin
		 * @note : Create a node diamond pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeDiamondPin( const bool is_connected, const ImColor&& color );

		/**
		 * NodeArrayPin method
		 * @author : ALVES Quentin
		 * @note : Create a node array pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeArrayPin( const bool is_connected, const ImColor& color );

		/**
		 * NodeArrayPin method
		 * @author : ALVES Quentin
		 * @note : Create a node array pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeArrayPin( const bool is_connected, const ImColor&& color );

		/**
		 * NodeTrianglePin method
		 * @author : ALVES Quentin
		 * @note : Create a node triangle pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeTrianglePin( const bool is_connected, const ImColor& color );

		/**
		 * NodeTrianglePin method
		 * @author : ALVES Quentin
		 * @note : Create a node triangle pin.
		 * @param is_connected : State of the pin.
		 * @param color : Color of the pin.
		 **/
		NUT_API void NodeTrianglePin( const bool is_connected, const ImColor&& color );

		/**
		 * MenuButton template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for MenuItem call from ImGui.
		 * @template OnClick : Lambda capture.
		 * @param label : Label of the menu button.
		 * @param shortcut : Shortcut of the button.
		 * @param is_active : Defined is the button can be triggered or not, true by default.
		 * @param callback : Current callback lambda.
		 **/
		template< typename OnClick >
		void MenuButton( nString label, nString shortcut, bool is_active, OnClick&& callback );

		/**
		 * ToolTip template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Text ToolTip from ImGui.
		 * @template Args : Type caprture for arguments of formated text.
		 * @param format : Formated text of the tool type.
		 * @param args : Formated text arguments values.
		 **/
		template< typename... Args >
		void ToolTip( nString format, Args... args );

		/**
		 * ToolTip template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Text ToolTip from ImGui.
		 * @template Args : Type caprture for arguments of formated text.
		 * @param color : Color of the formated text.
		 * @param format : Formated text of the tool type.
		 * @param args : Formated text arguments values.
		 **/
		template< typename... Args >
		void ToolTip( const ImColor& color, nString format, Args... args );

		/**
		 * ToolTip template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Text ToolTip from ImGui.
		 * @template Args : Type caprture for arguments of formated text.
		 * @param color : Color of the formated text.
		 * @param format : Formated text of the tool type.
		 * @param args : Formated text arguments values.
		 **/
		template< typename... Args >
		void ToolTip( const ImColor&& color, nString format, Args... args );

		/**
		 * ToolTip template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for ToolTip from ImGui.
		 * @template Content : Lambda capture.
		 * @template Args : Type caprture for Lambda.
		 * @param content : Lambda defined the ToolTip content.
		 * @param args : Lambda arguments values.
		 **/
		template< typename Content, typename... Args >
		void ToolTip( Content&& content, Args... args );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		NUT_API void Text( const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		NUT_API void Text( const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param renderer : Pointer to current ImGui draw list.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		NUT_API void Text( ImDrawList* renderer, const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param renderer : Pointer to current ImGui draw list.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		NUT_API void Text( ImDrawList* renderer, const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground );

		/**
		 * TextUnformatted method
		 * @author : ALVES Quentin
		 * @note : Draw a text on a panel.
		 * @param color : Color for the text.
		 * @param text : Query text to display.
		 * @param args : Arguments of the formated text.
		 **/
		template< typename... Args >
		void Text( const ImColor& color, nString format, Args... args );

		/**
		 * TextUnformatted method
		 * @author : ALVES Quentin
		 * @note : Draw a text on a panel.
		 * @param color : Color for the text.
		 * @param text : Query text to display.
		 * @param args : Arguments of the formated text.
		 **/
		template< typename... Args >
		void Text( const ImColor&& color, nString text, Args... args );

		/**
		 * Button template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Button.
		 * @template OnClick : Lambda capture.
		 * @param label : Label of the button.
		 * @param size : Size of the button.
		 * @param callback : Current callback lambda.
		 **/
		template< typename OnClick >
		void Button( nString label, const ImVec2& size, OnClick&& callback );

		/**
		 * Button template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Button.
		 * @template OnClick : Lambda capture.
		 * @param label : Label of the button.
		 * @param size : Size of the button.
		 * @param callback : Current callback lambda.
		 **/
		template< typename OnClick >
		void Button( nString label, const ImVec2&& size, OnClick&& callback );

		/**
		 * Checkbox template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template OnMark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 **/
		template< typename OnMark >
		void Checkbox( nString label, bool& state, OnMark&& mark );

		/**
		 * Checkbox template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template OnMark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 **/
		template< typename OnMark >
		void Checkbox( nString label, nString description, bool& state, OnMark&& mark );

		/**
		 * Checkbox template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template OnMark : Lambda capture.
		 * @template OnUnMark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 * @param unmark : Current unmark lambda.
		 **/
		template< typename OnMark, typename OnUnMark >
		void Checkbox( nString label, bool& state, OnMark&& mark, OnUnMark&& unmark );

		/**
		 * Checkbox template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Checkbox.
		 * @template OnMark : Lambda capture.
		 * @template OnUnMark : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param state : Reference to checkbox state.
		 * @param mark : Current mark lambda.
		 * @param unmark : Current unmark lambda.
		 **/
		template< typename OnMark, typename OnUnMark >
		void Checkbox( nString label, nString description, bool& state, OnMark&& mark, OnUnMark&& unmark );

		/**
		 * Slider template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for custom vector control.
		 * @template Length : How many axe in the widget.
		 * @template Type : Type of data.
		 * @param label : Label of the vector control.
		 * @param data : Pointer to query vector control data.
		 * @param reset : Reset value of the vector control.
		 **/
		template< size_t Length, typename Type >
		void Vector( nString label, Type* data, Type reset );

		/**
		 * Slider template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for custom vector control.
		 * @template Length : How many axe in the widget.
		 * @template Type : Type of data.
		 * @param label : Label of the vector control.
		 * @param data : Pointer to query vector control data.
		 * @param reset : Reset value of the vector control.
		 **/
		template< size_t Length, typename Type >
		void Vector( nString label, nString description, Type* data, Type reset );

		/**
		 * Slider template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for custom Slider.
		 * @template Length : How many slider in the widget.
		 * @template Type : Type of data.
		 * @param label : Label of the slider.
		 * @param data : Pointer to query slider data.
		 * @param min : Minimum value of the slider.
		 * @param max : Maximum value of the slider.
		 **/
		template< size_t Length, typename Type >
		void Slider( nString label, Type* data, Type min, Type max );

		/**
		 * Slider template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for custom Slider.
		 * @template Length : How many slider in the widget.
		 * @template Type : Type of data.
		 * @template OnChange : Lambda capure.
		 * @param label : Label of the slider.
		 * @param previous : Reference to the previous value.
		 * @param list : List of string inside the drop list.
		 * @param data : Reference to data changer by the drop options.
		 * @param on_change : on_change Lambda capture.
		 **/
		template< size_t Length, typename Type, typename OnChange >
		void DropList( nString label, nString& previous, nString* list, Type& data, OnChange&& on_change );

		/**
		 * Tree template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tree from ImGui.
		 * @template Content : Lambda capture for Tree content.
		 * @template Args : Type captyre for content lambda arguments.
		 * @param label : Query tree label.
		 * @param content : Lambda that defined tree content.
		 * @param args : Arguments for content lambda.
		 **/
		template< typename Content, typename... Args >
		void Tree( nString label, Content&& content, Args... args );

		/**
		 * Tree template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tree from ImGui.
		 * @template Content : Lambda capture for Tree content.
		 * @template Args : Type captyre for content lambda arguments.
		 * @param label : Query tree label.
		 * @param flags : Flags for tree creation.
		 * @param content : Lambda that defined tree content.
		 * @param args : Arguments for content lambda.
		 **/
		template< typename Content, typename... Args >
		void Tree( nString label, ImGuiTreeNodeFlags flags, Content&& content, Args... args );

		/**
		 * Tree template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tree from ImGui.
		 * @template Content : Lambda capture for Tree content.
		 * @template Args : Type captyre for content lambda arguments.
		 * @param label : Query tree label.
		 * @param description : Query tree description.
		 * @param content : Lambda that defined tree content.
		 * @param args : Arguments for content lambda.
		 **/
		template< typename Content, typename... Args >
		void Tree( nString label, nString description, Content&& content, Args... args );

		/**
		 * Tree template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tree from ImGui.
		 * @template Content : Lambda capture for Tree content.
		 * @template Args : Type captyre for content lambda arguments.
		 * @param label : Query tree label.
		 * @param description : Query tree description.
		 * @param flags : Flags for tree creation.
		 * @param content : Lambda that defined tree content.
		 * @param args : Arguments for content lambda.
		 **/
		template< typename Content, typename... Args >
		void Tree( nString label, nString description, ImGuiTreeNodeFlags flags, Content&& content, Args... args );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 **/
		NUT_API void Image( const OpenGL::Texture& texture );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		NUT_API void Image( const OpenGL::Texture& texture, const ImVec2& position, const ImVec2& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		NUT_API void Image( const OpenGL::Texture& texture, const ImVec2&& position, const ImVec2&& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 **/
		NUT_API void Image( const OpenGL::Frame& frame );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		NUT_API void Image( const OpenGL::Frame& frame, const ImVec2& position, const ImVec2& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		NUT_API void Image( const OpenGL::Frame& frame, const ImVec2&& position, const ImVec2&& size );

		/**
		 * RightClickPanel template method
		 * @author : ALVES Quentin
		 * @note : Right click popup management.
		 * @template Content : Lambda capture.
		 * @param over_items : True to display over other items.
		 * @param content : Current content lambda.
		 **/
		template< typename Content >
		void RightClickPanel( bool over_items, Content&& content );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param title : Title of the node.
		 * @param position : Position of the node on the canvas.
		 * @param color : Color of the node.
		 * @param is_selected : Defined if the node is selected.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImColor& color );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Query node context.
		 * @param color : Color of the node.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImColor&& color );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Query node context.
		 * @param style : Current node style.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImNodeStyle& style );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Query node context.
		 * @param style : Current node style.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImNodeStyle&& style );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Query node context.
		 * @param color : Color of the node.
		 * @param position : Position offset of the node.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImColor& color, const ImVec2& position );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End the current node on a canvas.
		 * @param canvas : Current context canvas where draw the node.
		 * @param node : Query node context.
		 * @param color : Color of the node.
		 * @param position : Position offset of the node.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, ImNodeContext& node, const ImColor&& color, const ImVec2&& position );

		/**
		 * EndCanvas method
		 * @author : ALVES Quentin
		 * @note : End current canvas.
		 **/
		NUT_API void EndCanvas( );

		/**
		 * EndPanel method
		 * @author : ALVES Quentin
		 * @note : End current panel.
		 **/
		NUT_API void EndPanel( );

		/**
		 * EndDockSpace method
		 * @author : ALVES Quentin
		 * @note : End dockspace context.
		 **/
		NUT_API void EndPopup( );

		/**
		 * End method
		 * @author : ALVES Quentin
		 * @note : End ImGui context.
		 **/
		NUT_API void End( );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy the current ImGUI instance.
		 **/
		void Destroy( );

	};

	#include <Templates/VendorImGUI.hpp>

#endif
