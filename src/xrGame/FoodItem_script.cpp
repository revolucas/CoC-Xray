#include "pch_script.h"
#include "FoodItem.h"
#include "eatable_item.h"

using namespace luabind;

#pragma optimize("s",on)
void CFoodItem::script_register(lua_State *L)
{
	module(L)
		[
			class_<CFoodItem, CEatableItem>("CFoodItem")
			.def(constructor<>())
		];
}