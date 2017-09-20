#pragma once
#include "object_interfaces.h"
#include "map_location_defs.h"
#include "../../xrServerEntities/script_space_forward.h"
#include "../../xrServerEntities/script_export_space.h"

class CMapLocationWrapper;
class CInventoryOwner;
class CMapLocation;

class CMapManager
{
	CMapLocationWrapper*	m_locations_wrapper;
	Locations*				m_locations;
	xr_vector<CMapLocation*> m_deffered_destroy_queue;
public:

							CMapManager					();
							~CMapManager				();
	void	__stdcall		Update						();
	/*ICF */Locations&		Locations					();//{return *m_locations;}
	CMapLocation*			AddMapLocation				(const shared_str& spot_type, u16 id);
	CMapLocation*			AddRelationLocation			(CInventoryOwner* pInvOwner);
	CMapLocation*			AddUserLocation(const shared_str& spot_type, const shared_str& level_name, Fvector position);
	void					RemoveMapLocation			(const shared_str& spot_type, u16 id);
	bool					HasMapLocation				(const shared_str& spot_type, u16 id);
	void					RemoveMapLocationByObjectID (u16 id); //call on destroy object
	void					RemoveMapLocation			(CMapLocation* ml);
	CMapLocation*			GetMapLocation				(const shared_str& spot_type, u16 id);
	void					GetMapLocations				(const shared_str& spot_type, u16 id, xr_vector<CMapLocation*>& res);
	void					DisableAllPointers			();
	bool					GetMapLocationsForObject	(u16 id, xr_vector<CMapLocation*>& res);
	void					OnObjectDestroyNotify		(u16 id);
	void					ResetStorage				() {m_locations = NULL;};
#ifdef DEBUG
	void					Dump						();
#endif
	void					Destroy						(CMapLocation*);

	//for security
	CMapLocation*			AddMapLocation_script(LPCSTR spot_type, u16 id) {AddMapLocation(spot_type, id);};
	CMapLocation*			AddUserLocation_script(LPCSTR spot_type, LPCSTR level_name, Fvector position){ AddUserLocation(spot_type, level_name, position); };
	void					RemoveMapLocation_script(LPCSTR spot_type, u16 id){	RemoveMapLocation(spot_type, id);};
	bool					HasMapLocation_script(LPCSTR spot_type, u16 id){HasMapLocation(spot_type, id);};
	CMapLocation*			GetMapLocation_script(LPCSTR spot_type, u16 id){ GetMapLocation(spot_type, id); };
	void					MapLocationsForEach(LPCSTR spot_type, u16 id,const luabind::functor<bool> &functor);
	void					AllLocationsForEach(const luabind::functor<bool> &functor);

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
