#pragma once

#include <string>
#include "Data.hpp"

UniverseData*	readLuaUniverse( const std::string& filename );
WorldData*		readLuaWorld( const std::string& filename );
LevelData*		readLuaLevel( const std::string& filename );
