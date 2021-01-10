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

#ifndef _IGS_NUT_PROPERTIES_HPP_
#define _IGS_NUT_PROPERTIES_HPP_

	#include <LetheNut/UI/NutPanel.hpp>

	typedef bool ( *NutPropertyCondition )( NutEditor*, NutWindow*, NutPanel*, NutContext* );
	typedef void ( *NutPropertyContent )( NutEditor*, NutWindow*, NutPanel*, NutContext* );

	struct NutProperty {

		bool need_context;
		NutHash hash;
		nString label;
		nString description;
		NutPropertyCondition condition;
		NutPropertyContent content;

		NutProperty( bool need_context, nString label, nString description, NutPropertyCondition condition, NutPropertyContent content );

		NutHash GetHash( ) const;

	};

	NUT_PANEL( NutProperties ) {

	private:
		NutList<NutProperty> properties;

	public:
		NutProperties( );

		~NutProperties( ) = default;

		void Register( nString label, NutPropertyContent content );

		void Register( nString label, NutPropertyCondition condition, NutPropertyContent content );

		void Register( nString label, nString description, NutPropertyContent content );

		void Register( nString label, nString description, NutPropertyCondition condition, NutPropertyContent content );

	public:
		template<typename Content>
		void Register( nString label, Content && content );
		
		template<typename Condition, typename Content>
		void Register( nString label, Condition&& condition, Content&& content );
		
		template<typename Content>
		void Register( nString label, nString description, Content&& content );

		template<typename Condition, typename Content>
		void Register( nString label, nString description, Condition&& condition, Content&& content );

	protected:
		virtual void OnCreate( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnProcess( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnRender( NutEditor* editor, NutWindow* parent ) override;

		virtual void OnRenderCategory( NutProperty& property, NutEditor* editor, NutWindow* parent );

	};

	#include <Templates/NutProperties.hpp>

#endif
