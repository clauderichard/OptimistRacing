#include "LuaGame.hpp"
#include "LuaGeneral.hpp"

struct dat_universe_ud {
	UniverseData* mData;
};

struct dat_world_ud {
	WorldData* mData;
};

struct dat_level_ud {
	LevelData* mData;
};

struct dat_ematerial_ud {
	ElectricMaterialData* mData;
};

extern "C"
int dat_universe_cmd(lua_State* L)
{ 
	dat_universe_ud* data = (dat_universe_ud*)lua_newuserdata(L, sizeof(dat_universe_ud));
	data->mData = NULL;
	data->mData = new UniverseData();
	luaL_getmetatable(L, "dat.universe");
	lua_setmetatable(L, -2);
	return 1;
}

extern "C"
int dat_world_cmd(lua_State* L)
{ 
	dat_world_ud* data = (dat_world_ud*)lua_newuserdata(L, sizeof(dat_world_ud));
	data->mData = NULL;
	data->mData = new WorldData();
	luaL_getmetatable(L, "dat.world");
	lua_setmetatable(L, -2);
	return 1;
}

extern "C"
int dat_level_cmd(lua_State* L)
{ 
	dat_level_ud* data = (dat_level_ud*)lua_newuserdata(L, sizeof(dat_level_ud));
	data->mData = NULL;
	data->mData = new LevelData();
	luaL_getmetatable(L, "dat.level");
	lua_setmetatable(L, -2);
	return 1;
}

extern "C"
int dat_ematerial_cmd(lua_State* L)
{ 
	dat_ematerial_ud* data = (dat_ematerial_ud*)lua_newuserdata(L, sizeof(dat_ematerial_ud));
	data->mData = NULL;
	data->mData = new ElectricMaterialData();
	luaL_getmetatable(L, "dat.ematerial");
	lua_setmetatable(L, -2);
	return 1;
}

extern "C"
int dat_universe_destroy_cmd( lua_State* L )
{
	// Don't delete mData from dat_universe_ud
	// since we will still use the UniverseData object
	// after destroying the Lua stuff.
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData = NULL;
	return 0;
};

extern "C"
int dat_world_destroy_cmd( lua_State* L )
{
	// Don't delete mData from dat_universe_ud
	// since we will still use the UniverseData object
	// after destroying the Lua stuff.
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData = NULL;
	return 0;
};

extern "C"
int dat_level_destroy_cmd( lua_State* L )
{
	// Don't delete mData from dat_universe_ud
	// since we will still use the UniverseData object
	// after destroying the Lua stuff.
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData = NULL;
	return 0;
};

extern "C"
int dat_ematerial_destroy_cmd( lua_State* L )
{
	// Don't delete mData from dat_universe_ud
	// since we will still use the UniverseData object
	// after destroying the Lua stuff.
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData = NULL;
	return 0;
};


extern "C"
int dat_universe_set_racermasses_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mMassHead = luaL_checknumber(L, 2);
	selfdata->mData->mMassBody = luaL_checknumber(L, 3);
	selfdata->mData->mMassBottom = luaL_checknumber(L, 4);
	return 0;
};

extern "C"
int dat_universe_set_racersize_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mLengthBody = luaL_checknumber(L, 2);
	selfdata->mData->mRadiusHead = luaL_checknumber(L, 3);
	selfdata->mData->mRadiusBody = luaL_checknumber(L, 4);
	selfdata->mData->mRadiusBottom = luaL_checknumber(L, 5);
	return 0;
};

extern "C"
int dat_universe_set_racerimages_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mImageHat = luaL_checkstring(L, 2);
	selfdata->mData->mImageHead = luaL_checkstring(L, 3);
	selfdata->mData->mImageBody = luaL_checkstring(L, 4);
	selfdata->mData->mImageBottom = luaL_checkstring(L, 5);
	return 0;
};

extern "C"
int dat_universe_set_spheredivision_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mSphereStacks = floor(luaL_checknumber(L, 2));
	selfdata->mData->mSphereSlices = floor(luaL_checknumber(L, 3));
	return 0;
};

extern "C"
int dat_universe_set_worlds_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	luaL_checktype(L, 2, LUA_TTABLE);
	int nWorlds = luaL_getn( L, 2 );
	for (int i=1; i<=nWorlds; i++) {
		lua_rawgeti(L, 2, i);
		selfdata->mData->mNamesWorlds.push_back( luaL_checkstring(L, -1) );
		lua_pop(L, 1);
	};
	return 0;
};

extern "C"
int dat_universe_set_skyboxsize_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mSizeSkybox = luaL_checknumber(L, 2);
	return 0;
};

extern "C"
int dat_universe_set_racervelocitymax_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mXYZDotMax = luaL_checknumber(L, 2);
	selfdata->mData->mThetaDotMax = luaL_checknumber(L, 3);
	selfdata->mData->mPhiDotMax = luaL_checknumber(L, 4);
	return 0;
};

extern "C"
int dat_universe_set_forces_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mForceMultiplierRight = luaL_checknumber(L, 2);
	selfdata->mData->mForceMultiplierUp = luaL_checknumber(L, 3);
	selfdata->mData->mTorqueMultiplier = luaL_checknumber(L, 4);
	return 0;
};

extern "C"
int dat_universe_set_itemsize_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	selfdata->mData->mRadiusEnd = luaL_checknumber(L, 2);
	selfdata->mData->mRadiusEndInner = luaL_checknumber(L, 3);
	selfdata->mData->mRadiusPainter = luaL_checknumber(L, 4);
	selfdata->mData->mRadiusPainterInner = luaL_checknumber(L, 5);
	selfdata->mData->mRadiusCoin = luaL_checknumber(L, 6);
	return 0;
};

extern "C"
int dat_universe_set_itemmaterials_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");

	dat_ematerial_ud* matdata1 = (dat_ematerial_ud*)luaL_checkudata(L, 2, "dat.ematerial");
	luaL_argcheck(L, matdata1 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialEnd = matdata1->mData;

	dat_ematerial_ud* matdata2 = (dat_ematerial_ud*)luaL_checkudata(L, 3, "dat.ematerial");
	luaL_argcheck(L, matdata2 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialPainter = matdata2->mData;

	dat_ematerial_ud* matdata3 = (dat_ematerial_ud*)luaL_checkudata(L, 4, "dat.ematerial");
	luaL_argcheck(L, matdata3 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialCoin = matdata3->mData;
	return 0;
};

extern "C"
int dat_universe_set_racermaterials_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");

	dat_ematerial_ud* matdata1 = (dat_ematerial_ud*)luaL_checkudata(L, 2, "dat.ematerial");
	luaL_argcheck(L, matdata1 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialHat = matdata1->mData;

	dat_ematerial_ud* matdata2 = (dat_ematerial_ud*)luaL_checkudata(L, 3, "dat.ematerial");
	luaL_argcheck(L, matdata2 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialHead = matdata2->mData;

	dat_ematerial_ud* matdata3 = (dat_ematerial_ud*)luaL_checkudata(L, 4, "dat.ematerial");
	luaL_argcheck(L, matdata3 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialBody = matdata3->mData;

	dat_ematerial_ud* matdata4 = (dat_ematerial_ud*)luaL_checkudata(L, 5, "dat.ematerial");
	luaL_argcheck(L, matdata4 != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialBottom = matdata4->mData;
	return 0;
};

extern "C"
int dat_universe_set_itemthetadot_cmd( lua_State* L )
{
	dat_universe_ud* selfdata = (dat_universe_ud*)luaL_checkudata(L, 1, "dat.universe");
	luaL_argcheck(L, selfdata != 0, 1, "Universe expected");
	
	selfdata->mData->mThetaDotEnd = luaL_checknumber( L, 2 );
	selfdata->mData->mThetaDotPainter = luaL_checknumber( L, 3 );
	selfdata->mData->mThetaDotCoin = luaL_checknumber( L, 4 );
	return 0;
};


extern "C"
int dat_world_set_gravity_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mGravity = luaL_checknumber(L, 2);
	return 0;
};

extern "C"
int dat_world_set_skyboximage_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mImageSkybox = luaL_checkstring(L, 2);
	return 0;
};

extern "C"
int dat_world_set_terrainimage_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mImageTerrain = luaL_checkstring(L, 2);
	selfdata->mData->mSizeTerrainX = luaL_checknumber(L, 3);
	selfdata->mData->mSizeTerrainY = luaL_checknumber(L, 4);
	selfdata->mData->mVelocityTerrainX = luaL_checknumber(L, 5);
	selfdata->mData->mVelocityTerrainY = luaL_checknumber(L, 6);
	return 0;
};

extern "C"
int dat_world_set_trackimage_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mImageTrack = luaL_checkstring(L, 2);
	selfdata->mData->mSizeImageTrackX = luaL_checknumber(L, 3);
	selfdata->mData->mSizeImageTrackY = luaL_checknumber(L, 4);
	return 0;
};

extern "C"
int dat_world_set_menuimage_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mImageMenu = luaL_checkstring(L, 2);
	return 0;
};

extern "C"
int dat_world_set_story_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mImageStory = luaL_checkstring(L, 2);
	selfdata->mData->mTextStory = luaL_checkstring(L, 3);
	return 0;
};

extern "C"
int dat_world_set_music_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mMusicNormal = luaL_checkstring(L, 2);
	selfdata->mData->mMusicChallenge = luaL_checkstring(L, 3);
	return 0;
};

extern "C"
int dat_world_set_levels_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	luaL_checktype(L, 2, LUA_TTABLE);
	int nLevels = luaL_getn( L, 2 );
	for (int i=1; i<=nLevels; i++) {
		lua_rawgeti(L, 2, i);
		selfdata->mData->mNamesLevels.push_back( luaL_checkstring(L, -1) );
		lua_pop(L, 1);
	};
	return 0;
};

extern "C"
int dat_world_set_trackmaterial_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	dat_ematerial_ud* matdata = (dat_ematerial_ud*)luaL_checkudata(L, 2, "dat.ematerial");
	luaL_argcheck(L, matdata != 0, 1, "Ematerial expected");
	selfdata->mData->mMaterialTrack = matdata->mData;
	return 0;
};

extern "C"
int dat_world_set_price_cmd( lua_State* L )
{
	dat_world_ud* selfdata = (dat_world_ud*)luaL_checkudata(L, 1, "dat.world");
	luaL_argcheck(L, selfdata != 0, 1, "World expected");
	selfdata->mData->mNumCoinsRequired = floor(luaL_checknumber(L, 2));
	return 0;
};


extern "C"
int dat_level_set_trackheight_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mFloorHeight = luaL_checknumber(L, 2);
	return 0;
};

extern "C"
int dat_level_set_tracksize_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mFloorBezierHX = luaL_checknumber(L, 2);
	selfdata->mData->mFloorBezierHY = luaL_checknumber(L, 3);
	selfdata->mData->mFloorBezierNumCellsX = luaL_checknumber(L, 4);
	selfdata->mData->mFloorBezierNumCellsY = luaL_checknumber(L, 5);

	// initialize the arrays
	if ( selfdata->mData->mFloorBezierFs!=NULL ) {
		delete selfdata->mData->mFloorBezierFs;
		delete selfdata->mData->mFloorColours;
	}
	selfdata->mData->mFloorBezierFs = new MatrixMxN*[
		(selfdata->mData->mFloorBezierNumCellsX+1) * (selfdata->mData->mFloorBezierNumCellsY+1) ];
	for (int i=0; i<(selfdata->mData->mFloorBezierNumCellsX+1) * (selfdata->mData->mFloorBezierNumCellsY+1); i++) {
		selfdata->mData->mFloorBezierFs[i] = new MatrixMxN( 3, 3 );
	}
	selfdata->mData->mFloorColours = new E_ELECTRICCOLOUR[
		selfdata->mData->mFloorBezierNumCellsX * selfdata->mData->mFloorBezierNumCellsY ];
	for (int i=0; i<selfdata->mData->mFloorBezierNumCellsX * selfdata->mData->mFloorBezierNumCellsY; i++) {
		selfdata->mData->mFloorColours[i] = ELECTRICCOLOUR_BLACK;
	}
	return 0;
};

extern "C"
int dat_level_set_quadspercell_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mQuadsPerCellX = floor(luaL_checknumber(L, 2));
	selfdata->mData->mQuadsPerCellY = floor(luaL_checknumber(L, 3));
	return 0;
};

extern "C"
int dat_level_set_trackcolours_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");

	luaL_checktype(L, 2, LUA_TTABLE);
	luaL_argcheck(L, luaL_getn(L, 2) == selfdata->mData->mFloorBezierNumCellsY, 2, "NumcellsY must match colour-grid");
	for (int i=1; i<=selfdata->mData->mFloorBezierNumCellsY; i++) {
		lua_rawgeti(L, 2, i);
		luaL_checktype(L, -1, LUA_TTABLE);
		luaL_argcheck(L, luaL_getn(L, -1) == selfdata->mData->mFloorBezierNumCellsX, -1, "NumcellsX must match colour-grid");
		for (int j=1; j<=selfdata->mData->mFloorBezierNumCellsX; j++) {
			lua_rawgeti(L, -1, j);
			selfdata->mData->mFloorColours[(i-1)*selfdata->mData->mFloorBezierNumCellsX+j-1] =
				electricColourFromChar( luaL_checkstring(L, -1)[0] );
			lua_pop(L, 1);
		};
		lua_pop(L, 1);
	};
	return 0;
};

extern "C"
int dat_level_set_trackFs_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");

	luaL_checktype(L, 2, LUA_TTABLE);
	luaL_argcheck(L, luaL_getn(L, 2) == selfdata->mData->mFloorBezierNumCellsY+1, 2, "NumcellsY must match F-grid");
	for (int i=1; i<=selfdata->mData->mFloorBezierNumCellsY+1; i++) {
		lua_rawgeti(L, 2, i);
		luaL_checktype(L, -1, LUA_TTABLE);
		luaL_argcheck(L, luaL_getn(L, -1) == selfdata->mData->mFloorBezierNumCellsX+1, -1, "NumcellsX must match F-grid");
		for (int j=1; j<=selfdata->mData->mFloorBezierNumCellsX+1; j++) {
			lua_rawgeti(L, -1, j);
			luaL_checktype(L, -1, LUA_TTABLE);
			luaL_argcheck(L, luaL_getn(L, -1) == 9, -2, "Each F must have 9 entries");
			double ds[9];
			for (int k=1; k<=9; k++) {
				lua_rawgeti(L, -1, k);
				ds[k-1] = luaL_checknumber(L, -1);
				if (k==1) ds[0] += selfdata->mData->mFloorHeight;
				lua_pop(L, 1);
			}
			delete selfdata->mData->mFloorBezierFs[(i-1)*(selfdata->mData->mFloorBezierNumCellsX+1)+j-1];
			selfdata->mData->mFloorBezierFs[(i-1)*(selfdata->mData->mFloorBezierNumCellsX+1)+j-1] = new MatrixMxN( 3, 3, ds );
			lua_pop(L, 1);
		};
		lua_pop(L, 1);
	};
	return 0;
};

extern "C"
int dat_level_set_end_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mPositionEnd = Vector3D(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)+selfdata->mData->mFloorHeight);
	return 0;
};

extern "C"
int dat_level_add_painter_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	double z = luaL_checknumber(L, 4);
	E_ELECTRICCOLOUR ec = electricColourFromChar( luaL_checkstring(L, 5)[0] );
	selfdata->mData->mPositionsPainters.push_back( Vector3D( x, y, z+selfdata->mData->mFloorHeight ) );
	selfdata->mData->mColoursPainters.push_back( ec );
	return 0;
};

extern "C"
int dat_level_add_coin_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	double z = luaL_checknumber(L, 4);
	E_ELECTRICCOLOUR ec = electricColourFromChar( luaL_checkstring(L, 5)[0] );
	selfdata->mData->mPositionsCoins.push_back( Vector3D( x, y, z+selfdata->mData->mFloorHeight ) );
	selfdata->mData->mColoursCoins.push_back( ec );
	return 0;
};

extern "C"
int dat_level_set_startcolour_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mColourRacer = electricColourFromChar( luaL_checkstring(L, 2)[0] );
	return 0;
};

extern "C"
int dat_level_set_startposition_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mStartX = luaL_checknumber(L, 2);
	selfdata->mData->mStartY = luaL_checknumber(L, 3);
	selfdata->mData->mStartTheta = luaL_checknumber(L, 4);
	selfdata->mData->mStartPhi = luaL_checknumber(L, 5);
	return 0;
};

extern "C"
int dat_level_set_startvelocity_cmd( lua_State* L )
{
	dat_level_ud* selfdata = (dat_level_ud*)luaL_checkudata(L, 1, "dat.level");
	luaL_argcheck(L, selfdata != 0, 1, "Level expected");
	selfdata->mData->mStartXDot = luaL_checknumber(L, 2);
	selfdata->mData->mStartYDot = luaL_checknumber(L, 3);
	selfdata->mData->mStartThetaDot = luaL_checknumber(L, 4);
	selfdata->mData->mStartPhiDot = luaL_checknumber(L, 5);
	return 0;
};


extern "C"
int dat_ematerial_set_emission_cmd( lua_State* L )
{
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData->mEmissionOn = luaL_checknumber(L, 2);
	selfdata->mData->mEmissionOff = luaL_checknumber(L, 3);
	return 0;
};

extern "C"
int dat_ematerial_set_ambient_cmd( lua_State* L )
{
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData->mAmbientOn = luaL_checknumber(L, 2);
	selfdata->mData->mAmbientOff = luaL_checknumber(L, 3);
	return 0;
};

extern "C"
int dat_ematerial_set_diffuse_cmd( lua_State* L )
{
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData->mDiffuseOn = luaL_checknumber(L, 2);
	selfdata->mData->mDiffuseOff = luaL_checknumber(L, 3);
	return 0;
};

extern "C"
int dat_ematerial_set_specular_cmd( lua_State* L )
{
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData->mSpecularOn = luaL_checknumber(L, 2);
	selfdata->mData->mSpecularOff = luaL_checknumber(L, 3);
	return 0;
};

extern "C"
int dat_ematerial_set_shininess_cmd( lua_State* L )
{
	dat_ematerial_ud* selfdata = (dat_ematerial_ud*)luaL_checkudata(L, 1, "dat.ematerial");
	luaL_argcheck(L, selfdata != 0, 1, "Ematerial expected");
	selfdata->mData->mShininess = luaL_checknumber(L, 2);
	return 0;
};


static const luaL_reg dat_universe_methods[] = {
  {"__gc", dat_universe_destroy_cmd},
  {"set_racermasses", dat_universe_set_racermasses_cmd},
  {"set_racersize", dat_universe_set_racersize_cmd},
  {"set_racerimages", dat_universe_set_racerimages_cmd},
  {"set_spheredivision", dat_universe_set_spheredivision_cmd},
  {"set_worlds", dat_universe_set_worlds_cmd},
  {"set_skyboxsize", dat_universe_set_skyboxsize_cmd},
  {"set_racervelocitymax", dat_universe_set_racervelocitymax_cmd},
  {"set_forces", dat_universe_set_forces_cmd},
  {"set_itemsize", dat_universe_set_itemsize_cmd},
  {"set_itemmaterials", dat_universe_set_itemmaterials_cmd},
  {"set_racermaterials", dat_universe_set_racermaterials_cmd},
  {"set_itemthetadot", dat_universe_set_itemthetadot_cmd},
  {0, 0}
};

static const luaL_reg dat_world_methods[] = {
  {"__gc", dat_world_destroy_cmd},
  {"set_gravity", dat_world_set_gravity_cmd},
  {"set_skyboximage", dat_world_set_skyboximage_cmd},
  {"set_terrainimage", dat_world_set_terrainimage_cmd},
  {"set_trackimage", dat_world_set_trackimage_cmd},
  {"set_menuimage", dat_world_set_menuimage_cmd},
  {"set_story", dat_world_set_story_cmd},
  {"set_music", dat_world_set_music_cmd},
  {"set_levels", dat_world_set_levels_cmd},
  {"set_trackmaterial", dat_world_set_trackmaterial_cmd},
  {"set_price", dat_world_set_price_cmd},
  {0, 0}
};

static const luaL_reg dat_level_methods[] = {
  {"__gc", dat_level_destroy_cmd},
  {"set_trackheight", dat_level_set_trackheight_cmd},
  {"set_tracksize", dat_level_set_tracksize_cmd},
  {"set_quadspercell", dat_level_set_quadspercell_cmd},
  {"set_trackcolours", dat_level_set_trackcolours_cmd},
  {"set_trackfs", dat_level_set_trackFs_cmd},
  {"set_end", dat_level_set_end_cmd},
  {"add_painter", dat_level_add_painter_cmd},
  {"add_coin", dat_level_add_coin_cmd},
  {"set_startcolour", dat_level_set_startcolour_cmd},
  {"set_startposition", dat_level_set_startposition_cmd},
  {"set_startvelocity", dat_level_set_startvelocity_cmd},
  {0, 0}
};

static const luaL_reg dat_ematerial_methods[] = {
  {"__gc", dat_ematerial_destroy_cmd},
  {"set_emission", dat_ematerial_set_emission_cmd},
  {"set_ambient", dat_ematerial_set_ambient_cmd},
  {"set_diffuse", dat_ematerial_set_diffuse_cmd},
  {"set_specular", dat_ematerial_set_specular_cmd},
  {"set_shininess", dat_ematerial_set_shininess_cmd},
  {0, 0}
};

static const luaL_reg dat_functions[] = {
  {"universe", dat_universe_cmd},
  {"world", dat_world_cmd},
  {"level", dat_level_cmd},
  {"ematerial", dat_ematerial_cmd},
  {0, 0}
};

UniverseData* readLuaUniverse( const std::string& filename )
{
	lua_State* L = lua_open();
	luaL_openlibs(L);

	// metatable for dat.universe etc
	luaL_newmetatable(L, "dat.universe");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_universe_methods, 0);
	luaL_newmetatable(L, "dat.world");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_world_methods, 0);
	luaL_newmetatable(L, "dat.level");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_level_methods, 0);
	luaL_newmetatable(L, "dat.ematerial");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_ematerial_methods, 0);
	
	// Load the functions and methods
	luaL_openlib(L, "dat", dat_functions, 0);

	// Parse the file
	if ( luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 1, 0) ) {
		std::cerr << "Error loading " << filename << ": " << lua_tostring(L, -1) << std::endl;
		return NULL;
	}
	
	// Return the UniverseData if it worked
	dat_universe_ud* data = (dat_universe_ud*)luaL_checkudata(L, -1, "dat.universe");
	if (!data) {
		std::cerr << "Error loading " << filename << ": Must return the universe-data." << std::endl;
		return 0;
	}
	UniverseData* univ = data->mData;
	lua_close(L);
	return univ;

}

WorldData* readLuaWorld( const std::string& filename )
{
	lua_State* L = lua_open();
	luaL_openlibs(L);

	// metatable for dat.world
	luaL_newmetatable(L, "dat.universe");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_universe_methods, 0);
	luaL_newmetatable(L, "dat.world");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_world_methods, 0);
	luaL_newmetatable(L, "dat.level");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_level_methods, 0);
	luaL_newmetatable(L, "dat.ematerial");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_ematerial_methods, 0);
	
	// Load the functions and methods
	luaL_openlib(L, "dat", dat_functions, 0);

	// Parse the file
	if ( luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 1, 0) ) {
		std::cerr << "Error loading " << filename << ": " << lua_tostring(L, -1) << std::endl;
		return NULL;
	}
	
	// Return the UniverseData if it worked
	dat_world_ud* data = (dat_world_ud*)luaL_checkudata(L, -1, "dat.world");
	if (!data) {
		std::cerr << "Error loading " << filename << ": Must return the world-data." << std::endl;
		return 0;
	}
	WorldData* wor = data->mData;
	lua_close(L);
	return wor;

}

LevelData* readLuaLevel( const std::string& filename )
{
	lua_State* L = lua_open();
	luaL_openlibs(L);

	// metatable for dat.world
	luaL_newmetatable(L, "dat.universe");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_universe_methods, 0);
	luaL_newmetatable(L, "dat.world");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_world_methods, 0);
	luaL_newmetatable(L, "dat.level");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_level_methods, 0);
	luaL_newmetatable(L, "dat.ematerial");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_openlib(L, 0, dat_ematerial_methods, 0);
	
	// Load the functions and methods
	luaL_openlib(L, "dat", dat_functions, 0);

	// Parse the file
	if ( luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 1, 0) ) {
		std::cerr << "Error loading " << filename << ": " << lua_tostring(L, -1) << std::endl;
		return NULL;
	}
	
	// Return the UniverseData if it worked
	dat_level_ud* data = (dat_level_ud*)luaL_checkudata(L, -1, "dat.level");
	if (!data) {
		std::cerr << "Error loading " << filename << ": Must return the level-data." << std::endl;
		return 0;
	}
	LevelData* lev = data->mData;
	lua_close(L);
	return lev;

}