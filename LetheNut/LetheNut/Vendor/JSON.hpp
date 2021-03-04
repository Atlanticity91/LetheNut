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

    #include <LetheNut/NutCore.hpp>
    #include <Thirdparty/JSON/NLohmann.hpp>

    /**
     * JSON final class.
     * @author : ALVES Quentin
     * @node : Defined JSON core code.
     **/
    class NUT_API JSON final {

    public:
        using StringArray = std::vector<std::string>;
        using BoolArray = std::vector<bool>;
        using IntArray = std::vector<nInt>;
        using UIntArray = std::vector<nUInt>;
        using FloatArray = std::vector<float>;

    private:
        nlohmann::json data;

    public:
        /**
         * Constructor
         * @author : ALVES Quentin
         **/
        JSON( );

        /**
         * Destructor
         * @author : ALVES Quentin
         **/
        ~JSON( );

        /**
         * Load function
         * @author : ALVES Quentin
         * @note : Load a json file.
         * @param path : Path to the query json file.
         * @return : bool
         **/
        bool Load( nString path );

        /**
         * Load function
         * @author : ALVES Quentin
         * @note : Load a json file.
         * @param path : Path to the query json file.
         * @return : bool
         **/
        bool Load( std::string path );

        /**
         * Write function
         * @author : ALVES Quentin
         * @note : Write a json file.
         * @param path : Path to the query json file.
         * @return : bool
         **/
        bool Write( nString path );

        /**
         * Write function
         * @author : ALVES Quentin
         * @note : Write a json file.
         * @param path : Path to the query json file.
         * @return : bool
         **/
        bool Write( std::string path );

    public:
        /**
         * Append template method
         * @author : ALVES Quentin
         * @note : Append parameter to current JSON object.
         * @template Type : Type of the parameter to add.
         * @param parameter : Name of the query parameter.
         * @param data : Parameter value.
         **/
        template< typename Type >
        void Append( nString parameter, const Type& data );

        /**
         * Append template method
         * @author : ALVES Quentin
         * @note : Append parameter to current JSON object.
         * @template Type : Type of the parameter to add.
         * @param parameter : Name of the query parameter.
         * @param data : Parameter value.
         **/
        template< typename Type >
        inline void Append( nString parameter, const Type&& data );

        /**
         * Foreach template method
         * @author : ALVES Quentin
         * @note : Foreach element of parameter.
         * @template Type : Type of the query parameter.
         * @template Action : Lambda capture.
         * @template Args : Types capture for lambda arguements.
         * @param parameter : Name of the query parameter.
         * @param action : Query lambda.
         * @param args : Arguments values for lambda.
         **/
        template< typename Type, typename Action, typename... Args >
        void Foreach( nString parameter, Action&& action, Args... args );

    private:
        /**
         * InternalForeach template method
         * @author : ALVES Quentin
         * @note : Foreach element of parameter.
         * @template Type : Type of the query parameter.
         * @template Action : Lambda capture.
         * @template Args : Types capture for lambda arguements.
         * @param parameter : Name of the query parameter.
         * @param action : Query lambda.
         * @param args : Arguments values for lambda.
         **/
        template< typename Type, typename Action, typename... Args >
        void InternalForeach( nString parameter, Action&& action, Args... args );

    public:
        /**
         * Cast operator
         * @author : ALVES Quentin
         * @note : Get current json object.
         * @return : nlohmann::json&
         **/
        operator nlohmann::json&();

    public:
        /**
         * Get template const function
         * @author : ALVES Quentin
         * @note : Get a parameter of the current JSON object.
         * @template Type : Type of the query parameter.
         * @param parameter : Name of the query parameter.
         * @return : const Type
         **/
        template< typename Type >
        const Type Get( nString parameter ) const;

    private:
        /**
         * InternalGetArray template const function
         * @author : ALVES Quentin
         * @note : Get an array parameter of the current JSON object.
         * @template Type : Type of the query array parameter.
         * @param parameter : Name of the query array parameter.
         * @return : const Type
         **/
        template< typename Array >
        const Array InternalGetArray( nString parameter ) const;

    };

    #include <Templates/JSON.hpp>

#endif
