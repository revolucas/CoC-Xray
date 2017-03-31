#include "pch_script.h"
#include "BottleItem.h"
#include "eatable_item.h"

using namespace luabind;

#pragma optimize("s",on)
void CBottleItem::script_register(lua_State *L)
{
	module(L)
		[
			class_<CBottleItem, CEatableItem>("CBottleItem")
			.def(constructor<>())
			.def("BreakToPieces", &CBottleItem::BreakToPieces)
		];
}