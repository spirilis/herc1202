/*
 * font_5x7.h
 *
 *  Created on: Mar 15, 2012
 *      Author: RG1540
 */

#include <stdint.h>

const uint8_t Herc1202_font_5x7[][6] = {		// basic font
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
	,{0x00, 0x00, 0x5f, 0x00, 0x00, 0x00} // 21 !
	,{0x00, 0x07, 0x00, 0x07, 0x00, 0x00} // 22 "
	,{0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00} // 23 #
	,{0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x00} // 24 $
	,{0x23, 0x13, 0x08, 0x64, 0x62, 0x00} // 25 %
	,{0x36, 0x49, 0x55, 0x22, 0x50, 0x00} // 26 &
	,{0x00, 0x05, 0x03, 0x00, 0x00, 0x00} // 27 '
	,{0x00, 0x1c, 0x22, 0x41, 0x00, 0x00} // 28 (
	,{0x00, 0x41, 0x22, 0x1c, 0x00, 0x00} // 29 )
	,{0x14, 0x08, 0x3e, 0x08, 0x14, 0x00} // 2a *
	,{0x08, 0x08, 0x3e, 0x08, 0x08, 0x00} // 2b +
	,{0x00, 0x50, 0x30, 0x00, 0x00, 0x00} // 2c ,
	,{0x08, 0x08, 0x08, 0x08, 0x08, 0x00} // 2d -
	,{0x00, 0x60, 0x60, 0x00, 0x00, 0x00} // 2e .
	,{0x20, 0x10, 0x08, 0x04, 0x02, 0x00} // 2f /
	,{0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00} // 30 0
	,{0x00, 0x42, 0x7f, 0x40, 0x00, 0x00} // 31 1
	,{0x42, 0x61, 0x51, 0x49, 0x46, 0x00} // 32 2
	,{0x21, 0x41, 0x45, 0x4b, 0x31, 0x00} // 33 3
	,{0x18, 0x14, 0x12, 0x7f, 0x10, 0x00} // 34 4
	,{0x27, 0x45, 0x45, 0x45, 0x39, 0x00} // 35 5
	,{0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00} // 36 6
	,{0x01, 0x71, 0x09, 0x05, 0x03, 0x00} // 37 7
	,{0x36, 0x49, 0x49, 0x49, 0x36, 0x00} // 38 8
	,{0x06, 0x49, 0x49, 0x29, 0x1e, 0x00} // 39 9
	,{0x00, 0x36, 0x36, 0x00, 0x00, 0x00} // 3a :
	,{0x00, 0x56, 0x36, 0x00, 0x00, 0x00} // 3b ;
	,{0x08, 0x14, 0x22, 0x41, 0x00, 0x00} // 3c <
	,{0x14, 0x14, 0x14, 0x14, 0x14, 0x00} // 3d =
	,{0x00, 0x41, 0x22, 0x14, 0x08, 0x00} // 3e >
	,{0x02, 0x01, 0x51, 0x09, 0x06, 0x00} // 3f ?
	,{0x32, 0x49, 0x79, 0x41, 0x3e, 0x00} // 40 @
	,{0x7e, 0x11, 0x11, 0x11, 0x7e, 0x00} // 41 A
	,{0x7f, 0x49, 0x49, 0x49, 0x36, 0x00} // 42 B
	,{0x3e, 0x41, 0x41, 0x41, 0x22, 0x00} // 43 C
	,{0x7f, 0x41, 0x41, 0x22, 0x1c, 0x00} // 44 D
	,{0x7f, 0x49, 0x49, 0x49, 0x41, 0x00} // 45 E
	,{0x7f, 0x09, 0x09, 0x09, 0x01, 0x00} // 46 F
	,{0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00} // 47 G
	,{0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00} // 48 H
	,{0x00, 0x41, 0x7f, 0x41, 0x00, 0x00} // 49 I
	,{0x20, 0x40, 0x41, 0x3f, 0x01, 0x00} // 4a J
	,{0x7f, 0x08, 0x14, 0x22, 0x41, 0x00} // 4b K
	,{0x7f, 0x40, 0x40, 0x40, 0x40, 0x00} // 4c L
	,{0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x00} // 4d M
	,{0x7f, 0x04, 0x08, 0x10, 0x7f, 0x00} // 4e N
	,{0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00} // 4f O
	,{0x7f, 0x09, 0x09, 0x09, 0x06, 0x00} // 50 P
	,{0x3e, 0x41, 0x51, 0x21, 0x5e, 0x00} // 51 Q
	,{0x7f, 0x09, 0x19, 0x29, 0x46, 0x00} // 52 R
	,{0x46, 0x49, 0x49, 0x49, 0x31, 0x00} // 53 S
	,{0x01, 0x01, 0x7f, 0x01, 0x01, 0x00} // 54 T
	,{0x3f, 0x40, 0x40, 0x40, 0x3f, 0x00} // 55 U
	,{0x1f, 0x20, 0x40, 0x20, 0x1f, 0x00} // 56 V
	,{0x3f, 0x40, 0x38, 0x40, 0x3f, 0x00} // 57 W
	,{0x63, 0x14, 0x08, 0x14, 0x63, 0x00} // 58 X
	,{0x07, 0x08, 0x70, 0x08, 0x07, 0x00} // 59 Y
	,{0x61, 0x51, 0x49, 0x45, 0x43, 0x00} // 5a Z
	,{0x00, 0x7f, 0x41, 0x41, 0x00, 0x00} // 5b [
	,{0x02, 0x04, 0x08, 0x10, 0x20, 0x00} // 5c �
	,{0x00, 0x41, 0x41, 0x7f, 0x00, 0x00} // 5d ]
	,{0x04, 0x02, 0x01, 0x02, 0x04, 0x00} // 5e ^
	,{0x40, 0x40, 0x40, 0x40, 0x40, 0x00} // 5f _
	,{0x00, 0x01, 0x02, 0x04, 0x00, 0x00} // 60 `
	,{0x20, 0x54, 0x54, 0x54, 0x78, 0x00} // 61 a
	,{0x7f, 0x48, 0x44, 0x44, 0x38, 0x00} // 62 b
	,{0x38, 0x44, 0x44, 0x44, 0x20, 0x00} // 63 c
	,{0x38, 0x44, 0x44, 0x48, 0x7f, 0x00} // 64 d
	,{0x38, 0x54, 0x54, 0x54, 0x18, 0x00} // 65 e
	,{0x08, 0x7e, 0x09, 0x01, 0x02, 0x00} // 66 f
	,{0x0c, 0x52, 0x52, 0x52, 0x3e, 0x00} // 67 g
	,{0x7f, 0x08, 0x04, 0x04, 0x78, 0x00} // 68 h
	,{0x00, 0x44, 0x7d, 0x40, 0x00, 0x00} // 69 i
	,{0x20, 0x40, 0x44, 0x3d, 0x00, 0x00} // 6a j
	,{0x7f, 0x10, 0x28, 0x44, 0x00, 0x00} // 6b k
	,{0x00, 0x41, 0x7f, 0x40, 0x00, 0x00} // 6c l
	,{0x7c, 0x04, 0x18, 0x04, 0x78, 0x00} // 6d m
	,{0x7c, 0x08, 0x04, 0x04, 0x78, 0x00} // 6e n
	,{0x38, 0x44, 0x44, 0x44, 0x38, 0x00} // 6f o
	,{0x7c, 0x14, 0x14, 0x14, 0x08, 0x00} // 70 p
	,{0x08, 0x14, 0x14, 0x18, 0x7c, 0x00} // 71 q
	,{0x7c, 0x08, 0x04, 0x04, 0x08, 0x00} // 72 r
	,{0x48, 0x54, 0x54, 0x54, 0x20, 0x00} // 73 s
	,{0x04, 0x3f, 0x44, 0x40, 0x20, 0x00} // 74 t
	,{0x3c, 0x40, 0x40, 0x20, 0x7c, 0x00} // 75 u
	,{0x1c, 0x20, 0x40, 0x20, 0x1c, 0x00} // 76 v
	,{0x3c, 0x40, 0x30, 0x40, 0x3c, 0x00} // 77 w
	,{0x44, 0x28, 0x10, 0x28, 0x44, 0x00} // 78 x
	,{0x0c, 0x50, 0x50, 0x50, 0x3c, 0x00} // 79 y
	,{0x44, 0x64, 0x54, 0x4c, 0x44, 0x00} // 7a z
	,{0x00, 0x08, 0x36, 0x41, 0x00, 0x00} // 7b {
	,{0x00, 0x00, 0x7f, 0x00, 0x00, 0x00} // 7c |
	,{0x00, 0x41, 0x36, 0x08, 0x00, 0x00} // 7d }
	,{0x10, 0x08, 0x08, 0x10, 0x08, 0x00} // 7e ~
	,{0x00, 0x06, 0x09, 0x09, 0x06, 0x00} // 7f Deg Symbol
	,{0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0} // 80 Cursor
	,{0x08, 0x18, 0x38, 0x3F, 0x1F, 0x3F} // 81 TI logo - left half
	,{0x44, 0xF6, 0x3C, 0x1C, 0x18, 0x00} // 82 TI logo - right half
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 83
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 84
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 85
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 86
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 87
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 88
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 89
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8A
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8B
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8C
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8D
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8E
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 8F
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 90
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 91
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 92
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 93
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 94
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 95
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 96
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 97
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 98
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 99
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9A
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9B
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9C
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9D
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9E
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9F
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // A9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AD
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // AF
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // B9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BD
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // BF
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // C9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CD
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // CF
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // D9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DD
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // DF
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // E9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // EA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // EB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // EC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // ED
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // EE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // EF
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F0
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F1
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F2
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F3
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F4
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F5
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F6
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F7
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F8
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // F9
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FA
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FB
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FC
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FD
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FE
	,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // FF
};

