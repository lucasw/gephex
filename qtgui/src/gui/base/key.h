/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_KEY_H
#define INCLUDED_KEY_H

#include <string>

namespace gui {

  /**
   * Represents a pressed or released key.
   * The key consists of its code and the modifier-mask.
   * The modifier-mask contains information about alt, ctrl and shift.
   * So A, Ctrl-A and Alt-A are different keys, for example.
   */
  class Key
  {
  public:
    /**
     * Constructs a new key from keyCode and modifierMask.
     * @param keyCode the code of the key (see KeyCodes below)
     * @param modifierMask the modifierMask (see ModifierMasks below).
     */
    explicit Key(int keyCode, int modifierMask);

    /**
     * Constructs a new key from a string representation.
     * @param keyName the id of the key. keyIds have the following format:
     *
     *    <keyID>        ::= (<ModifierList>-)?<KeyName>
     *    <ModifierList> ::= (Ctrl)?(Alt)?(Shift)?
     *    <KeyName>      ::= [a-z0-9@°!"§$%&/()=[]{}\^#'`+-*~-_.,:;<>|] |
     *                       F[0-9] | F1[0-2] | Home | End | Insert |
     *                       Backspace | Delete | Tab | Return | Enter |
     *                       Pause | Print | SysReq | Up | Down | Right |
     *                       Left | PageUp | PageDown | (Caps|Scroll|Num)Lock |
     *                       Shift | Control | Meta | Alt
     *
     *    Note: the keyname translation is *not* case sensitive!
     *
     *    So, valid keyIds are: "a" (the same as "A"), "Shift-B", "alt-a",
     *                          "ctrlshift-="
     *
     *    Invalid examples are: "ShiftCtrl-a", "Shift-AKJAKjAKJADKJ"
     *
     * @throw std::runtime_error if the keyName is malformed
     */
    explicit Key(const std::string& keyName);

    /**
     * Returns the keycode of the key.
     */
    int code() const;

    /**
     * Returns the modifier-maks of the key.
     */
    int modifierMask() const;

    bool operator==(const Key& rhs) const;
    bool operator!=(const Key& rhs) const;

    // masks for modifiers as Shift, Ctrl, Alt
    enum ModifierMasks {
      NoModifier    = 0x00000,
      AltModifier   = 0x00001,
      ShiftModifier = 0x00002,
      CtrlModifier  = 0x00004
    };

    enum KeyCodes {
      Key_Escape = 0x1000,		// misc keys
      Key_Tab = 0x1001,
      Key_Backtab = 0x1002, Key_BackTab = Key_Backtab,
      Key_Backspace = 0x1003, Key_BackSpace = Key_Backspace,
      Key_Return = 0x1004,
      Key_Enter = 0x1005,
      Key_Insert = 0x1006,
      Key_Delete = 0x1007,
      Key_Pause = 0x1008,
      Key_Print = 0x1009,
      Key_SysReq = 0x100a,
      Key_Home = 0x1010,		// cursor movement
      Key_End = 0x1011,
      Key_Left = 0x1012,
      Key_Up = 0x1013,
      Key_Right = 0x1014,
      Key_Down = 0x1015,
      Key_Prior = 0x1016, Key_PageUp = Key_Prior,
      Key_Next = 0x1017, Key_PageDown = Key_Next,
      Key_Shift = 0x1020,		// modifiers
      Key_Control = 0x1021,
      Key_Meta = 0x1022,
      Key_Alt = 0x1023,
      Key_CapsLock = 0x1024,
      Key_NumLock = 0x1025,
      Key_ScrollLock = 0x1026,
      Key_F1 = 0x1030,		// function keys
      Key_F2 = 0x1031,
      Key_F3 = 0x1032,
      Key_F4 = 0x1033,
      Key_F5 = 0x1034,
      Key_F6 = 0x1035,
      Key_F7 = 0x1036,
      Key_F8 = 0x1037,
      Key_F9 = 0x1038,
      Key_F10 = 0x1039,
      Key_F11 = 0x103a,
      Key_F12 = 0x103b,
      Key_F13 = 0x103c,
      Key_F14 = 0x103d,
      Key_F15 = 0x103e,
      Key_F16 = 0x103f,
      Key_F17 = 0x1040,
      Key_F18 = 0x1041,
      Key_F19 = 0x1042,
      Key_F20 = 0x1043,
      Key_F21 = 0x1044,
      Key_F22 = 0x1045,
      Key_F23 = 0x1046,
      Key_F24 = 0x1047,
      Key_F25 = 0x1048,		// F25 .. F35 only on X11
      Key_F26 = 0x1049,
      Key_F27 = 0x104a,
      Key_F28 = 0x104b,
      Key_F29 = 0x104c,
      Key_F30 = 0x104d,
      Key_F31 = 0x104e,
      Key_F32 = 0x104f,
      Key_F33 = 0x1050,
      Key_F34 = 0x1051,
      Key_F35 = 0x1052,
      Key_Super_L = 0x1053, 		// extra keys
      Key_Super_R = 0x1054,
      Key_Menu = 0x1055,
      Key_Hyper_L = 0x1056,
      Key_Hyper_R = 0x1057,
      Key_Help = 0x1058,
      Key_Space = 0x20,		// 7 bit printable ASCII
      Key_Any = Key_Space,
      Key_Exclam = 0x21,
      Key_QuoteDbl = 0x22,
      Key_NumberSign = 0x23,
      Key_Dollar = 0x24,
      Key_Percent = 0x25,
      Key_Ampersand = 0x26,
      Key_Apostrophe = 0x27,
      Key_ParenLeft = 0x28,
      Key_ParenRight = 0x29,
      Key_Asterisk = 0x2a,
      Key_Plus = 0x2b,
      Key_Comma = 0x2c,
      Key_Minus = 0x2d,
      Key_Period = 0x2e,
      Key_Slash = 0x2f,
      Key_0 = 0x30,
      Key_1 = 0x31,
      Key_2 = 0x32,
      Key_3 = 0x33,
      Key_4 = 0x34,
      Key_5 = 0x35,
      Key_6 = 0x36,
      Key_7 = 0x37,
      Key_8 = 0x38,
      Key_9 = 0x39,
      Key_Colon = 0x3a,
      Key_Semicolon = 0x3b,
      Key_Less = 0x3c,
      Key_Equal = 0x3d,
      Key_Greater = 0x3e,
      Key_Question = 0x3f,
      Key_At = 0x40,
      Key_A = 0x41,
      Key_B = 0x42,
      Key_C = 0x43,
      Key_D = 0x44,
      Key_E = 0x45,
      Key_F = 0x46,
      Key_G = 0x47,
      Key_H = 0x48,
      Key_I = 0x49,
      Key_J = 0x4a,
      Key_K = 0x4b,
      Key_L = 0x4c,
      Key_M = 0x4d,
      Key_N = 0x4e,
      Key_O = 0x4f,
      Key_P = 0x50,
      Key_Q = 0x51,
      Key_R = 0x52,
      Key_S = 0x53,
      Key_T = 0x54,
      Key_U = 0x55,
      Key_V = 0x56,
      Key_W = 0x57,
      Key_X = 0x58,
      Key_Y = 0x59,
      Key_Z = 0x5a,
      Key_BracketLeft = 0x5b,
      Key_Backslash = 0x5c,
      Key_BracketRight = 0x5d,
      Key_AsciiCircum = 0x5e,
      Key_Underscore = 0x5f,
      Key_QuoteLeft = 0x60,
      Key_BraceLeft = 0x7b,
      Key_Bar = 0x7c,
      Key_BraceRight = 0x7d,
      Key_AsciiTilde = 0x7e,

	// Latin 1 codes adapted from X: keysymdef.h,v 1.21 94/08/28 16:17:06

      Key_nobreakspace = 0x0a0,
      Key_exclamdown = 0x0a1,
      Key_cent = 0x0a2,
      Key_sterling = 0x0a3,
      Key_currency = 0x0a4,
      Key_yen = 0x0a5,
      Key_brokenbar = 0x0a6,
      Key_section = 0x0a7,
      Key_diaeresis = 0x0a8,
      Key_copyright = 0x0a9,
      Key_ordfeminine = 0x0aa,
      Key_guillemotleft = 0x0ab,	// left angle quotation mark
      Key_notsign = 0x0ac,
      Key_hyphen = 0x0ad,
      Key_registered = 0x0ae,
      Key_macron = 0x0af,
      Key_degree = 0x0b0,
      Key_plusminus = 0x0b1,
      Key_twosuperior = 0x0b2,
      Key_threesuperior = 0x0b3,
      Key_acute = 0x0b4,
      Key_mu = 0x0b5,
      Key_paragraph = 0x0b6,
      Key_periodcentered = 0x0b7,
      Key_cedilla = 0x0b8,
      Key_onesuperior = 0x0b9,
      Key_masculine = 0x0ba,
      Key_guillemotright = 0x0bb,	// right angle quotation mark
      Key_onequarter = 0x0bc,
      Key_onehalf = 0x0bd,
      Key_threequarters = 0x0be,
      Key_questiondown = 0x0bf,
      Key_Agrave = 0x0c0,
      Key_Aacute = 0x0c1,
      Key_Acircumflex = 0x0c2,
      Key_Atilde = 0x0c3,
      Key_Adiaeresis = 0x0c4,
      Key_Aring = 0x0c5,
      Key_AE = 0x0c6,
      Key_Ccedilla = 0x0c7,
      Key_Egrave = 0x0c8,
      Key_Eacute = 0x0c9,
      Key_Ecircumflex = 0x0ca,
      Key_Ediaeresis = 0x0cb,
      Key_Igrave = 0x0cc,
      Key_Iacute = 0x0cd,
      Key_Icircumflex = 0x0ce,
      Key_Idiaeresis = 0x0cf,
      Key_ETH = 0x0d0,
      Key_Ntilde = 0x0d1,
      Key_Ograve = 0x0d2,
      Key_Oacute = 0x0d3,
      Key_Ocircumflex = 0x0d4,
      Key_Otilde = 0x0d5,
      Key_Odiaeresis = 0x0d6,
      Key_multiply = 0x0d7,
      Key_Ooblique = 0x0d8,
      Key_Ugrave = 0x0d9,
      Key_Uacute = 0x0da,
      Key_Ucircumflex = 0x0db,
      Key_Udiaeresis = 0x0dc,
      Key_Yacute = 0x0dd,
      Key_THORN = 0x0de,
      Key_ssharp = 0x0df,
      Key_agrave = 0x0e0,
      Key_aacute = 0x0e1,
      Key_acircumflex = 0x0e2,
      Key_atilde = 0x0e3,
      Key_adiaeresis = 0x0e4,
      Key_aring = 0x0e5,
      Key_ae = 0x0e6,
      Key_ccedilla = 0x0e7,
      Key_egrave = 0x0e8,
      Key_eacute = 0x0e9,
      Key_ecircumflex = 0x0ea,
      Key_ediaeresis = 0x0eb,
      Key_igrave = 0x0ec,
      Key_iacute = 0x0ed,
      Key_icircumflex = 0x0ee,
      Key_idiaeresis = 0x0ef,
      Key_eth = 0x0f0,
      Key_ntilde = 0x0f1,
      Key_ograve = 0x0f2,
      Key_oacute = 0x0f3,
      Key_ocircumflex = 0x0f4,
      Key_otilde = 0x0f5,
      Key_odiaeresis = 0x0f6,
      Key_division = 0x0f7,
      Key_oslash = 0x0f8,
      Key_ugrave = 0x0f9,
      Key_uacute = 0x0fa,
      Key_ucircumflex = 0x0fb,
      Key_udiaeresis = 0x0fc,
      Key_yacute = 0x0fd,
      Key_thorn = 0x0fe,
      Key_ydiaeresis = 0x0ff,

      Key_unknown = 0xffff
    };

  private:
    int m_code;
    int m_modifierMask;
  };

}

#endif
