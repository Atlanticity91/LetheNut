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

#include "__pch.hpp"

#include <LetheNut/Framework/Logger/NutLoggerProfile.hpp>
#include <Thirdparty/SpdLog/sinks/basic_file_sink.h>
#include <Thirdparty/SpdLog/sinks/stdout_color_sinks.h>

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
NutLoggerProfile::NutLoggerProfile( nString name, NutLoggerLevels level )
	: NutElement( name )
{ 
#ifdef NDEBUG
	this->handle = spdlog::stdout_color_mt( name );
	this->handle->set_pattern( "[ %T | %^%n%$ ] %v" );
#else
	this->handle = spdlog::basic_logger_mt( name, "Logs/" + std::string(name) + ".txt" );
	this->handle->set_pattern( "[ %T | %^%n%$ ][ %l ] %v" );
#endif

	this->SetLevel( level );
}

void NutLoggerProfile::SetLevel( NutLoggerLevels level ) {
	if ( this->handle ) {
		this->level = level;

		spdlog::level::level_enum value;

		switch ( level ) {
			case NutLoggerLevels::NLL_TRACE: value = spdlog::level::trace; break;
			case NutLoggerLevels::NLL_DEBUG: value = spdlog::level::debug; break;
			case NutLoggerLevels::NLL_INFO: value = spdlog::level::info; break;
			case NutLoggerLevels::NLL_WARN: value = spdlog::level::warn; break;
			case NutLoggerLevels::NLL_ERRR: value = spdlog::level::err; break;
			case NutLoggerLevels::NLL_CRITICAL: value = spdlog::level::critical; break;

			default: value = spdlog::level::off;
		}

		this->handle->set_level( value );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC GET
///////////////////////////////////////////////////////////////////////////////////////////
NutLoggerLevels NutLoggerProfile::GetLevel( ) const { return this->level; }

///////////////////////////////////////////////////////////////////////////////////////////
//      OPERATOR
///////////////////////////////////////////////////////////////////////////////////////////
NutLoggerProfile::operator bool( ) const { return this->handle != nullptr; }
