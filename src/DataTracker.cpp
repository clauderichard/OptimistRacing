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

#include "DataTracker.hpp"
#include <sstream>

#define UNIVERSE_FOLDER "world/"

DataTracker::DataTracker( const std::string universeName )
{
	mUniverse = readLuaUniverse( UNIVERSE_FOLDER + universeName + ".lua" );
	mWorld = NULL;
	mLevel = NULL;
	mWorldIndex = 0;
	mLevelIndex = 0;
}

DataTracker::~DataTracker()
{
	if (mWorld!=NULL) delete mWorld;
	if (mLevel!=NULL) delete mLevel;
}
	
WorldData* DataTracker::loadWorld( int index )
{
	if (mWorld!=NULL) delete mWorld;
	mWorldIndex = index;
	mWorld = readLuaWorld( UNIVERSE_FOLDER + mUniverse->mNamesWorlds[mWorldIndex-1] + ".lua" );
	return mWorld;
}

LevelData* DataTracker::loadLevel( int index )
{
	if (mLevel!=NULL) delete mLevel;
	mLevelIndex = index;
	mLevel = readLuaLevel( UNIVERSE_FOLDER + mWorld->mNamesLevels[index-1] + ".lua" );
	return mLevel;
}

UniverseData* DataTracker::getUniverse()
{
	return mUniverse;
}

WorldData* DataTracker::getWorld()
{
	return mWorld;
}

LevelData* DataTracker::getLevel()
{
	return mLevel;
}

// Where are you?
bool DataTracker::isLastLevelInWorld()
{
	return (mLevelIndex == mWorld->mNamesLevels.size());
}

bool DataTracker::isLastLevelInUniverse()
{
	return (mLevelIndex == mWorld->mNamesLevels.size()) && (mWorldIndex == mUniverse->mNamesWorlds.size());
}

bool DataTracker::isLastWorldInUniverse()
{
	return (mWorldIndex == mUniverse->mNamesWorlds.size());
}

// Step
WorldData* DataTracker::loadNextWorld()
{
	mWorldIndex ++;
	loadWorld( mWorldIndex );
	delete mLevel; mLevel = NULL;
	mLevelIndex = 0;
	return mWorld;
}

LevelData* DataTracker::loadNextLevel()
{
	if (mLevelIndex == mWorld->mNamesLevels.size()) {
		if (mWorldIndex == mUniverse->mNamesWorlds.size()) throw -1;
		loadNextWorld();
	}
	mLevelIndex ++;
	loadLevel( mLevelIndex );
	return mLevel;
}