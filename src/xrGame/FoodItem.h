#pragma once

#include "eatable_item_object.h"
#include "script_export_space.h"

class CFoodItem: public CEatableItemObject
{
public:
						CFoodItem			();
	virtual				~CFoodItem			();

	virtual void	net_Import(NET_Packet& P);					// import from server
	virtual void	net_Export(NET_Packet& P);					// export to server
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CFoodItem)
#undef script_type_list
#define script_type_list save_type_list(CFoodItem)