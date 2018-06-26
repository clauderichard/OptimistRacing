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

#include "FileLocator.hpp"

UniverseData* loadUniverseData( const std::string& name )
{
	return readLuaUniverse( "world/" + name + ".lua" );
}

WorldData* loadWorldData( const std::string& name )
{
	return readLuaWorld( "world/" + name + ".lua" );
}

LevelData* loadLevelData( const std::string& name )
{
	return readLuaLevel( "world/" + name + ".lua" );
}