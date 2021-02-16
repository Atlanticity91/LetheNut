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

#pragma once

#include <LetheNut/NutDev.hpp>

NCLASS( EditorModule ) final : public NutModule{

public:
	EditorModule( NutPlatformLib* importer );

	~EditorModule( ) = default;

protected:
	/**
	 * OnCreate pure-virtual method
	 * @author : ALVES Quentin
	 * @node : Called once when the module is created.
	 * @param editor : Pointer to current editor.
	 **/
	virtual void OnCreate( NutEditor* editor ) override;

	/**
	 * OnEnable pure-virtual method
	 * @author : ALVES Quentin
	 * @node : Called every time the module is enabled.
	 * @param editor : Pointer to current editor.
	 **/
	virtual void OnEnable( NutEditor* editor ) override;

	/**
	 * OnDisable pure-virtual method
	 * @author : ALVES Quentin
	 * @node : Called every time the module is disable.
	 * @param editor : Pointer to current editor.
	 **/
	virtual void OnDisable( NutEditor* editor ) override;

	/**
	 * OnDestroy pure-virtual method
	 * @author : ALVES Quentin
	 * @node : Called once when the module is destoyed.
	 * @param editor : Pointer to current editor.
	 **/
	virtual void OnDestroy( NutEditor* editor ) override;

	/**
	 * Process pure-virtual method
	 * @author : ALVES Quentin
	 * @node : Called every tick of the editor when the module is enabled.
	 * @param editor : Pointer to current editor.
	 **/
	virtual void Process( NutEditor* editor ) override;

};

NMODULE_CREATE( EditorModule )
