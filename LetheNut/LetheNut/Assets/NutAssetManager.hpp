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

	/**
	 * NutAssetManager final class
	 * @author : ALVES Quentin
	 * @node : Defined Nut Asset Manager core class.
	 **/
	class NUT_API NutAssetManager final {

	private:
		nPointer gl_context;
		NutList<NutImage> images;
		NutList<NutSound> sounds;
		NutList<NutJSON> jsons;
		NutList<NutBinary> binaries;

	public:
		/**
		 * Constructor
		 * @author : ALVES Quentin
		 **/
		NutAssetManager( );

		/**
		 * Destructor
		 * @author : ALVES Quentin
		 **/
		~NutAssetManager( );

		/**
		 * Initialize function
		 * @author : ALVES Quentin
		 * @note : Initialize current asset manager.
		 * @return : bool
		 **/
		bool Initialize( );

		/**
		 * LoadImageAs function
		 * @author : ALVES Quentin
		 * @note : Load an image with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query image alias.
		 * @param path : Query image path.
		 * @return : bool
		 **/
		bool LoadImageAs( NutEditor* editor, nString alias, nString path );

		/**
		 * LoadImageAs function
		 * @author : ALVES Quentin
		 * @note : Load an image with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query image alias.
		 * @param path : Query image path.
		 * @return : bool
		 **/
		inline bool LoadImageAs( NutEditor* editor, const std::string& alias, const std::string& path );

		/**
		 * LoadSoundAs function
		 * @author : ALVES Quentin
		 * @note : Load a sound with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query sound alias.
		 * @param path : Query sound path.
		 * @return : bool
		 **/
		bool LoadSoundAs( NutEditor* editor, nString alias, nString path );

		/**
		 * LoadSoundAs function
		 * @author : ALVES Quentin
		 * @note : Load a sound with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query sound alias.
		 * @param path : Query sound path.
		 * @return : bool
		 **/
		inline bool LoadSoundAs( NutEditor* editor, const std::string& alias, const std::string& path );

		/**
		 * LoadJSONAs function
		 * @author : ALVES Quentin
		 * @note : Load a JSON with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query JSON alias.
		 * @param path : Query JSON path.
		 * @return : bool
		 **/
		bool LoadJSONAs( NutEditor* editor, nString alias, nString path );

		/**
		 * LoadJSONAs function
		 * @author : ALVES Quentin
		 * @note : Load a JSON with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query JSON alias.
		 * @param path : Query JSON path.
		 * @return : bool
		 **/
		inline bool LoadJSONAs( NutEditor* editor, const std::string& alias, const std::string& path );

		/**
		 * LoadBinaryAs function
		 * @author : ALVES Quentin
		 * @note : Load a binary with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query binary alias.
		 * @param path : Query binary path.
		 * @return : bool
		 **/
		bool LoadBinaryAs( NutEditor* editor, nString alias, nString path );

		/**
		 * LoadBinaryAs function
		 * @author : ALVES Quentin
		 * @note : Load a binary with an alias.
		 * @param editor : Current editor pointer.
		 * @param alias : Query binary alias.
		 * @param path : Query binary path.
		 * @return : bool
		 **/
		inline bool LoadBinaryAs( NutEditor* editor, const std::string& alias, const std::string& path );

		/**
		 * WriteJSON function
		 * @author : ALVES Quentin
		 * @note : Write a JSON.
		 * @param editor : Current editor pointer.
		 * @param alias : Query JSON alias.
		 * @param path : Query JSON path.
		 * @return : bool
		 **/
		bool WriteJSON( NutEditor* editor, nString alias, nString path );

		/**
		 * WriteJSON function
		 * @author : ALVES Quentin
		 * @note : Write a JSON.
		 * @param editor : Current editor pointer.
		 * @param alias : Query JSON alias.
		 * @param path : Query JSON path.
		 * @return : bool
		 **/
		inline bool WriteJSON( NutEditor* editor, const std::string& alias, const std::string& path );

		/**
		 * WriteBinary function
		 * @author : ALVES Quentin
		 * @note : Write a binary.
		 * @param editor : Current editor pointer.
		 * @param alias : Query binary alias.
		 * @param path : Query binary path.
		 * @return : bool
		 **/
		bool WriteBinary( NutEditor* editor, nString alias, nString path );

		/**
		 * WriteBinary function
		 * @author : ALVES Quentin
		 * @note : Write a binary.
		 * @param editor : Current editor pointer.
		 * @param alias : Query binary alias.
		 * @param path : Query binary path.
		 * @return : bool
		 **/
		inline bool WriteBinary( NutEditor* editor, const std::string& alias, const std::string& path );

	public:
		/**
		 * GetContext const function
		 * @author : ALVES Quentin
		 * @note : Get current opengl context use for texture loading.
		 * @return : nPointer
		 **/
		nPointer GetContext( ) const;

		/**
		 * GetImage const function
		 * @author : ALVES Quentin
		 * @note : Get an image.
		 * @param alias : Query image alias.
		 * @return : NutImage*
		 **/
		NutImage* GetImage( nString alias ) const;

		/**
		 * GetSound const function
		 * @author : ALVES Quentin
		 * @note : Get a sound.
		 * @param alias : Query sound alias.
		 * @return : NutSound*
		 **/
		NutSound* GetSound( nString alias ) const;

		/**
		 * GetJSON const function
		 * @author : ALVES Quentin
		 * @note : Get a JSON.
		 * @param alias : Query JSON alias.
		 * @return : NutJSON*
		 **/
		NutJSON* GetJSON( nString alias ) const;

		/**
		 * GetBinary const function
		 * @author : ALVES Quentin
		 * @note : Get a binary.
		 * @param alias : Query binary alias.
		 * @return : NutBinary*
		 **/
		NutBinary* GetBinary( nString alias ) const;

	};

#endif
