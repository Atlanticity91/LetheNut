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

	// TODO : Divide ImGui API's to sub file for maintenance and redability.

	#ifndef IMGUI_DEFINE_MATH_OPERATORS
		#define IMGUI_DEFINE_MATH_OPERATORS
	#endif

	#include <Thirdparty/ImGui/imgui.h>
	#include <Thirdparty/ImGui/imgui_internal.h>

	#include "GLFW.hpp"
	#include "JSON.hpp"
	#include "OpenAL.hpp"
	#include "OpenGL.hpp"

	class NutStyle;
	class NutPanel;
	class NutWindow;
	class NutTextDocument;

	#define REG_VAR( TYPE, NAME, ... )		const TYPE NAME = __VA_ARGS__
	#define REG_VEC( QUERY, NAME, ... )		REG_VAR( QUERY, NAME, QUERY{ __VA_ARGS__ } )
	#define REG_VEC2( NAME, X, Y )			REG_VEC( ImVec2, NAME, X, Y )
	#define REG_VEC4( NAME, X, Y, Z, W )	REG_VEC( ImVec4, NAME, X, Y, Z, W )
	#define REG_COLOR( NAME, R, G, B, A )	REG_VAR( ImColor, NAME, { R, G, B, A } )

	/**
	 * ImGUI namespace
	 * @author : ALVES Quentin
	 * @node : Wrapper for ImGui.
	 **/
	namespace ImGUI {

		REG_COLOR( DEFAULT_COLOR,	.8f, .8f, .8f, 1.f );
		REG_COLOR( AxeX_Normal,		204,  26,  38, 255 );
		REG_COLOR( AxeX_Hovered,	230,  51,  51, 255 );
		REG_COLOR( AxeY_Normal,		 51,  77,  51, 255 );
		REG_COLOR( AxeY_Hovered,	 77, 204,  77, 255 );
		REG_COLOR( AxeZ_Normal,		 26,  64, 204, 255 );
		REG_COLOR( AxeZ_Hovered,	 51,  89, 230, 255 );
		REG_COLOR( AxeW_Normal,		242, 179,  14, 255 );
		REG_COLOR( AxeW_Hovered,	255, 204,  16, 255 );

		REG_VAR( float, ItemSpacer, .75f );
		REG_VAR( nUByte, PaletteSize, 32 );

		static ImVec4 Palette[ ImGUI::PaletteSize ];

		/**
		 * ImSprite struct
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Sprite core struct.
		 **/
		struct NUT_API ImSprite {
			
			ImTextureID sprite;
			nUByte columns;
			nUByte rows;
			ImVec2 offset;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImSprite( );

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param sprite : Query sprite.
			 * @param columns : Columns count. 
			 * @param rows : Rows count.
			 **/
			ImSprite( ImTextureID sprite, nUByte columns, nUByte rows );

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param texture : Texture used as sprite.
			 * @param columns : Columns count.
			 * @param rows : Rows count.
			 **/
			ImSprite( const OpenGL::Texture& texture, nUByte columns, nUByte rows );

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param frame : Frame Buffer used as sprite.
			 * @param columns : Columns count.
			 * @param rows : Rows count.
			 **/
			ImSprite( const OpenGL::Frame& frame, nUByte columns, nUByte rows );

			/**
			 * GetIsValid const function
			 * @author : ALVES Quentin
			 * @note : Get if the current sprite is valid.
			 * @return : bool
			 **/
			bool GetIsValid( ) const;

			/**
			 * GetIndices const function
			 * @author : ALVES Quentin
			 * @note : Convert index to 2D coordinates.
			 * @param column : Refernce to hold the current sprite column.
			 * @param row : Refernce to hold the current sprite row.
			 * @param index : Index of the query sprite.
			 * @return : bool
			 **/
			bool GetIndices( nUByte& column, nUByte& row, nInt index ) const;

			/**
			 * GetCoords const function
			 * @author : ALVES Quentin
			 * @note : Get sprite coordinates.
			 * @param index : Index of the query sprite.
			 * @return : ImVec4
			 **/
			ImVec4 GetCoords( nInt index ) const;

			/**
			 * GetCoords const function
			 * @author : ALVES Quentin
			 * @note : Get sprite coordinates.
			 * @param columns : Column of query sprite. 
			 * @param rows : Row of query sprite.
			 * @return : ImVec4
			 **/
			ImVec4 GetCoords( nUByte column, nUByte row ) const;

		};

		/**
		 * ImCanvas struct
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Canvas Style core struct.
		 **/
		struct NUT_API ImCanvasStyle {

			float Size_Grid;
			ImVec2 Size_Selection;
			float Tiling;
			ImColor Color_Background;
			ImColor Color_Grid;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImCanvasStyle( );

		};

		/**
		 * ImNodeStyle struct
		 * @author : ALVES Quentin
		 * @note : Defined ImGui Node Style struct.
		 **/
		struct NUT_API ImNodeStyle {

			float Var_PinSize;
			float Var_Rounding;
			ImVec2 Var_SelectionSize;
			ImVec2 Var_ImageSize;
			ImVec2 Var_PinOffset;
			ImVec2 Var_PinTextOffset;
			ImTextureID Var_Header;
			ImSprite Var_Icons;

			ImColor Color_Background;
			ImColor Color_Selection;
			ImColor Color_Comment;
			ImColor Color_Inner;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImNodeStyle( );

			/**
			 * SetHeader method
			 * @author : ALVES Quentin
			 * @note : Set current header texture.
			 * @param texture : Node header texture.
			 **/
			void SetHeader( const OpenGL::Texture& texture );

			/**
			 * SetIcons method
			 * @author : ALVES Quentin
			 * @note : Set current icons texture.
			 * @param texture : Node icon texture.
			 * @param columns : 
			 * @param rows : 
			 **/
			void SetIcons( const OpenGL::Texture& texture, nUByte columns, nUByte rows );

		};

		/**
		 * ImCanvas struct
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Canvas core struct.
		 **/
		struct NUT_API ImCanvas {

			float zoom_level;
			float zoom_max;
			ImVec2 offset;
			float curve_thickness;
			float connection_indent;
			ImCanvasStyle style;
			ImNodeStyle node_style;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param zoom_max : Maximum zoom level of the canvas.
			 **/
			ImCanvas( float zoom_max );

			/**
			 * SetStyle method
			 * @author : ALVES Quentin
			 * @node : Set current canvas style.
			 * @param style : Query new style.
			 **/
			void SetStyle( const ImCanvasStyle* style );

			/**
			 * SetStyle method
			 * @author : ALVES Quentin
			 * @node : Set current canvas style.
			 * @param style : Query new style.
			 **/
			void SetStyle( const ImCanvasStyle& style );

			/**
			 * SetStyle method
			 * @author : ALVES Quentin
			 * @node : Set current node style.
			 * @param style : Query new node style.
			 **/
			void SetStyle( const ImNodeStyle* style );

			/**
			 * SetStyle method
			 * @author : ALVES Quentin
			 * @node : Set current node style.
			 * @param style : Query new node style.
			 **/
			void SetStyle( const ImNodeStyle& style );

		};

		/**
		 * ImNode struct
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Node core struct.
		 **/
		struct NUT_API ImNode {

			nString label;
			nString description;
			bool is_centered;
			bool has_icon;
			ImColor color;
			nUByte column;
			nUByte row;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImNode( );

			ImNode( nString label, nString description, bool is_centered, ImColor color );

			ImNode( nString label, nString description, bool is_centered, ImColor color, nUByte column, nUByte row );

		};

		/**
		 * EImNodePinTypes enum
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Node Pin type enum.
		 **/
		enum NUT_API EImNodePinTypes {

			EPT_TRIANGLE,
			EPT_CIRCLE,
			EPT_SQUARE,
			EPT_ARRAY,
			EPT_DIAMOND,

		};

		/**
		 * ImNodePin struct
		 * @author : ALVES Quentin
		 * @node : Defined ImGui Node Pin core struct.
		 **/
		struct NUT_API ImNodePin {

			EImNodePinTypes type;
			nString label;
			ImColor color;

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 **/
			ImNodePin( );

			/**
			 * Constructor
			 * @author : ALVES Quentin
			 * @param type : Type of pin.
			 * @param label : Label of the pin.
			 * @param color : Color of the pin.
			 **/
			ImNodePin( EImNodePinTypes type, nString label, ImColor color );

		};

		/**
		 * Setup method
		 * @author : ALVES Quentin
		 * @note : Setup ImGui.
		 * @param window : Current GLFW window.
		 * @param context : Curent ImGui context.
		 **/
		void Setup( GLFW::Window& window, ImGuiContext*& context );

		/**
		 * DockSpace method
		 * @author : ALVES Quentin
		 * @note : Setup ImGui DockSpace environement.
		 **/
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

		/**
		 * SetStyle method
		 * @author : ALVES Quentin
		 * @note : Set current ImGui style.
		 * @param style : Pointer to current style.
		 **/
		NUT_API void SetStyle( NutStyle* style );

		/**
		 * SetPaletteColor method
		 * @author : ALVES Quentin
		 * @note : Set a color of the current ImGUI color palette.
		 * @param query_id : Index of the query color on the palette.
		 * @param color : New color value.
		 **/
		NUT_API void SetPaletteColor( nUByte query_id, const ImColor& color );

		/**
		 * Start method
		 * @author : ALVES Quentin
		 * @note : Start ImGui context.
		 * @param context : Pointer to current ImGui context.
		 **/
		NUT_API void Start( ImGuiContext* context );

		/**
		 * DequeueCharacters template method
		 * @author : ALVES Quentin
		 * @note : Dequeue characters from keyboard input.
		 * @template Callback : Capture lambda function.
		 * @template Args : Capture lambda function argumrnts types.
		 * @param callback : Callback for characters.
		 * @param args : Arguements of the callback.
		 **/
		template< typename Callback, typename... Args >
		void DequeueCharacters( Callback&& callback, Args... args );

		/**
		 * Window function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Window.
		 * @param window : Window storage.
		 * @return : bool
		 **/
		NUT_API bool Window( NutWindow* window );

		/**
		 * Panel function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Panel.
		 * @param window : Panel storage.
		 * @return : bool
		 **/
		NUT_API bool Panel( NutPanel* panel );

		/**
		 * TabBar function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Tab Bar for a Nut Text Document.
		 * @param label : Label of the tab bar.
		 * @param flags : Tab bar flags.
		 * @param spacing : Spacing between the tabs of the tab bar.
		 * @return : bool
		 **/
		NUT_API bool TabBar( nString label, ImGuiTabBarFlags flags, float spacing );

		/**
		 * Tab function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Tab for a Nut Text Document.
		 * @param document : Document contained in the tab.
		 * @return : bool
		 **/
		NUT_API bool Tab( NutTextDocument& document );

		/**
		 * EndTab method
		 * @author : ALVES Quentin
		 * @note : End ImGui Tab for a Nut Text Document.
		 **/
		NUT_API void EndTab( );

		/**
		 * Modal function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Panel.
		 * @param label : Label of the modal.
		 * @return : bool
		 **/
		NUT_API bool Modal( nString label );

		/**
		 * Modal function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Panel.
		 * @param label : Label of the modal.
		 * @param is_visible : Toggle modal visibility.
		 * @return : bool
		 **/
		NUT_API bool Modal( nString label, bool is_visible );

		/**
		 * ModalButton function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Panel.
		 * @param label : Label of the modal button.
		 * @return : bool
		 **/
		NUT_API bool ModalButton( nString label );

		/**
		 * ModalButton function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Panel.
		 * @param label : Label of the modal button.
		 * @param close_modal : True to close to modal.
		 * @return : bool
		 **/
		NUT_API bool ModalButton( nString label, bool close_modal );

		/**
		 * CloseModal method
		 * @author : ALVES Quentin
		 * @note : Close current ImGui Modal.
		 **/
		NUT_API void CloseModal( );

		/**
		 * EndModal method
		 * @author : ALVES Quentin
		 * @note : End ImGui Modal.
		 **/
		NUT_API void EndModal( );

		/**
		 * Tooltip function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Tooltip.
		 * @return : bool
		 **/
		NUT_API bool Tooltip( );

		/**
		 * Tooltip function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Tooltip.
		 * @param hover : Bounding box use for hover check.
		 * @return : bool
		 **/
		NUT_API bool Tooltip( const ImRect& hover );

		/**
		 * Tooltip function
		 * @author : ALVES Quentin
		 * @note : Create ImGui Tooltip.
		 * @param min : Bounding box min use for hover check.
		 * @param max : Bounding box max use for hover check.
		 * @return : bool
		 **/
		NUT_API bool Tooltip( const ImVec2& min, const ImVec2& max );

		/**
		 * EndTooltip method
		 * @author : ALVES Quentin
		 * @note : End current ImGui Tooltip.
		 **/
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

		NUT_API void Sprite( const ImSprite& sprite, nInt index );

		NUT_API void Sprite( const ImSprite& sprite, nUByte column, nUByte row );

		NUT_API void Sprite( const ImSprite& sprite, nInt index, const ImVec2& offset );

		NUT_API void Sprite( const ImSprite& sprite, nUByte column, nUByte row, const ImVec2& offset );

		NUT_API void Sprite( const ImSprite& sprite, nInt index, const ImVec2& offset, const ImVec2& size );

		NUT_API void Sprite( const ImSprite& sprite, nUByte column, nUByte row, const ImVec2& offset, const ImVec2& size );

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

		/**
		 * Canvas function
		 * @author : ALVES Quentin
		 * @note : Begin a canvas.
		 * @param canvas : Canvas data.
		 * @return : bool
		 **/
		NUT_API bool Canvas( const ImCanvas& canvas );

		/**
		 * Canvas function
		 * @author : ALVES Quentin
		 * @note : Begin a canvas.
		 * @param canvas : Canvas data.
		 * @param offset : Offset of the canvas from current window left.
		 * @param size : Size of the canvas.
		 * @return : bool
		 **/
		NUT_API bool Canvas( const ImCanvas& canvas, const ImVec2& offset, const ImVec2& size );
		
		/**
		 * Zoom method
		 * @author : ALVES Quentin
		 * @note : Zoom inside a canvas.
		 * @param canvas : Query canvas.
		 * @param offset : Canvas zoom offset.
		 **/
		NUT_API void Zoom( ImCanvas& canvas, float offset );

		/**
		 * SetZoom method
		 * @author : ALVES Quentin
		 * @note : Set Zoom level of a canvas.
		 * @param canvas : Query canvas.
		 * @param offset : Canvas zoom offset.
		 **/
		NUT_API void SetZoom( ImCanvas& canvas, float zoom_level );

		/**
		 * EndCanvas method
		 * @author : ALVES Quentin
		 * @note : End current canvas.
		 * @param canvas : Query canvas.
		 **/
		NUT_API void EndCanvas( const ImCanvas& canvas );

		NUT_API bool Node( const ImCanvas& canvas, const ImNodeStyle& style, const ImNode& node, const ImVec2& position );

		NUT_API void NodeInputPin( const ImNodeStyle& style, const ImNodePin& pin, bool has_link );

		NUT_API void NodeOutputputPin( const ImNodeStyle& style, const ImNodePin& pin, bool has_link );

		NUT_API void NodeContent( const ImNodeStyle& style );

		NUT_API void EndNodeContent( );

		NUT_API void NodeImage( const ImNodeStyle& style, const OpenGL::Texture& texture );

		NUT_API void NodeImage( const ImNodeStyle& style, const OpenGL::Frame& frame );

		NUT_API void NodeSprite( const ImNodeStyle& style, const ImSprite& sprite, nInt index );

		NUT_API void NodeSprite( const ImNodeStyle& style, const ImSprite& sprite, nUByte column, nUByte row );

		/**
		 * EndNode method
		 * @author : ALVES Quentin
		 * @note : End a node.
		 * @param canvas : Query canvas.
		 **/
		NUT_API void EndNode( const ImCanvas& canvas, const ImNodeStyle& style, const ImNode& node, const ImVec2& position, bool is_selected );

		/**
		 * NodeLink method
		 * @author : ALVES Quentin
		 * @note : End a node.
		 * @param canvas : Query canvas.
		 * @param node_a : Start pin of the link.
		 * @param node_b : End pin of  the link.
		 * @parma color : Query link color.
		 **/
		NUT_API void NodeLink( const ImCanvas& canvas, const ImVec2& node_a, const ImVec2& node_b, const ImColor& color );

		/**
		 * NodeLink method
		 * @author : ALVES Quentin
		 * @note : End a node.
		 * @param canvas : Query canvas.
		 * @param node_a : Start pin of the link.
		 * @param node_b : End pin of  the link.
		 * @param color_a : Query link color from start pin.
		 * @param color_b : Query link color from stop pin.
		 **/
		NUT_API void NodeLink( const ImCanvas& canvas, const ImVec2& node_a, const ImVec2& node_b, const ImColor& color_a, const ImColor& color_b );

		/**
		 * Category function
		 * @author : ALVES Quentin
		 * @note : Begin a category.
		 * @param label : Name of the category.
		 * @return : bool
		 **/
		NUT_API bool Category( nString label );

		/**
		 * Category function
		 * @author : ALVES Quentin
		 * @note : Begin a category.
		 * @param label : Name of the category.
		 * @param description : Description of the category.
		 * @return : bool
		 **/
		NUT_API bool Category( nString label, nString description );

		/**
		 * EndCategory method
		 * @author : ALVES Quentin
		 * @note : End current category.
		 **/
		NUT_API void EndCategory( );

		/**
		 * Item function
		 * @author : ALVES Quentin
		 * @note : Begin category item.
		 * @param label : Label of the item.
		 * @return : bool 
		 **/
		NUT_API bool Item( nString label );

		/**
		 * EndItem method
		 * @author : ALVES Quentin
		 * @note : End category item.
		 **/
		NUT_API void EndItem( );

		/**
		 * ItemString method
		 * @author : ALVES Quentin
		 * @note : Create a string input for category.
		 * @param label : String input label.
		 * @param length : Length of the string.
		 * @param text : Query string.
		 **/
		NUT_API void ItemString( nString label, const nUInt length, char* text );

		/**
		 * ItemCheckbox method
		 * @author : ALVES Quentin
		 * @note : Create a checkbox for category, return true when state change.
		 * @param label : Checkbox label.
		 * @param state : Checkbox state.
		 * @return : bool
		 **/
		NUT_API bool ItemCheckbox( nString label, bool& state );

		/**
		 * ItemVector method
		 * @author : ALVES Quentin
		 * @note : Create an Item Vector.
		 * @param label : Label of the item vector.
		 * @param reset : Reset value.
		 * @param value : Value edited by the vector.
		 **/
		template<typename Type>
		void ItemVector( nString label, Type reset, Type& value );

		/**
		 * ItemVector2 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Vector.
		 * @param label : Label of the item vector.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the vector.
		 * @param value_y : Y Value edited by the vector.
		 **/
		template<typename Type>
		void ItemVector2( nString label, Type reset, Type& value_x, Type& value_y );

		/**
		 * ItemVector3 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Vector.
		 * @param label : Label of the item vector.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the vector.
		 * @param value_y : Y Value edited by the vector.
		 * @param value_z : Z Value edited by the vector.
		 **/
		template<typename Type>
		void ItemVector3( nString label, Type reset, Type& value_x, Type& value_y, Type& value_z );

		/**
		 * ItemVector4 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Vector.
		 * @param label : Label of the item vector.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the vector.
		 * @param value_y : Y Value edited by the vector.
		 * @param value_z : Z Value edited by the vector.
		 * @param value_w : W Value edited by the vector.
		 **/
		template<typename Type>
		void ItemVector4( nString label, Type reset, Type& value_x, Type& value_y, Type& value_z, Type& value_w );

		/**
		 * ItemSlider method
		 * @author : ALVES Quentin
		 * @note : Create an Item Slider.
		 * @param label : Label of the item slider.
		 * @param reset : Reset value.
		 * @param value : Value edited by the slider.
		 **/
		template<typename Type>
		void ItemSlider( nString label, Type min, Type max, Type& value );

		/**
		 * ItemSlider2 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Slider.
		 * @param label : Label of the item slider.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the slider.
		 * @param value_y : Y Value edited by the slider.
		 **/
		template<typename Type>
		void ItemSlider2( nString label, Type min, Type max, Type& value_x, Type& value_y );

		/**
		 * ItemSlider3 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Slider.
		 * @param label : Label of the item slider.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the slider.
		 * @param value_y : Y Value edited by the slider.
		 * @param value_z : Z Value edited by the slider.
		 **/
		template<typename Type>
		void ItemSlider3( nString label, Type min, Type max, Type& value_x, Type& value_y, Type& value_z );

		/**
		 * ItemSlider4 method
		 * @author : ALVES Quentin
		 * @note : Create an Item Slider.
		 * @param label : Label of the item slider.
		 * @param reset : Reset value.
		 * @param value_x : X Value edited by the slider.
		 * @param value_y : Y Value edited by the slider.
		 * @param value_z : Z Value edited by the slider.
		 * @param value_w : W Value edited by the slider.
		 **/
		template<typename Type>
		void ItemSlider4( nString label, Type min, Type max, Type& value_x, Type& value_y, Type& value_z, Type& value_w );

		/**
		 * ItemDropList function
		 * @author : ALVES Quentin
		 * @note : Create a drop list for category, return true when state change.
		 * @param label : Drop list label.
		 * @param state : Drop list state.
		 * @param current_id : Index of the current list element.
		 * @param count : Size of the query element list.
		 * @param list : List of the element.
		 * @return : bool
		 **/
		NUT_API bool ItemDropList( nString label, nUInt& current_id, const nUInt count, nString* list );

		/**
		 * ItemDropList function
		 * @author : ALVES Quentin
		 * @note : Create a drop list for category, return true when state change.
		 * @param label : Drop list label.
		 * @param state : Drop list state.
		 * @param current_id : Index of the current list element.
		 * @param list : List of the element.
		 * @return : bool
		 **/
		NUT_API bool ItemDropList( nString label, nUInt& current_id, const std::vector<nString>& list );

		/**
		 * ItemPicker method
		 * @author : ALVES Quentin
		 * @note : Create a color pîcker for category.
		 * @param label : Color picker label.
		 * @param color : Query color.
		 **/
		NUT_API void ItemPicker( nString label, ImVec4& color );

		/**
		 * ItemPicker method
		 * @author : ALVES Quentin
		 * @note : Create a color pîcker for category.
		 * @param label : Color picker label.
		 * @param color : Query color.
		 **/
		NUT_API void ItemPicker( nString label, ImColor& color );

		/**
		 * Stop method
		 * @author : ALVES Quentin
		 * @note : End and render current ImGui context.
		 **/
		NUT_API void Stop( );

		/**
		 * Cleanup method
		 * @author : ALVES Quentin
		 * @note : Cleanup ImGui.
		 **/
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

		/**
		 * GetTextSize const function
		 * @author : ALVES Quentin
		 * @note : Get the size of a text.
		 * @param text : Query text.
		 * @return : const ImVec2
		 **/
		NUT_API const ImVec2 GetTextSize( const std::string_view& text );

		/**
		 * GetTextSize const function
		 * @author : ALVES Quentin
		 * @note : Get the size of a text.
		 * @template Args : Arguments types.
		 * @param format : Query text.
		 * @param args : Arguments of the text.
		 * @return : const ImVec2
		 **/
		template<typename... Args>
		const ImVec2 GetTextSize( nString format, Args... args );

	};

	#include <Templates/ImGUI.hpp>

#endif
