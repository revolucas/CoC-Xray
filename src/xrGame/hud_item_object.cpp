#include "stdafx.h"
#include "hud_item_object.h"

//Alundaio: 3D UI
#include "Level.h"
#include "inventory.h"
#include "Weapon.h"
#include "weaponBinocularsVision.h"
#include "ui/UIStatic.h"
//-Alundaio

CHudItemObject::CHudItemObject			()
{
	//Alundaio: For 3D UI
	m_3d_ui = NULL;
	m_hud_ui_xml_tag_name = NULL;
	m_b_show_ui = false;
}

CHudItemObject::~CHudItemObject			()
{
	if (m_3d_ui)
		xr_delete(m_3d_ui);
}

DLL_Pure *CHudItemObject::_construct	()
{
	CInventoryItemObject::_construct();
	CHudItem::_construct		();
	return						(this);
}

void CHudItemObject::Load				(LPCSTR section)
{
	CInventoryItemObject::Load	(section);
	CHudItem::Load				(section);
	m_hud_ui_xml_tag_name = READ_IF_EXISTS(pSettings, r_string, HudSection(), "hud_ui_xml_tag_name", ""); //Alundaio: For 3D UI
}

bool CHudItemObject::Action				(u16 cmd, u32 flags)
{
	if (CInventoryItemObject::Action(cmd, flags))
		return					(true);
	return						(CHudItem::Action(cmd,flags));
}

void CHudItemObject::SwitchState		(u32 S)
{
	CHudItem::SwitchState		(S);
}

void CHudItemObject::OnStateSwitch		(u32 S)
{
	CHudItem::OnStateSwitch		(S);
}

void CHudItemObject::OnMoveToRuck(const SInvItemPlace& prev)
{
	m_b_show_ui = false; //Alundaio: For 3D UI
	CInventoryItemObject::OnMoveToRuck(prev);
	CHudItem::OnMoveToRuck			(prev);
}

void CHudItemObject::OnEvent			(NET_Packet& P, u16 type)
{
	CInventoryItemObject::OnEvent(P,type);
	CHudItem::OnEvent			(P,type);
}

void CHudItemObject::OnH_A_Chield		()
{
	CHudItem::OnH_A_Chield				();
	CInventoryItemObject::OnH_A_Chield	();
}

void CHudItemObject::OnH_B_Chield		()
{
	CInventoryItemObject::OnH_B_Chield	();
	CHudItem::OnH_B_Chield				();
}

void CHudItemObject::OnH_B_Independent	(bool just_before_destroy)
{
	CHudItem::OnH_B_Independent				(just_before_destroy);
	CInventoryItemObject::OnH_B_Independent	(just_before_destroy);
}

void CHudItemObject::OnH_A_Independent	()
{
	CHudItem::OnH_A_Independent				();
	CInventoryItemObject::OnH_A_Independent	();
}

BOOL CHudItemObject::net_Spawn			(CSE_Abstract* DC)
{
	m_b_show_ui = false; //Alundaio: For 3D UI
	return						(
		CInventoryItemObject::net_Spawn(DC) &&
		CHudItem::net_Spawn(DC)
	);
}

void CHudItemObject::net_Destroy		()
{
	CHudItem::net_Destroy		();
	CInventoryItemObject::net_Destroy	();
}

bool CHudItemObject::ActivateItem			()
{
	return			(CHudItem::ActivateItem());
}

void CHudItemObject::DeactivateItem			()
{
	CHudItem::DeactivateItem		();
}

void CHudItemObject::UpdateCL			()
{
	CInventoryItemObject::UpdateCL	();
	CHudItem::UpdateCL				();
	//Alundaio: 3D UI
	m_b_show_ui = false;
	if (GetNextState() == GetState() && H_Parent() == Level().CurrentEntity() && m_pInventory->ActiveItem() == this)
	{
		m_b_show_ui = true;
		CWeapon* wpn = smart_cast<CWeapon*>(this);
		if (wpn)
			m_b_show_ui = (/*(wpn->get_ScopeStatus() == ALife::eAddonDisabled) || */(wpn->GetAddonsState()&CSE_ALifeItemWeapon::eWeaponAddonScope != 0));

		switch (GetState())
		{
		case eHiding:
		case eHidden:	m_b_show_ui = false;
		default:
			Create_3D_UI();
			if (m_b_show_ui && m_3d_ui)
				m_3d_ui->update();
		}
	}
	//-Alundaio
}

void CHudItemObject::renderable_Render	()
{
	CHudItem::renderable_Render	();
}

void CHudItemObject::on_renderable_Render()
{
	CInventoryItemObject::renderable_Render();
}

void CHudItemObject::render_item_3d_ui()
{
	CHudItem::render_item_3d_ui();
}

bool CHudItemObject::render_item_3d_ui_query()
{
	return	m_b_show_ui && m_3d_ui && H_Parent() && H_Parent() == Level().CurrentViewEntity() && m_pInventory->ActiveItem() == this;
}

void CHudItemObject::Create_3D_UI()
{
	if (!m_b_show_ui)
		return;

	if (m_hud_ui_xml_tag_name[0] == 0)
		return;

	if (!m_3d_ui)
	{
		m_3d_ui = xr_new<CUIHudUI>();
		m_3d_ui->construct(cast_hud_item(), m_hud_ui_xml_tag_name);
	}
}

#include "player_hud.h"
#include "../Include/xrRender/UIRender.h"
#include "ui/UIXmlInit.h"
#include "ui/xrUIXmlParser.h"
void CUIHudUI::construct(CHudItem* p, LPCSTR xml_tag)
{
	m_parent = p;

	CUIXml uiXml;
	uiXml.Load(CONFIG_PATH, UI_PATH, "hud_ui_3d.xml");

	CUIXmlInit xml_init;
	string512 buff;
	xr_strcpy(buff, xml_tag);

	xml_init.InitWindow(uiXml, buff, 0, this);

	// Canvas
	xr_sprintf(buff, "%s:canvas", xml_tag);
	m_wrk_area = xr_new<CUIWindow>();
	xml_init.InitWindow(uiXml, buff, 0, m_wrk_area);
	m_wrk_area->SetAutoDelete(true);
	AttachChild(m_wrk_area);

	//read attach offset
	m_attach_bone = pSettings->r_string(m_parent->HudSection(), "hud_ui_attach_bone");
	Fvector _map_attach_p = pSettings->r_fvector3(m_parent->HudSection(), "hud_ui_pos");
	Fvector _map_attach_r = pSettings->r_fvector3(m_parent->HudSection(), "hud_ui_rot");

	_map_attach_r.mul(PI / 180.f);
	m_attach_offset.setHPB(_map_attach_r.x, _map_attach_r.y, _map_attach_r.z);
	m_attach_offset.translate_over(_map_attach_p);
}

void CUIHudUI::update()
{
	if (!m_wrk_area || !IsChild(m_wrk_area))
		return;
	inherited::Update();
}

void CUIHudUI::Draw()
{
	Fmatrix LM;
	GetUILocatorMatrix(LM);

	IUIRender::ePointType bk = UI().m_currentPointType;
	UI().m_currentPointType = IUIRender::pttLIT;

	UIRender->CacheSetXformWorld(LM);
	UIRender->CacheSetCullMode(IUIRender::cmNONE);

	CUIWindow::Draw();

	Fvector2 wrk_sz = m_wrk_area->GetWndSize();
	Fvector2 rp;
	m_wrk_area->GetAbsolutePos(rp);

	UI().ScreenFrustumLIT().CreateFromRect(Frect().set(rp.x, rp.y, wrk_sz.x, wrk_sz.y));
	UI().m_currentPointType = bk;

	UIRender->CacheSetCullMode(IUIRender::cmCCW);
}

void CUIHudUI::GetUILocatorMatrix(Fmatrix& _m)
{
	Fmatrix	trans = m_parent->HudItemData()->m_item_transform;
	u16 bid = m_parent->HudItemData()->m_model->LL_BoneID(m_attach_bone);
	Fmatrix cover_bone = m_parent->HudItemData()->m_model->LL_GetTransform(bid);
	_m.mul(trans, cover_bone);
	_m.mulB_43(m_attach_offset);
}