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

univ = dat.universe()

-- racer
univ:set_racermasses( 0.2, 0.2, 4.0 ) -- head,body,bottom
univ:set_racersize( 1.0, 0.2, 0.1, 0.2 ) -- bodylength,headradius,bodyradius,bottomradius
univ:set_racerimages( 'logo-creepy2', 'logo-creepy2', 'Mothership', 'Mothership' ) -- hat,head,body,bottom
univ:set_forces( 12, 12, 0.4 ) -- forcex,forcey,torque

-- set the graphics for all spheres
-- (spheres are only used for racer head&bottom)
univ:set_spheredivision( 20, 20 ) -- slices,stacks

univ:set_skyboxsize( 200 )
univ:set_racervelocitymax( 20, 10, 10 ) -- xyz,theta,phi
univ:set_itemsize( 0.3, 0.2, 0.3, 0.2, 0.3 ) -- end,endinner,painter,painterinner,coin

-- set the racer materials
hatm = dat.ematerial()
hatm:set_emission( 0.0, 0.0 )
hatm:set_ambient( 0.2, 0.0 )
hatm:set_diffuse( 0.7, 0.1 )
hatm:set_specular( 0.7, 0.1 )
hatm:set_shininess( 1.0 )
headm = dat.ematerial()
headm:set_emission( 0.0, 0.0 )
headm:set_ambient( 0.2, 0.0 )
headm:set_diffuse( 0.7, 0.1 )
headm:set_specular( 0.7, 0.1 )
headm:set_shininess( 1.0 )
bodym = dat.ematerial()
bodym:set_emission( 0.0, 0.0 )
bodym:set_ambient( 0.2, 0.0 )
bodym:set_diffuse( 0.7, 0.1 )
bodym:set_specular( 0.7, 0.1 )
bodym:set_shininess( 1.0 )
bottomm = dat.ematerial()
bottomm:set_emission( 0.0, 0.0 )
bottomm:set_ambient( 0.2, 0.0 )
bottomm:set_diffuse( 0.7, 0.1 )
bottomm:set_specular( 0.7, 0.1 )
bottomm:set_shininess( 1.0 )
univ:set_racermaterials( hatm, headm, bodym, bottomm ) -- endmaterial,paintermaterial,coinmaterial
univ:set_itemthetadot( 2, 2, 2 )

-- set the item materials
endm = dat.ematerial()
endm:set_emission( 0.0, 0.0 )
endm:set_ambient( 0.2, 0.0 )
endm:set_diffuse( 0.7, 0.1 )
endm:set_specular( 0.7, 0.1 )
endm:set_shininess( 1.0 )
paintm = dat.ematerial()
paintm:set_emission( 0.0, 0.0 )
paintm:set_ambient( 0.2, 0.0 )
paintm:set_diffuse( 0.7, 0.1 )
paintm:set_specular( 0.7, 0.1 )
paintm:set_shininess( 1.0 )
coinm = dat.ematerial()
coinm:set_emission( 0.0, 0.0 )
coinm:set_ambient( 0.2, 0.0 )
coinm:set_diffuse( 0.7, 0.1 )
coinm:set_specular( 0.7, 0.1 )
coinm:set_shininess( 1.0 )
univ:set_itemmaterials( endm, paintm, coinm ) -- endmaterial,paintermaterial,coinmaterial
univ:set_itemthetadot( 2, 2, 2 )

-- set the worlds
--univ:set_worlds( {'ocean'} ) -- ordered list of worlds
univ:set_worlds( {'desert','ocean','forest'} ) -- ordered list of worlds

return univ