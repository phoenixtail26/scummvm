/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "common/endian.h"

#include "gob/gob.h"
#include "gob/global.h"
#include "gob/inter.h"
#include "gob/game.h"
#include "gob/script.h"
#include "gob/expression.h"

namespace Gob {

#define OPCODEVER Inter_v7
#define OPCODEDRAW(i, x)  _opcodesDraw[i]._OPCODEDRAW(OPCODEVER, x)
#define OPCODEFUNC(i, x)  _opcodesFunc[i]._OPCODEFUNC(OPCODEVER, x)
#define OPCODEGOB(i, x)   _opcodesGob[i]._OPCODEGOB(OPCODEVER, x)

Inter_v7::Inter_v7(GobEngine *vm) : Inter_Playtoons(vm) {
}

void Inter_v7::setupOpcodesDraw() {
	Inter_Playtoons::setupOpcodesDraw();

	OPCODEDRAW(0x0C, o7_draw0x0C);
	OPCODEDRAW(0x0D, o7_loadCursor);
	OPCODEDRAW(0x44, o7_displayWarning);
	OPCODEDRAW(0x45, o7_draw0x45);
	OPCODEDRAW(0x57, o7_draw0x57);
	OPCODEDRAW(0x89, o7_draw0x89);
	OPCODEDRAW(0x8A, o7_draw0x8A);
	OPCODEDRAW(0x8C, o7_getSystemProperty);
	OPCODEDRAW(0x90, o7_loadLBM);
	OPCODEDRAW(0x93, o7_draw0x93);
	OPCODEDRAW(0xA1, o7_getINIValue);
	OPCODEDRAW(0xA2, o7_draw0xA2);
	OPCODEDRAW(0xA4, o7_draw0xA4);
	OPCODEDRAW(0xC4, o7_opendBase);
	OPCODEDRAW(0xC5, o7_draw0xC5);
	OPCODEDRAW(0xC6, o7_draw0xC6);
}

void Inter_v7::setupOpcodesFunc() {
	Inter_Playtoons::setupOpcodesFunc();
}

void Inter_v7::setupOpcodesGob() {
	Inter_Playtoons::setupOpcodesGob();

	OPCODEGOB(420, o7_oemToANSI);
}

void Inter_v7::o7_draw0x0C() {
	WRITE_VAR(17, 0);
}

void Inter_v7::o7_loadCursor() {
	int16 cursorIndex = _vm->_game->_script->readValExpr();

	_vm->_game->_script->evalExpr(0);
	Common::String cursorFile = _vm->_game->_script->getResultStr();

	warning("Addy Stub: Load cursor \"%s\" to %d", cursorFile.c_str(), cursorIndex);
}

void Inter_v7::o7_displayWarning() {
	_vm->_game->_script->evalExpr(0);
	Common::String caption = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String text = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String source = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String msg =  _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String param = _vm->_game->_script->getResultStr();

	warning("%s: %s (%s)", source.c_str(), msg.c_str(), param.c_str());
}

void Inter_v7::o7_draw0x45() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str1 = _vm->_game->_script->getResultStr();

	warning("Addy Stub Draw 0x45: \"%s\", \"%s\"", str0.c_str(), str1.c_str());
}

void Inter_v7::o7_draw0x57() {
	int16 index0 = _vm->_game->_script->readVarIndex();
	int16 index1 = _vm->_game->_script->readVarIndex();

	warning("Addy Stub Draw 0x57: %d, %d", index0, index1);
}

void Inter_v7::o7_draw0x89() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str1 = _vm->_game->_script->getResultStr();

	int16 index0 = _vm->_game->_script->readVarIndex();

	warning("Addy Stub Draw 0x89: \"%s\", \"%s\", %d", str0.c_str(), str1.c_str(), index0);
}

void Inter_v7::o7_draw0x8A() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();

	int16 index0 = _vm->_game->_script->readVarIndex();
	int16 index1 = _vm->_game->_script->readVarIndex();

	warning("Addy Stub Draw 0x8A: \"%s\", %d, %d", str0.c_str(), index0, index1);
}

void Inter_v7::o7_getSystemProperty() {
	_vm->_game->_script->evalExpr(0);

	if (!scumm_stricmp(_vm->_game->_script->getResultStr(), "TotalPhys")) {
		// HACK
		storeValue(1000000);
		return;
	}

	if (!scumm_stricmp(_vm->_game->_script->getResultStr(), "AvailPhys")) {
		// HACK
		storeValue(1000000);
		return;
	}

	if (!scumm_stricmp(_vm->_game->_script->getResultStr(), "TimeGMT")) {
		renewTimeInVars();
		storeValue(0);
		return;
	}

	warning("Inter_v7::o7_getSystemProperty(): Unknown property \"%s\"",
			_vm->_game->_script->getResultStr());
	storeValue(0);
}

void Inter_v7::o7_loadLBM() {
	_vm->_game->_script->evalExpr(0);
	Common::String file = _vm->_game->_script->getResultStr();
	if (!file.contains('.'))
		file += ".LBM";

	int16 spriteIndex = _vm->_game->_script->readValExpr();
	int16 left        = _vm->_game->_script->readValExpr();
	int16 top         = _vm->_game->_script->readValExpr();
	int16 width       = _vm->_game->_script->readValExpr();
	int16 height      = _vm->_game->_script->readValExpr();
	int16 x           = _vm->_game->_script->readValExpr();
	int16 y           = _vm->_game->_script->readValExpr();
	int16 transp      = _vm->_game->_script->readValExpr();

	warning("Addy Stub: Load LBM \"%s\", sprite %d, %dx%d+%d+%d @ %d+%d (%d)",
			file.c_str(), spriteIndex, width, height, left, top, x, y, transp);
}

void Inter_v7::o7_draw0x93() {
	uint32 expr0 = _vm->_game->_script->readValExpr();

	warning("Addy Stub Draw 0x93: %d", expr0);
}

void Inter_v7::o7_getINIValue() {
	_vm->_game->_script->evalExpr(0);
	Common::String file = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String section = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String key = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String def = _vm->_game->_script->getResultStr();

	uint16 type;
	int16 varIndex = _vm->_game->_script->readVarIndex(0, &type);

	warning("Addy Stub: Get INI value, \"%s\":\"%s\":\"%s\" (\"%s\")",
		file.c_str(), section.c_str(), key.c_str(), def.c_str());

	if (type == TYPE_VAR_STR) {
		char *str = GET_VARO_STR(varIndex);

		strncpy(str, def.c_str(), _vm->_global->_inter_animDataSize);
		str[_vm->_global->_inter_animDataSize - 1] = '\0';

	} else if (type == TYPE_IMM_INT8) {

		strcpy(GET_VARO_STR(varIndex), def.c_str());

	} else if (type == TYPE_VAR_INT32) {

		char str[256];

		Common::strlcpy(str, def.c_str(), 256);

		WRITE_VARO_UINT32(varIndex, atoi(str));

	} else if (type == TYPE_VAR_INT16) {

		char str[256];

		Common::strlcpy(str, def.c_str(), 256);

		WRITE_VARO_UINT16(varIndex, atoi(str));
	}

}

void Inter_v7::o7_draw0xA2() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str1 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str2 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str3 = _vm->_game->_script->getResultStr();

	warning("Addy Stub Draw 0xA2: \"%s\", \"%s\", \"%s\", \"%s\"",
			str0.c_str(), str1.c_str(), str2.c_str(), str3.c_str());
}

void Inter_v7::o7_draw0xA4() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();

	int16 expr0 = _vm->_game->_script->readValExpr();
	int16 expr1 = _vm->_game->_script->readValExpr();

	warning("Addy Stub Draw 0xA4: \"%s\", %d, %d", str0.c_str(), expr0, expr1);
}

void Inter_v7::o7_opendBase() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str1 = _vm->_game->_script->getResultStr();

	warning("Addy Stub: Open dBase file \"%s.dbf\" (%s)", str0.c_str(), str1.c_str());
}

void Inter_v7::o7_draw0xC5() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();

	warning("Addy Stub Draw 0xC5: \"%s\"", str0.c_str());
}

void Inter_v7::o7_draw0xC6() {
	_vm->_game->_script->evalExpr(0);
	Common::String str0 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str1 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str2 = _vm->_game->_script->getResultStr();
	_vm->_game->_script->evalExpr(0);
	Common::String str3 = _vm->_game->_script->getResultStr();

	int16 index0 = _vm->_game->_script->readVarIndex();

	warning("Addy Stub Draw 0xC6: \"%s\", \"%s\", \"%s\", \"%s\", %d",
			str0.c_str(), str1.c_str(), str2.c_str(), str3.c_str(), index0);
}

void Inter_v7::storeValue(uint16 index, uint16 type, uint32 value) {
	switch (type) {
	case OP_ARRAY_INT8:
	case TYPE_VAR_INT8:
		WRITE_VARO_UINT8(index, value);
		break;

	case TYPE_VAR_INT16:
	case TYPE_VAR_INT32_AS_INT16:
	case TYPE_ARRAY_INT16:
		WRITE_VARO_UINT16(index, value);
		break;

	default:
		WRITE_VARO_UINT32(index, value);
	}
}

void Inter_v7::storeValue(uint32 value) {
	uint16 type;
	uint16 index = _vm->_game->_script->readVarIndex(0, &type);

	storeValue(index, type, value);
}

void Inter_v7::o7_oemToANSI(OpGobParams &params) {
	_vm->_game->_script->skip(2);
}

} // End of namespace Gob