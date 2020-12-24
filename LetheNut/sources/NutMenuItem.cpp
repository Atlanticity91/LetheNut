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

#include <LetheNut/UI/NutMenuItem.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutMenuItem::NutMenuItem( )
    : NutBasic( "" ) 
{
    this->type.reset( );
    this->type[ 0 ] = 1;
    this->shortcut = nullptr;
    this->checkbox = false;
    this->callback = nullptr;
    this->unmark = nullptr;
}

NutMenuItem::NutMenuItem( nString name, nString shortcut )
    : NutBasic( name ) 
{
    this->type.reset( );
    this->type[ 1 ] = 1;
    this->shortcut = shortcut;
    this->checkbox = false;
    this->callback = nullptr;
    this->unmark = nullptr;
}

NutMenuItem::NutMenuItem( nString name, bool state )
    : NutBasic( name ) 
{
    this->type.reset( );
    this->type[ 2 ] = 1;
    this->shortcut = nullptr;
    this->checkbox = state;
    this->callback = nullptr;
    this->unmark = nullptr;
}

class NutMenuItem* NutMenuItem::SetCallback( NutItemCallback callback ) {
    this->callback = callback;

    return this;
}

class NutMenuItem* NutMenuItem::SetMark( NutItemCallback callback ) {
    this->callback = callback;

    return this;
}

class NutMenuItem* NutMenuItem::SetUnMark( NutItemCallback callback ) {
    this->unmark = callback;

    return this;
}

void NutMenuItem::Process( NutEditor* editor, NutPanel& parent ) {
    if ( this->type[ 1 ] == 1 ) {
        if ( this->callback )
            this->callback( *this, editor, parent );
    } else if ( this->type[ 1 ] == 2 ) {
        if ( this->checkbox )
            this->callback( *this, editor, parent );
        else
            this->unmark( *this, editor, parent );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
bool NutMenuItem::IsSeparator( ) const { return this->type[ 0 ]; }

bool NutMenuItem::IsButton( ) const { return this->type[ 1 ]; }

bool NutMenuItem::IsCheckbox( ) const { return this->type[ 2 ]; }

std::bitset< 8 > NutMenuItem::GetType( ) const { return this->type; }

nString NutMenuItem::GetShortcut( ) const { return this->shortcut; }

bool NutMenuItem::GetState( ) const { return this->checkbox; }

bool& NutMenuItem::GetState( ) { return this->checkbox; }

bool NutMenuItem::HasCallback( ) const { return this->callback; }

NutItemCallback NutMenuItem::Get( ) const { return this->callback; }

NutItemCallback NutMenuItem::GetMark( ) const { return this->callback; }

NutItemCallback NutMenuItem::GetUnMark( ) const { return this->unmark; }
