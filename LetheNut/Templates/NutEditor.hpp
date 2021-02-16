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

#ifndef _IGS_NUT_EDITOR_IMP_HPP_
#define _IGS_NUT_EDITOR_IMP_HPP_

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename... Args>
	void NutEditor::Log( NutLoggerModes mode, nString format, Args... args ) {
		this->logger.Append( mode, format, args... );
	}

	template<typename... Args>
	void NutEditor::Log( NutLoggerModes mode, const std::string& format, Args... args ) {
		this->Log( mode, format.c_str( ), args... );
	}

	template<typename... Args>
	void NutEditor::LogProfile( nString name, NutLoggerModes mode, nString format, Args... args ) {
		this->logger.Append( name, mode, format, args... );
	}

	template<typename... Args>
	void NutEditor::LogProfile( const std::string& name, NutLoggerModes mode, const std::string& format, Args... args ) {
		this->Log( name.c_str( ), mode, format.c_str( ), args... );
	}

	template<typename Type>
	void NutEditor::SetStyle( ) {
		if constexpr ( std::is_base_of<NutStyle, Type>::value ) {
			auto new_style = std::make_shared<Type>( );

			if ( new_style ) {
				if ( this->style )
					this->style.reset( );

				this->style = new_style;
				this->style->OnCreate( );
			}
		}
	}

	template<typename Type, typename... Args>
	Type* NutEditor::Register( NutPlatformLib* importer, Args... args ) {
		if constexpr ( std::is_base_of<NutModule, Type>::value ) {
			auto* module = new Type( importer, args... );

			if ( module ) {
				this->modules.Emplace( module );

				NUT_CAST( module, NutModule )->OnCreate( this );

				return module;
			}
		}

		return nullptr;
	}

	template<typename Type, typename... Args>
	Type* NutEditor::Open( Args... args ) {
		if constexpr ( std::is_base_of<NutWindow, Type>::value ) {
			auto* window = new Type( args... );

			if ( window && window->Open( this->assets.GetContext( ) ) && OpenGL::Initialize( this ) ) {
				this->windows.Emplace( window );

				NUT_CAST( window, NutUIElement )->OnCreateUI( );
				NUT_CAST( window, NutWindow )->OnCreate( this );

				return window;
			} else
				delete window;
		}

		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	//      PUBLIC GET
	///////////////////////////////////////////////////////////////////////////////////////////
	template<typename Type>
	Type* NutEditor::GetLibrary( nString name ) const {
		if constexpr ( std::is_base_of<NutLibrary, Type>::value ) {
			auto* library = this->libraries[ name ];

			if ( dynamic_cast<Type*>( library ) )
				return NUT_CAST( library, Type );
		}

		return nullptr;
	}

	template<typename Type>
	Type* NutEditor::GetModule( nString name ) const {
		if constexpr ( std::is_base_of<NutModule, Type>::value ) {
			auto* library = this->modules[ name ];

			if ( dynamic_cast<Type*>( library ) )
				return NUT_CAST( library, Type );
		}

		return nullptr;
	}

	template<typename Type>
	Type* NutEditor::GetWindow( nString name ) const {
		if constexpr ( std::is_base_of<NutWindow, Type>::value ) {
			auto* window = this->windows[ name ];

			if ( dynamic_cast<Type*>( window ) )
				return NUT_CAST( window, Type );
		}

		return nullptr;
	}

#endif
