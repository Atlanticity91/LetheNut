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

	// TODO : Description ToolTip
	// TODO : TimeLine
	// TODO : Patch Tooltip Rounding

	#define IMGUI_DEFINE_MATH_OPERATORS

	#include <LetheNut/Core.hpp>
	#include "OpenGL.hpp"
	#include <Thirdparty/ImGUI/imgui_internal.h>

	#define REG_VAR( TYPE, NAME, ... ) const TYPE NAME = __VA_ARGS__
	#define REG_VEC( QUERY, NAME, ... ) REG_VAR( QUERY, NAME, QUERY{ __VA_ARGS__ } )
	#define REG_VEC2( NAME, X, Y ) REG_VEC( ImVec2, NAME, X, Y )
	#define REG_VEC3( NAME, X, Y, Z ) REG_VEC( ImVec3, NAME, X, Y, Z )
	#define REG_VEC4( NAME, X, Y, Z, W ) REG_VEC( ImVec4, NAME, X, Y, Z, W )

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
		REG_VEC4( DEFAULT_COLOR, .8f, .8f, .8f, 1.f );

		// Internal colors
		REG_VEC4( AxeX_Normal, .8f, .1f, .15f, 1.f );
		REG_VEC4( AxeX_Hovered, .9f, .2f, .2f,  1.f );
		REG_VEC4( AxeY_Normal, .2f, .7f, .2f, 1.f );
		REG_VEC4( AxeY_Hovered, .3f, .8f, .3f, 1.f );
		REG_VEC4( AxeZ_Normal, .1f, .25f, .8f, 1.f );
		REG_VEC4( AxeZ_Hovered, .2f, .35f, .9f, 1.f );
		REG_VEC4( AxeW_Normal, .95f, .7f, .053f, 1.f );
		REG_VEC4( AxeW_Hovered, 1.f, .8f, .063f, 1.f );

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
		void LoadFont( nString path, float size );

		/**
		 * SetFont method
		 * @author : ALVES Quentin
		 * @note : Set current ImGui font.
		 * @param font_id : Index of the query font.
		 **/
		void SetFont( nInt font_id );

		/**
		 * ApplyStyle method
		 * @author : ALVES Quentin
		 * @note : Apply a style to ImGui.
		 * @param style : Reference to query style to apply.
		 **/
		void NUT_API ApplyStyle( NutStyle& style );

		/**
		 * Internal_StyleHeader method
		 * @author : ALVES Quentin
		 * @note : Internal ImGui custom widget header.
		 * @param label : Label of the widget.
		 * @param components : Count of element inside the widget.
		 **/
		void Internal_StyleHeader( nString label, int components );

		/**
		 * Internal_StyleFooter method
		 * @author : ALVES Quentin
		 * @note : Internal ImGui custom widget footer.
		 **/
		void Internal_StyleFooter( );

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
		 * GetIsShiftDown function
		 * @author : ALVES Quentin
		 * @note : Get if shift key is pressed.
		 * @return : const bool
		 **/
		const bool GetIsShiftDown( );

		/**
		 * GetIsCtrltDown function
		 * @author : ALVES Quentin
		 * @note : Get if control key is pressed.
		 * @return : const bool
		 **/
		const bool GetIsCtrltDown( );

		/**
		 * GetIsAltDown function
		 * @author : ALVES Quentin
		 * @note : Get if alt key is pressed.
		 * @return : const bool
		 **/
		const bool GetIsAltDown( );

		/**
		 * GetLineHeight const function
		 * @author : ALVES Quentin
		 * @note : Get current ImGui line height.
		 * @return : const float
		 **/
		const float GetLineHeight( );

		/**
		 * GetTextSize const function
		 * @author : ALVES Quentin
		 * @note : Get the size of a text with current font.
		 * @param text : The text you wan't size.
		 * @return : const ImVec2
		 **/
		const ImVec2 GetTextSize( nString text );

		/**
		 * Begin method
		 * @author : ALVES Quentin
		 * @note : Begin ImGui context.
		 **/
		void Begin( );

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
		void BeginPopup( nString label, ImGuiWindowFlags flags, ImVec2& size, float border_size, bool* is_open );

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
		void BeginDockspace( );

		/**
		 * BeginPanel method
		 * @author : ALVES Quentin
		 * @note : Begin a panel.
		 * @param label : Label of the menu button.
		 * @param padding : Padding of content on axes.
		 **/
		void BeginPanel( nString label, const ImVec2& padding );

		/**
		 * BeginPanel method
		 * @author : ALVES Quentin
		 * @note : Begin a panel.
		 * @param label : Label of the menu button.
		 * @param padding : Padding of content on axes.
		 **/
		void BeginPanel( nString label, const ImVec2&& padding );

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
		void Spacer( const ImVec2& spacing );

		/**
		 * Spacer method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spacer.
		 * @param spacing : Value for x and y spacing.
		 **/
		void Spacer( const ImVec2&& spacing );

		/**
		 * Spacer method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spacer.
		 * @param x : Spacing x value.
		 * @param y : Spacing y value.
		 **/
		void Spacer( const float x, const float y );

		/**
		 * Spring method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spring.
		 * @param value : Spring value.
		 **/
		void Spring( nInt value );

		/**
		 * Spring method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Spring.
		 **/
		void Spring( );

		/**
		 * Link method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Link using Bézier curve's.
		 * @param source : Source point of the link.
		 * @param destination : Destination point of the link.
		 * @param color : Color of the link.
		 * @param thickness : Thickness of the link.
		 **/
		void Link( const ImVec2& source, const ImVec2& destination, const ImVec4& color, float thickness );

		/**
		 * Link method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Link using Bézier curve's.
		 * @param source : Source point of the link.
		 * @param destination : Destination point of the link.
		 * @param color : Color of the link.
		 * @param thickness : Thickness of the link.
		 **/
		void Link( const ImVec2&& source, const ImVec2&& destination, const ImVec4&& color, float thickness );

		/**
		 * CircleIcon method
		 * @author : ALVES Quentin
		 * @note : Wrapper for drawing a circle icon.
		 * @param size : Size of the icon.
		 * @param is_filled : True to draw filled icon.
		 * @param color : Color of the icon.
		 * @param inner : Internal color of the icon if is not filled.
		 **/
		void CircleIcon( const float size, bool is_filled, const ImU32 color, const ImU32 inner );

		/**
		 * SquareIcon method
		 * @author : ALVES Quentin
		 * @note : Wrapper for drawing a square icon.
		 * @param size : Size of the icon.
		 * @param is_filled : True to draw filled icon.
		 * @param color : Color of the icon.
		 * @param inner : Internal color of the icon if is not filled.
		 **/
		void SquareIcon( const float size, bool is_filled, const ImU32 color, const ImU32 inner );

		/**
		 * DiamondIcon method
		 * @author : ALVES Quentin
		 * @note : Wrapper for drawing a diamond icon.
		 * @param size : Size of the icon.
		 * @param is_filled : True to draw filled icon.
		 * @param color : Color of the icon.
		 * @param inner : Internal color of the icon if is not filled.
		 **/
		void DiamondIcon( const float size, bool is_filled, const ImU32 color, const ImU32 inner );

		/**
		 * GridIcon method
		 * @author : ALVES Quentin
		 * @note : Wrapper for drawing a grid icon.
		 * @param size : Size of the icon.
		 * @param is_filled : True to draw filled icon.
		 * @param color : Color of the icon.
		 * @param inner : Internal color of the icon if is not filled.
		 **/
		void GridIcon( const float size, bool is_filled, const ImU32 color, const ImU32 inner );

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
		 * @note : Wrapper for Tooltip.
		 * @template OnFly : Lambda capture.
		 * @param on_fly : Current on fly lambda.
		 **/
		template< typename OnFly >
		void ToolTip( OnFly&& on_fly );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		void Text( const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground );

		/**
		 * Text method
		 * @author : ALVES Quentin
		 * @note : Wrapper for Tooltip.
		 * @param position : Position where draw the text.
		 * @param text : Query text to display.
		 * @param background : Text background color.
		 * @param foreground : Text foreground color.
		 **/
		void Text( const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground );

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
		void Text( ImDrawList* renderer, const ImVec2& position, nString text, const ImColor& background, const ImColor& foreground );

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
		void Text( ImDrawList* renderer, const ImVec2&& position, nString text, const ImColor&& background, const ImColor&& foreground );

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
		 * TreeNode template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for TreeNode.
		 * @template Content : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param flags : Flags for tree node creation.
		 * @param size : Size of the tree node.
		 * @param content : Current content lambda.
		 **/
		template< typename Content >
		void TreeNode( nString label, ImGuiTreeNodeFlags flags, Content&& content );

		/**
		 * TreeNode template method
		 * @author : ALVES Quentin
		 * @note : Wrapper for TreeNode.
		 * @template Settings : Lambda capture.
		 * @template Content : Lambda capture.
		 * @param label : Label of the tree node.
		 * @param flags : Flags for tree node creation.
		 * @param size : Size of the tree node.
		 * @param settings : Current settings lambda.
		 * @param content : Current content lambda.
		 **/
		template< typename Settings, typename Content >
		void TreeNode( nString label, ImGuiTreeNodeFlags flags, Settings&& settings, Content&& content );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 **/
		void Image( const OpenGL::Texture& texture );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		void Image( const OpenGL::Texture& texture, const ImVec2& position, const ImVec2& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL texture as image.
		 * @param texture : Reference to query OpenGL texture.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		void Image( const OpenGL::Texture& texture, const ImVec2&& position, const ImVec2&& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 **/
		void Image( const OpenGL::Frame& frame );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		void Image( const OpenGL::Frame& frame, const ImVec2& position, const ImVec2& size );

		/**
		 * Image method
		 * @author : ALVES Quentin
		 * @note : Wrapper for displaying OpenGL frame buffer as image.
		 * @param frame : Reference to query OpenGL frame buffer.
		 * @param position : Offset from current element to display the image.
		 * @param size : Size of the area to render the image.
		 **/
		void Image( const OpenGL::Frame& frame, const ImVec2&& position, const ImVec2&& size );

		/**
		 * RightClickPanel template method
		 * @author : ALVES Quentin
		 * @note : Right click popup management.
		 * @template Content : Lambda capture.
		 * @param content : Current content lambda.
		 **/
		template< typename Content >
		void RightClickPanel( Content&& content );

		/**
		 * EndPanel method
		 * @author : ALVES Quentin
		 * @note : End current panel.
		 **/
		void EndPanel( );

		/**
		 * EndDockSpace method
		 * @author : ALVES Quentin
		 * @note : End dockspace context.
		 **/
		void EndPopup( );

		/**
		 * End method
		 * @author : ALVES Quentin
		 * @note : End ImGui context.
		 **/
		void End( );

		/**
		 * Destroy method
		 * @author : ALVES Quentin
		 * @note : Destroy the current ImGUI instance.
		 **/
		void Destroy( );

	};

	#include <Templates/VendorImGUI.hpp>

#endif
