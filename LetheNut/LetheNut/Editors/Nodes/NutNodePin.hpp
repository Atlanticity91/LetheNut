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

#ifndef _IGS_NUT_NODE_PIN_HPP_
#define _IGS_NUT_NODE_PIN_HPP_

	#include <LetheNut/Utils/NutBasic.hpp>

	#define NPIN( TYPE, NAME, DESCRIPTION ) NutNodePin{ false, TYPE, NAME, DESCRIPTION }
	#define NPIN_ARRAY( TYPE, NAME, DESCRIPTION ) NutNodePin{ true, TYPE, NAME, DESCRIPTION }
	
	enum ENutPinTypes : nUInt {

		EPT_FLOW = 0,
		EPT_STRING,
		EPT_BOOL,
		EPT_INT8,
		EPT_INT16,
		EPT_INT32,
		EPT_INT64,
		EPT_FLOAT32,
		EPT_FLOAT64,
		EPT_VECT2,
		EPT_VECT3,
		EPT_VECT4,
		EPT_MAT2,
		EPT_MAT3,
		EPT_MAT4,
		EPT_CUSTOM,

	};

	struct NutNodePinString {

		char* value;
		nUInt length;

	};

	union NutNodePinData {

		nByte int8;
		nShort int16;
		nInt int32;
		nLong int64;
		float float32;
		double float64;
		NutNodePinString string;

	};

	struct NutNodePin {

		bool is_array;
		bool is_connected;
		nUInt type;
		nString name;
		nString description;
		NutNodePinData data;

	};

	struct NutNodeLinkPin {

		nUInt node_id;
		nUInt pin_id;

	};

	struct NutNodeLink {

		NutNodeLinkPin source;
		NutNodeLinkPin destination;
		ImVec4 color;

	};

#endif
