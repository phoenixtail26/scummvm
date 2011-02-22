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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm-misc.svn.sourceforge.net/svnroot/scummvm-misc/trunk/engines/tsage/tsage.cpp $
 * $Id: tsage.cpp 211 2011-02-06 06:59:31Z dreammaster $
 *
 */

#include "common/config-manager.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/system.h"
#include "common/savefile.h"
#include "engines/util.h"

#include "tsage/tsage.h"
#include "tsage/core.h"
#include "tsage/dialogs.h"
#include "tsage/events.h"
#include "tsage/resources.h"
#include "tsage/globals.h"

namespace tSage {

TSageEngine *_vm = NULL;

TSageEngine::TSageEngine(OSystem *system, const ADGameDescription *gameDesc): Engine(system),
		_gameDescription(gameDesc) {
	_vm = this;
	DebugMan.addDebugChannel(kRingDebugScripts, "scripts", "Scripts debugging");
	_debugger = new Debugger();
	_dataManager = NULL;
}

Common::Error TSageEngine::init() {
	initGraphics(SCREEN_WIDTH, SCREEN_HEIGHT, false);

	return Common::kNoError;
}

TSageEngine::~TSageEngine() {
	// Remove all of our debug levels here
	DebugMan.clearAllDebugChannels();
	delete _debugger;
	delete _dataManager;
	delete _tSageManager;
}

bool TSageEngine::hasFeature(EngineFeature f) const {
	return
		(f == kSupportsRTL) ||
		(f == kSupportsLoadingDuringRuntime) ||
		(f == kSupportsSavingDuringRuntime);
}

void TSageEngine::initialise() {
	_tSageManager = new RlbManager(_memoryManager, "tsage.rlb");
	_dataManager = new RlbManager(_memoryManager, "ring.rlb");
}

Common::Error TSageEngine::run() {
	// Basic initialisation
	initialise();
	_saver = new Saver();
	_globals = new Globals();
	_globals->gfxManager().setDefaults();

	initialise();

	_globals->_events.showCursor();

	_globals->_sceneHandler.registerHandler();
	_globals->_game.execute();

	delete _globals;
	delete _saver;
	return Common::kNoError;
}

/**
 * Returns true if it is currently okay to restore a game
 */
bool TSageEngine::canLoadGameStateCurrently() {
	return _globals->getFlag(50) == 0;
}

/**
 * Returns true if it is currently okay to save the game
 */
bool TSageEngine::canSaveGameStateCurrently() {
	return _globals->getFlag(50) == 0;
}

/**
 * Load the savegame at the specified slot index
 */
Common::Error TSageEngine::loadGameState(int slot) {
	return _saver->restore(slot);
}

/**
 * Save the game to the given slot index, and with the given name
 */
Common::Error TSageEngine::saveGameState(int slot, const char *desc) {
	return _saver->save(slot, desc);
}

/**
 * Support method that generates a savegame name
 * @param slot		Slot number
 */
Common::String TSageEngine::generateSaveName(int slot) {
	return Common::String::format("%s.%03d", _targetName.c_str(), slot);
}

} // End of namespace tSage
