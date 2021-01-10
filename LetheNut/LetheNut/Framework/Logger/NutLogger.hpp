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

#ifndef _IGS_NUT_LOGGER_HPP_
#define _IGS_NUT_LOGGER_HPP_

	#include <LetheNut/Utils/NutList.hpp>

	#include "NutLoggerProfile.hpp"

	class NUT_API NutLogger final {

		nString NUT_LOGGER = "LehteNut";

	private:
		NutList<NutLoggerProfile> profiles;

	public:
		NutLogger( );

		~NutLogger( ) = default;

		void CreateProfile( nString name, NutLoggerLevels level );

		void SetLevel( nString profile, NutLoggerLevels level );

	public:
		template<typename... Args>
		void Append( NutLoggerModes mode, nString format, Args... args );

		template<typename... Args>
		void Append( nString profile, NutLoggerModes mode, nString format, Args... args );

	public:
		NutLoggerLevels GetLevel( ) const;

		NutLoggerLevels GetLevel( nString profile ) const;

	};

	#include <Templates/NutLogger.hpp>

#endif
