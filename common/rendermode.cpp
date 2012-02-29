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
 */

#include "common/rendermode.h"

#include "common/str.h"
#include "common/translation.h"


namespace Common {


const RenderModeDescription g_renderModes[] = {
	// I18N: Hercules is graphics card name
	{ "hercGreen", _s("Hercules Green"), kRenderHercG },
	{ "hercAmber", _s("Hercules Amber"), kRenderHercA },
	{ "cga", "CGA", kRenderCGA },
	{ "ega", "EGA", kRenderEGA },
	{ "vga", "VGA", kRenderVGA },
	{ "amiga", "Amiga", kRenderAmiga },
	{ "fmtowns", "FM-Towns", kRenderFMTowns },
	{ "pc9821", "PC-9821 (256 Colors)", kRenderPC9821 },
	{ "pc9801", "PC-9801 (16 Colors)", kRenderPC9801 },
	{0, 0, kRenderDefault}
};

DECLARE_TRANSLATION_ADDITIONAL_CONTEXT("Hercules Green", "lowres")
DECLARE_TRANSLATION_ADDITIONAL_CONTEXT("Hercules Amber", "lowres")

RenderMode parseRenderMode(const String &str) {
	if (str.empty())
		return kRenderDefault;

	const RenderModeDescription *l = g_renderModes;
	for (; l->code; ++l) {
		if (str.equalsIgnoreCase(l->code))
			return l->id;
	}

	return kRenderDefault;
}

const char *getRenderModeCode(RenderMode id) {
	const RenderModeDescription *l = g_renderModes;
	for (; l->code; ++l) {
		if (l->id == id)
			return l->code;
	}
	return 0;
}

const char *getRenderModeDescription(RenderMode id) {
	const RenderModeDescription *l = g_renderModes;
	for (; l->code; ++l) {
		if (l->id == id)
			return l->description;
	}
	return 0;
}


} // End of namespace Common
