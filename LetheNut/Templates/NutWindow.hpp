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

#ifndef _IGS_NUT_WINDOW_IMP_HPP_
#define _IGS_NUT_WINDOW_IMP_HPP_

    ///////////////////////////////////////////////////////////////////////////////////////////
    //      PUBLIC
    ///////////////////////////////////////////////////////////////////////////////////////////
    template< typename Type, typename... Args  >
    Type* NutWindow::OpenPopup( NutEditor* editor, Args... args ) {
        auto* popup = new Type( args... );

        if ( popup ) {
            this->popups.emplace_back( popup );

            reinterpret_cast<NutPopup*>( popup )->OnCreate( editor );
        }

        return popup;
    }

    template< typename Type >
    void NutWindow::ClosePopup( ) {
        auto idx = this->popups.size( );

        while ( idx > 0 ) {
            idx -= 1;

            auto* popup = this->popups[ idx ];

            if ( !dynamic_cast<Type*>( popup ) )
                continue;
            else {
                delete popup;

                this->popups.erase( this->popups.begin( ) + idx );

                return;
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    //      PUBLIC GET
    ///////////////////////////////////////////////////////////////////////////////////////////
    template< typename Type >
    Type* NutWindow::GetPopup( ) const {
        for ( auto& popup : this->popups ) {
            if ( !dynamic_cast<Type*>( popup ) )
                continue;
            else
                return reinterpret_cast<Type*>( popup );
        }

        return nullptr;
    }

#endif
