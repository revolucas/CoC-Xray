////////////////////////////////////////////////////////////////////////////
//	Module 		: xrServer_Objects_ALife_Items_script.cpp
//	Created 	: 19.09.2002
//  Modified 	: 04.06.2003
//	Author		: Dmitriy Iassenev
//	Description : Server items for ALife simulator, script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "xrServer_Objects_ALife_Items.h"
#include "xrServer_script_macroses.h"

void add_upgrade_script(CSE_ALifeInventoryItem* ta, LPCSTR str)
{
	shared_str upgrade_id(str);
	ta->add_upgrade(upgrade_id);
}

bool has_upgrade_script(CSE_ALifeInventoryItem* ta,LPCSTR str)
{
	shared_str upgrade_id(str);
	return ta->has_upgrade(upgrade_id);
}

using namespace luabind;

#pragma optimize("s",on)
void CSE_ALifeInventoryItem::script_register(lua_State *L)
{
	module(L)[
		class_<CSE_ALifeInventoryItem>
			("cse_alife_inventory_item")
//			.def(		constructor<LPCSTR>())
			.def("has_upgrade", &has_upgrade_script)
			.def("add_upgrade", &add_upgrade_script)
			.def_readwrite("condition", &CSE_ALifeInventoryItem::m_fCondition)
	];
}

void CSE_ALifeItem::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item2(
//		luabind_class_abstract2(
			CSE_ALifeItem,
			"cse_alife_item",
			CSE_ALifeDynamicObjectVisual,
			CSE_ALifeInventoryItem
		)
	];
}

void CSE_ALifeItemTorch::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemTorch,
			"cse_alife_item_torch",
			CSE_ALifeItem
		)
	];
}

void CSE_ALifeItemAmmo::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemAmmo,
			"cse_alife_item_ammo",
			CSE_ALifeItem
		)
	];
}

void CSE_ALifeItemWeapon::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemWeapon,
			"cse_alife_item_weapon",
			CSE_ALifeItem
		)
		.enum_("addon_flag")
		[
			value("eWeaponAddonGrenadeLauncher", int(CSE_ALifeItemWeapon::EWeaponAddonState::eWeaponAddonGrenadeLauncher)),
			value("eWeaponAddonScope", int(CSE_ALifeItemWeapon::EWeaponAddonState::eWeaponAddonScope)),
			value("eWeaponAddonSilencer", int(CSE_ALifeItemWeapon::EWeaponAddonState::eWeaponAddonSilencer)),
			value("eAddonAttachable", int(CSE_ALifeItemWeapon::EWeaponAddonStatus::eAddonAttachable)),
			value("eAddonDisabled", int(CSE_ALifeItemWeapon::EWeaponAddonStatus::eAddonDisabled)),
			value("eAddonPermanent", int(CSE_ALifeItemWeapon::EWeaponAddonStatus::eAddonPermanent))
		]
		.def("clone_addons",						&CSE_ALifeItemWeapon::clone_addons)
		.def("set_ammo_elapsed",					&CSE_ALifeItemWeapon::set_ammo_elapsed)
		.def("set_ammo_elapsed2",					&CSE_ALifeItemWeapon::set_ammo_elapsed2)
		.def("get_ammo_elapsed",					&CSE_ALifeItemWeapon::get_ammo_elapsed)
		.def("get_ammo_elapsed2",					&CSE_ALifeItemWeapon::get_ammo_elapsed2)
		.def("get_ammo_magsize",					&CSE_ALifeItemWeapon::get_ammo_magsize)
		.def_readwrite("grenade_launcher_status",	&CSE_ALifeItemWeapon::m_grenade_launcher_status)
		.def_readwrite("silencer_status",			&CSE_ALifeItemWeapon::m_silencer_status)
		.def_readwrite("scope_status",				&CSE_ALifeItemWeapon::m_scope_status)
		.def("get_ammo_type",						&CSE_ALifeItemWeapon::get_ammo_type)
		.def("get_ammo_type2",						&CSE_ALifeItemWeapon::get_ammo_type2)
		.def("set_ammo_type",						&CSE_ALifeItemWeapon::set_ammo_type)
		.def("set_ammo_type2",						&CSE_ALifeItemWeapon::set_ammo_type2)
		.def("get_addon_flags",						&CSE_ALifeItemWeapon::get_addon_flags)
		//.def("set_addon_flags",					    &CSE_ALifeItemWeapon::set_addon_flags)
	];
}

void CSE_ALifeItemWeaponShotGun::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemWeaponShotGun,
			"cse_alife_item_weapon_shotgun",
			CSE_ALifeItemWeapon
			)
	];
}

void CSE_ALifeItemWeaponAutoShotGun::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemWeaponAutoShotGun,
			"cse_alife_item_weapon_auto_shotgun",
			CSE_ALifeItemWeapon
			)
	];
}

void CSE_ALifeItemDetector::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemDetector,
			"cse_alife_item_detector",
			CSE_ALifeItem
		)
	];
}

void CSE_ALifeItemArtefact::script_register(lua_State *L)
{
	module(L)[
		luabind_class_item1(
			CSE_ALifeItemArtefact,
			"cse_alife_item_artefact",
			CSE_ALifeItem
		)
	];
}
