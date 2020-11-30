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

#ifndef _IGS_NUT_VENDOR_JSON_HPP_
#define _IGS_NUT_VENDOR_JSON_HPP_

    #include <LetheNut/Core.hpp>
    #include <Thirdparty/JSON/NLohmann.hpp>

    class NUT_API nJSON final {

    public:
        using StringArray = std::vector<std::string>;
        using BoolArray = std::vector<bool>;
        using IntArray = std::vector<nInt>;
        using UIntArray = std::vector<nUInt>;
        using FloatArray = std::vector<float>;

    private:
        nlohmann::json data;

    public:
        nJSON( );

        ~nJSON( );

        bool Load( nString path );

        bool Load( std::string path );

        bool Write( nString path );

        bool Write( std::string path );

    public:
        template< typename Type >
        void Append( nString parameter, const Type& data );

        template< typename Type >
        inline void Append( nString parameter, const Type&& data );

        template< typename Type, typename Action, typename... Args >
        void Foreach( nString parameter, Action&& action, Args... args );

    private:
        template< typename Type, typename Action, typename... Args >
        void InternalForeach( nString parameter, Action&& action, Args... args );

    public:
        template< typename Type >
        const Type Get( nString parameter ) const;

    private:
        template< typename Array >
        const Array InternalGetArray( nString parameter ) const;

    };
    
    #include <Templates/VendorJSON.hpp>

#endif
