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

w = dat.world()

trackm = dat.ematerial()
trackm:set_emission( 0.0, 0.0 )
trackm:set_ambient( 0.2, 0.0 )
trackm:set_diffuse( 0.7, 0.1 )
trackm:set_specular( 0.7, 0.1 )
trackm:set_shininess( 1.0 )

-- racer
w:set_gravity( 2.0 )
w:set_skyboximage( 'SkyBox-Clouds-Heavy-Early' )
w:set_terrainimage( 'watertex', 5.0, 5.0, 0.5, 0.2 )
w:set_trackimage( 'TexturedMetal', 3.0, 3.0 )
w:set_trackmaterial( trackm )
w:set_menuimage( 'ocean-menu' )
w:set_story( 'bkgd5', 'On to the ocean, what what yo dawg!!' )
w:set_music( 'KirbyStyleLaser.ogg', 'KirbyStyleLaser.ogg' )

w:set_levels( { 'ocean-1', 'ocean-2', 'ocean-3' } )
w:set_price( 0 )

return w