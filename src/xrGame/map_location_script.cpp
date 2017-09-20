#include "pch_script.h"
#include "map_location.h"
#include "map_manager.h"

using namespace luabind;

#pragma optimize("s",on)
void CMapLocation::script_register(lua_State *L)
{
	module(L)
		[
			class_<CMapManager>("CMapManager")
			.def(constructor<>())
			.def("AddMapLocation", &CMapManager::AddMapLocation_script)
			.def("AddUserLocation", &CMapManager::AddUserLocation_script)
			.def("RemoveMapLocation", &CMapManager::RemoveMapLocation_script)
			.def("HasMapLocation", &CMapManager::HasMapLocation_script)
			.def("GetMapLocation", &CMapManager::GetMapLocation_script)
			.def("RemoveMapLocationByObjectID", &CMapManager::RemoveMapLocationByObjectID)
			.def("RemoveMapLocation", &CMapManager::RemoveMapLocation)
			.def("DisableAllPointers", &CMapManager::DisableAllPointers)
			.def("MapLocationsForEach", &CMapManager::MapLocationsForEach)
			.def("AllLocationsForEach", &CMapManager::AllLocationsForEach),

			class_<CMapLocation>("CMapLocation")
			.def(constructor<>())
			.def("HintEnabled", &CMapLocation::HintEnabled)
			.def("GetHint", &CMapLocation::GetHint)
			.def("SetHint", &CMapLocation::SetHint)
			.def("PointerEnabled", &CMapLocation::PointerEnabled)
			.def("EnablePointer", &CMapLocation::EnablePointer)
			.def("DisablePointer", &CMapLocation::DisablePointer)
			.def("GetType", &CMapLocation::GetType)
			.def("SpotSize", &CMapLocation::SpotSize)
			.def("IsUserDefined", &CMapLocation::IsUserDefined)
			.def("SetUserDefinedFlag", &CMapLocation::SetUserDefinedFlag)
			.def("HighlightSpot", &CMapLocation::HighlightSpot)
			.def("Collidable", &CMapLocation::Collidable)
			.def("SpotEnabled", &CMapLocation::SpotEnabled)
			.def("EnableSpot", &CMapLocation::EnableSpot)
			.def("DisableSpot", &CMapLocation::DisableSpot)
			.def("GetLevelName", &CMapLocation::GetLevelName)
			.def("GetPosition", &CMapLocation::GetPosition)
			.def("ObjectID", &CMapLocation::ObjectID)
			.def("GetLastPosition", &CMapLocation::GetLastPosition)
			.def("GetOwnerTaskID", &CMapLocation::GetOwnerTaskID)
		];
}
