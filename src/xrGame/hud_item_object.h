#pragma once

#include "inventory_item_object.h"
#include "huditem.h"
#include "ui/UIWindow.h"


class CUIHudUI : public CUIWindow
{
	typedef CUIWindow inherited;

	CHudItem*				m_parent;
	Fmatrix					m_attach_offset;
	LPCSTR					m_attach_bone;

	void					GetUILocatorMatrix(Fmatrix& _m);
public:
	CUIWindow*				m_wrk_area;

	virtual void			update();
	virtual void			Draw();

	void					construct(CHudItem* p, LPCSTR xml_tag);
};

class CHudItemObject : 
		public CInventoryItemObject,
		public CHudItem
{
protected: //чтоб нельзя было вызвать на прямую
						CHudItemObject		();
	virtual				~CHudItemObject		();

public:
	virtual	DLL_Pure	*_construct			();

public:
	virtual CHudItem	*cast_hud_item		()	{return this;}

	//Alundaio
	LPCSTR				m_hud_ui_xml_tag_name;
	bool				m_b_show_ui;
	CUIHudUI*			m_3d_ui;
	virtual void		render_item_3d_ui();
	virtual bool		render_item_3d_ui_query();
	virtual void		Create_3D_UI();
	//-Alundaio
public:
	virtual void		Load				(LPCSTR section);
	virtual bool		Action				(u16 cmd, u32 flags);
	virtual void		SwitchState			(u32 S);
	virtual void		OnStateSwitch		(u32 S);
	virtual void		OnEvent				(NET_Packet& P, u16 type);
	virtual void		OnH_A_Chield		();
	virtual void		OnH_B_Chield		();
	virtual void		OnH_B_Independent	(bool just_before_destroy);
	virtual void		OnH_A_Independent	();
	virtual	BOOL		net_Spawn			(CSE_Abstract* DC);
	virtual void		net_Destroy			();
	virtual bool		ActivateItem		();
	virtual void		DeactivateItem	();
	virtual void		UpdateCL			();
	virtual void		renderable_Render	();
	virtual void		on_renderable_Render();
	virtual void		OnMoveToRuck		(const SInvItemPlace& prev);

	virtual bool			use_parent_ai_locations	() const
	{
		return				CInventoryItemObject::use_parent_ai_locations	() && (Device.dwFrame != dwXF_Frame);
	}
};
