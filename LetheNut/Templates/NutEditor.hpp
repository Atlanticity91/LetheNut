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
    template< typename Type, typename... Args >
    Type* NutEditor::Register( Args... args ) {
        if constexpr ( std::is_base_of<NutModule, Type>::value ) {
            auto* module = new Type( args... );

            if ( module ) {
                this->modules.emplace_back( module );

                auto md = reinterpret_cast<NutModule*>( module );
                md->OnCreate( this );
                md->Initialize( this );
            }

            return module;
        }

        return nullptr;
    }
    
    template< typename Type, typename... Args >
    Type* NutEditor::Create( Args... args ) {
        if constexpr ( std::is_base_of<NutWindow, Type>::value ) {
            auto* window = new Type( args... );

            if ( window ) {
                this->windows.emplace_back( window );

                reinterpret_cast<NutWindow*>( window )->OnCreate( this );
            }

            return window;
        }

        return nullptr;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    //      PUBLIC GET 
    ///////////////////////////////////////////////////////////////////////////////////////////
    template< typename Type >
    Type* NutEditor::GetTool( nString name ) const {
        if constexpr ( std::is_base_of<NutTool, Type>::value )
            return this->GetPanel<Type>( name );

        return nullptr;
    }

    template< typename Type >
    Type* NutEditor::GetModule( nString name ) const {
        if constexpr ( std::is_base_of<NutModule, Type>::value ) {
            if ( nHelper::GetIsValid( name ) ) {
                for ( auto& module : this->modules ) {
                    if ( std::strcmp( name, module->GetName( ) ) != 0 || !dynamic_cast<Type*>( module ) )
                        continue;
                    else
                        return reinterpret_cast<Type*>( module );
                }
            }
        }

        return nullptr;
    }

    template< typename Type >
    Type* NutEditor::GetWindow( nString name ) const {
        if constexpr ( std::is_base_of<NutWindow, Type>::value ) {
            if ( nHelper::GetIsValid( name ) ) {
                for ( auto& window : this->windows ) {
                    if ( std::strcmp( name, window->GetName( ) ) != 0 || !dynamic_cast<Type*>( window ) )
                        continue;
                    else
                        return reinterpret_cast<Type*>( window );
                }
            }
        }

        return nullptr;
    }

#endif
