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

#include <LetheNut/Core.hpp>

///////////////////////////////////////////////////////////////////////////////////////////
//      INTERNAL
///////////////////////////////////////////////////////////////////////////////////////////
typedef nUInt nDigest[ 4 ];
typedef unsigned ( *DgstFctn )( nUInt* a );

union WBunion {
    
    nUInt w;
    unsigned char b[ 4 ];

};

nUInt f0( nUInt* abcd ) { return ( abcd[ 1 ] & abcd[ 2 ] ) | ( ~abcd[ 1 ] & abcd[ 3 ] ); }

nUInt f1( nUInt* abcd ) { return ( abcd[ 3 ] & abcd[ 1 ] ) | ( ~abcd[ 3 ] & abcd[ 2 ] ); }

nUInt f2( nUInt* abcd ) { return  abcd[ 1 ] ^ abcd[ 2 ] ^ abcd[ 3 ]; }

nUInt f3( nUInt* abcd ) { return abcd[ 2 ] ^ ( abcd[ 1 ] | ~abcd[ 3 ] ); }

nUInt* calcKs( nUInt* k ) {
    double pwr = pow( 2, 32 );
	double s = 0.0;

    for ( nInt i = 0; i < 64; i++ ) {
		s = fabs( sin( 1 + i ) );

        k[ i ] = (nUInt)( s * pwr );
    }

    return k;
}

nUInt rol( nUInt v, nShort amt ) {
	nUInt  msk1 = ( 1 << amt ) - 1;

	return ( ( v >> ( 32 - amt ) ) & msk1 ) | ( ( v << amt ) & ~msk1 );
}

///////////////////////////////////////////////////////////////////////////////////////////
//      PUBLIC
///////////////////////////////////////////////////////////////////////////////////////////
void nHelper::Copy( nString source, char* destination, nUInt size ) {
#ifdef _WIN64
    strcpy_s( destination, size, source );
#else
    strcpy( destination, source );
#endif
}

bool nHelper::GetIsValid( nString text ) { return text && strlen( text ) > 0; }

NutHash nHelper::Hash_MD5( nString text ) {
    static nDigest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
    static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22 };
    static short rot1[] = { 5, 9,14,20 };
    static short rot2[] = { 4,11,16,23 };
    static short rot3[] = { 6,10,15,21 };
    static short* rots[] = { rot0, rot1, rot2, rot3 };
    static nUInt kspace[ 64 ];
    static nUInt* k;

    static nDigest h;
    nDigest abcd;
    DgstFctn fctn;
    short m, o, g;
    nUInt f;
    short* rotn;
    union {
        unsigned w[ 16 ];
        char     b[ 64 ];
    }mm;
    nInt os = 0;
    nInt grp, grps, q, p;
    nUByte* msg2;

    if ( k == NULL ) k = calcKs( kspace );

    for ( q = 0; q < 4; q++ ) h[ q ] = h0[ q ];   // initialize

    {
        nInt text_len = (nInt)strlen( text );
        grps = 1 + ( text_len + 8 ) / 64;
        msg2 = (nUByte*)malloc( 64 * grps );
        memcpy( msg2, text, text_len );
        msg2[ text_len ] = (nUByte)0x80;
        q = text_len + 1;
        while ( q < 64 * grps ) { msg2[ q ] = 0; q++; } {
            WBunion u;
            u.w = 8 * text_len;
            q -= 8;

            memcpy( msg2 + q, &u.w, 4 );
        }
    }

    for ( grp = 0; grp < grps; grp++ ) {
        memcpy( mm.b, msg2 + os, 64 );
        for ( q = 0; q < 4; q++ ) abcd[ q ] = h[ q ];

        for ( p = 0; p < 4; p++ ) {
            fctn = ff[ p ];
            rotn = rots[ p ];
            m = M[ p ]; o = O[ p ];

            for ( q = 0; q < 16; q++ ) {
                g = ( m * q + o ) % 16;
                f = abcd[ 1 ] + rol( abcd[ 0 ] + fctn( abcd ) + k[ q + 16 * p ] + mm.w[ g ], rotn[ q % 4 ] );

                abcd[ 0 ] = abcd[ 3 ];
                abcd[ 3 ] = abcd[ 2 ];
                abcd[ 2 ] = abcd[ 1 ];
                abcd[ 1 ] = f;
            }
        }

        for ( p = 0; p < 4; p++ )
            h[ p ] += abcd[ p ];

        os += 64;
    }

    if ( msg2 )
        free( msg2 );

    return h[ 0 ];
}

void nHelper::ToDeg( float& radians ) { radians *= nHelper::RAD2DEG; }

void nHelper::ToRad( float& degree ) { degree *= nHelper::DEG2RAD; }

nTimePoint nHelper::GetTime( ) {
    return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );
}
