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
lev:set_tracksize( 2.0, 2.0, 5, 10 ) -- cellsizex,cellsizey,numcellsx,numcellsy
lev:set_quadspercell( 4, 4 ) -- x,y

lev:set_trackcolours( {
	{'N','N','W','N','N'},
	{'N','N','G','N','N'},
	{'N','N','G','N','N'},
	{'G','W','W','W','R'},
	{'G','W','N','W','R'},
	{'G','W','N','W','R'},
	{'G','W','W','W','R'},
	{'G','W','W','W','R'},
	{'N','N','B','N','N'},
	{'N','N','B','N','N'}
} )

lev:set_trackfs( {
	{
		{0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0.5,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0.5,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
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
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0.5,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0.5,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0.8,0.5,0,0,0,0,0,0,0},
		{0.8,0.5,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}, {
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{2,1,0,0,0,0,0,0,0},
		{2,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}
	}
} )

lev:set_end( 5.0, 20.0, 3.0 )
lev:add_painter( 3.0, 11.0, 1.0, 'R' )
lev:add_painter( 5.0, 13.0, 1.0, 'G' )
lev:add_painter( 7.0, 11.0, 1.0, 'B' )

lev:set_startcolour( 'G' )
lev:set_startposition( 5.0, 1.0, 0.0, 0.0 )
lev:set_startvelocity( 0.0, 0.0, 0.0, 0.0 )


return lev