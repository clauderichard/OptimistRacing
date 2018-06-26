/*	Copyright (C) 2012  Claude Richard
 *
 *	Optimist Racing is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Optimist Racing is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include "LuaGame.hpp"
#include "Data.hpp"

class DataTracker
{
public:
	DataTracker( const std::string universeName );
	~DataTracker();
	
	WorldData* loadWorld( int index ); // 1-based index in universe
	LevelData* loadLevel( int index ); // 1-based index in current world

	UniverseData* getUniverse();
	WorldData* getWorld();
	LevelData* getLevel();

	// Where are you?
	bool isLastLevelInWorld();
	bool isLastLevelInUniverse();
	bool isLastWorldInUniverse();

	// Step
	WorldData* loadNextWorld();
	LevelData* loadNextLevel(); // also loads next world if you're on last level in world

private:
	UniverseData* mUniverse;
	WorldData* mWorld;
	LevelData* mLevel;

	int mWorldIndex;
	int mLevelIndex;
};