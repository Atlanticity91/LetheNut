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
 * Copyright (C) 2021 ALVES Quentin.
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

#ifndef _IGS_NUT_ASSET_MANAGER_HPP
#define _IGS_NUT_ASSET_MANAGER_HPP

	#include <LetheNut/Utils/NutList.hpp>

	#include "NutBinary.hpp"
	#include "NutImage.hpp"
	#include "NutJSON.hpp"
	#include "NutSound.hpp"

	class NUT_API NutAssetManager final {

	private:
		nPointer gl_context;
		NutList<NutImage> images;
		NutList<NutSound> sounds;
		NutList<NutJSON> jsons;
		NutList<NutBinary> binaries;

	public:
		NutAssetManager( );

		~NutAssetManager( );

		bool Initialize( );

		bool LoadImageAs( NutEditor* editor, nString alias, nString path );

		inline bool LoadImageAs( NutEditor* editor, const std::string& alias, const std::string& path );

		bool LoadSoundAs( NutEditor* editor, nString alias, nString path );

		inline bool LoadSoundAs( NutEditor* editor, const std::string& alias, const std::string& path );

		bool LoadJSONAs( NutEditor* editor, nString alias, nString path );

		inline bool LoadJSONAs( NutEditor* editor, const std::string& alias, const std::string& path );

		bool LoadBinaryAs( NutEditor* editor, nString alias, nString path );

		inline bool LoadBinaryAs( NutEditor* editor, const std::string& alias, const std::string& path );

		bool WriteJSON( NutEditor* editor, nString alias, nString path );

		inline bool WriteJSON( NutEditor* editor, const std::string& alias, const std::string& path );

		bool WriteBinary( NutEditor* editor, nString alias, nString path );

		inline bool WriteBinary( NutEditor* editor, const std::string& alias, const std::string& path );

	public:
		nPointer GetContext( ) const;

		NutImage* GetImage( nString alias ) const;

		NutSound* GetSound( nString alias ) const;

		NutJSON* GetJSON( nString alias ) const;

		NutBinary* GetBinary( nString alias ) const;

	};

#endif
