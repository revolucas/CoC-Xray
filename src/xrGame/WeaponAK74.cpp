#include "pch_script.h"
#include "WeaponAK74.h"
#include "Weapon.h"
#include "WeaponMagazined.h"
#include "WeaponMagazinedWGrenade.h"

CWeaponAK74::CWeaponAK74(ESoundTypes eSoundType) : CWeaponMagazinedWGrenade(eSoundType)
{}

CWeaponAK74::~CWeaponAK74()
{}

using namespace luabind;

#pragma optimize("s",on)
void CWeaponAK74::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CWeaponAK74,CGameObject>("CWeaponAK74")
			.def(constructor<>()),
			
		class_<CWeapon,CGameObject>("CWeapon")
			.def(constructor<>())
			.def("can_kill", (bool (CWeapon::*)() const)&CWeapon::can_kill)
			.def("ready_to_kill", (bool (CWeapon::*)() const)&CWeapon::ready_to_kill)
			.def("GetAddonsState", (u8 (CWeapon::*)() const)&CWeapon::GetAddonsState)
			.def("SetAddonsState",&CWeapon::SetAddonsState)
			.def("IsZoomed", (bool (CWeapon::*)() const)&CWeapon::IsZoomed)
			.def("GetZoomFactor", (float (CWeapon::*)() const)&CWeapon::GetZoomFactor)
			.def("SetZoomFactor", &CWeapon::SetZoomFactor)
			.def("Weight", (float (CWeapon::*)() const)&CWeapon::Weight)
			.def("Cost", (u32 (CWeapon::*)() const)&CWeapon::Cost)
			.def("GetMagazine", &CWeapon::GetMagazine, return_stl_iterator)
			,
			
		class_<CWeaponMagazined,CGameObject>("CWeaponMagazined")
			.def(constructor<>()),
			
		class_<CWeaponMagazinedWGrenade,CGameObject>("CWeaponMagazinedWGrenade")
			.def(constructor<>())
	];
}
