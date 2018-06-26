--
--	Copyright (C) 2012  Claude Richard
--
--	Optimist Racing is free software: you can redistribute it and/or modify
--	it under the terms of the GNU General Public License as published by
--	the Free Software Foundation, either version 3 of the License, or
--	(at your option) any later version.
--
--	Optimist Racing is distributed in the hope that it will be useful,
--	but WITHOUT ANY WARRANTY; without even the implied warranty of
--	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--	GNU General Public License for more details.
--
--	You should have received a copy of the GNU General Public License
--	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
--

lev = dat.level()

-- must do this before setting grid-values
lev:set_trackheight( 2.0 )
lev:set_tracksize( 2.0, 2.0, 4, 4 ) -- cellsizex,cellsizey,numcellsx,numcellsy
lev:set_quadspercell( 4, 4 ) -- x,y

lev:set_trackcolours( {
	{'W','N','N','W'},
	{'W','N','N','W'},
	{'W','N','N','W'},
	{'R','W','W','G'}
} )

lev:set_trackfs( {
	{
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0.2,0.15,0,0,0,0,0,0,0},
		{0.2,0.15,0,0,0,0,0,0,0},
		{0.2,0.15,0,0,0,0,0,0,0},
		{0.2,0.15,0,0,0,0,0,0,0},
		{0.2,0.15,0,0,0,0,0,0,0}
	}, {
		{1,0.6,0,0,0,0,0,0,0},
		{1,0.6,0,0,0,0,0,0,0},
		{1,0.6,0,0,0,0,0,0,0},
		{1,0.6,0,0,0,0,0,0,0},
		{1,0.6,0,0,0,0,0,0,0}
	}
} )

lev:set_end( 7.0, 1.0, 1.0 )
lev:add_painter( 1.2, 4.4, 2.0, 'B' )
lev:add_painter( 3.2, 2.4, 1.5, 'G' )

lev:set_startcolour( 'Y' )
lev:set_startposition( 1.0, 0.5, 0.0, 0.0 )
lev:set_startvelocity( 0.0, 1.9, 0.0, 0.0 )


return lev