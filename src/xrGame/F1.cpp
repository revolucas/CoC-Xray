#include "pch_script.h"
#include "f1.h"
#include "WeaponAmmo.h"
#include "Medkit.h"
#include "Antirad.h"
#include "FoodItem.h"
#include "BottleItem.h"
#include "ExplosiveItem.h"
#include "InventoryBox.h"

CF1::CF1(void) {
}

CF1::~CF1(void) {
}

using namespace luabind;

#pragma optimize("s",on)
void CF1::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CF1,CGameObject>("CF1")
			.def(constructor<>()),
			//new 14.10.08 peacemaker
		//class_<CWeaponAmmo,CGameObject>("CWeaponAmmo") //Alun: Moved to WeaponAmmo_script.cpp
		//	.def(constructor<>()),
		//class_<CMedkit,CGameObject>("CMedkit") //Alun: Moved to Medkit_script.cpp
		//	.def(constructor<>()),
		//class_<CAntirad,CGameObject>("CAntirad") //Alun: Moved to Antirad_script.cpp
		//	.def(constructor<>()),
		//class_<CFoodItem,CGameObject>("CFoodItem") //Alun: Moved to FoodItem_script.cpp
		//	.def(constructor<>()),
		//class_<CBottleItem,CGameObject>("CBottleItem") //Alun: Moved to BottleItem_script.cpp
		//	.def(constructor<>()),
		//class_<CInventoryBox,CGameObject>("CInventoryBox") //Alun: Moved to InventoryBox_script.cpp
		//	.def(constructor<>()),
		class_<CExplosiveItem,CGameObject>("CExplosiveItem")
			.def(constructor<>())
	];
}
