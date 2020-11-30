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

#ifndef _IGS_NUT_POPUP_HPP_
#define _IGS_NUT_POPUP_HPP_

	#include <LetheNut/Vendor/ImGUI.hpp>

	#include "NutPanel.hpp"

	#define NUT_POPUP( NAME, ... ) NUT_CLASS( NAME, NutPopup, __VA_ARGS__ )

	/**
	 * NutPopup class [ NutPanel ]
	 * @author : ALVES Quentin
	 * @note : Defined Nut Popup core class.
	 **/
	class NUT_API NutPopup : public NutPanel {

		friend class NutWindow;

	public:
		static constexpr ImGuiWindowFlags POPUP_DEFAULT_FLAGS =
			ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	protected:
		bool is_open;
		ImGuiWindowFlags flags;
		ImVec2 size;

	private:
		std::vector< class NutPanel* > panels;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current popup.
		 * @param flags : Current popup creation flags.
		 **/
		NutPopup( nString name, ImGuiWindowFlags flags = POPUP_DEFAULT_FLAGS );

		/**
		 * Constructor
		 * @author : ALVES Quentin
		 * @param name : Name of the current popup.
		 * @param width : Width of the popup.
		 * @param height : Height of the popup.
		 * @param flags : Current popup creation flags.
		 **/
		NutPopup( nString name, nUInt width, nUInt height, ImGuiWindowFlags flags = POPUP_DEFAULT_FLAGS );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		virtual ~NutPopup( );

		/**
		 * Enable virtual function
		 * @author : ALVES Quentin
		 * @note : Enable the current panel.
		 * @return : class NutPanel*
		 **/
		virtual class NutPanel* Enable( ) override;

		/**
		 * Disable virtual function
		 * @author : ALVES Quentin
		 * @note : Disable the current panel.
		 * @return : class NutPanel*
		 **/
		virtual class NutPanel* Disable( ) override;

		/**
		 * EnablePanel virtual function
		 * @author : ALVES Quentin
		 * @note : Enable the query panel.
		 * @param name : Name of the query panel.
		 * @return : class NutPopup*
		 **/
		virtual class NutPopup* EnablePanel( nString name );

		/**
		 * DisabePanel virtual function
		 * @author : ALVES Quentin
		 * @note : Disable the query panel.
		 * @param name : Name of the query panel.
		 * @return : class NutPopup*
		 **/
		virtual class NutPopup* DisabePanel( nString name );

		/**
		 * ClosePanel method
		 * @author : ALVES Quentin
		 * @note : Close a panel.
		 * @param name : Name of the query panel.
		 **/
		void ClosePanel( nString name );

	protected:
		/**
		 * OnEditorRender override method
		 * @author : ALVES Quentin
		 * @note : Called once a frame to render ImGUI stuff.
		 * @param editor : Pointer to current editor.
		 **/
		virtual void OnEditorRender( class NutEditor* editor ) override;

	private:
		/**
		 * OnToolProcess method
		 * @author : ALVES Quentin
		 * @note : Process all tools of the current popup.
		 * @param editor : Pointer to current editor.
		 **/
		void OnToolProcess( class NutEditor* editor );

		/**
		 * OnPanelRender method
		 * @author : ALVES Quentin
		 * @note : Render all panels of the current popup.
		 * @param editor : Pointer to current editor.
		 **/
		void OnPanelRender( class NutEditor* editor );

	public:
		/**
		 * OpenPanel template function
		 * @author : ALVES Quentin
		 * @note : Open a dockable panel on the editor.
		 * @template PanelType : Subclass of NutPanel.
		 * @template Args : All type of arguments pass for popup constructor call.
		 * @param editor : Pointer to current editor.
		 * @param panel : Internal use to store the address of the PType panel instance.
		 * @param args : List of arguments for constructor call.
		 * @return : PType*
		 **/
		template< typename Type = class NutPanel, typename... Args >
		Type* OpenPanel( class NutEditor* editor, Args... args );

	public:
		/**
		 * GetIsOpen inline const function
		 * @author : ALVES Quentin
		 * @note : Get if the popup is open.
		 * @return : bool
		 **/
		inline bool GetIsOpen( ) const;

		/**
		 * GetFlags inline const function
		 * @author : ALVES Quentin
		 * @note : Get ImGui window flags of the current popup.
		 * @return : ImGuiWindowFlags
		 **/
		 inline ImGuiWindowFlags GetFlags( ) const;
	
	public:
		/**
		 * GetPanel const function
		 * @author : ALVES Quentin
		 * @note : Get a panel from the editor by it's name.
		 * @param name : Name of the query panel.
		 * @return : class NutPanel*
		 **/
		template< typename Type = class NutPanel >
		Type* GetPanel( nString name ) const;

	};

	#include <Templates/NutPopup.hpp>

#endif
