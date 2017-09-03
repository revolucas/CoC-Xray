#include "stdafx.h"
#include "ActorBackpack.h"
#include "Actor.h"
#include "Inventory.h"

CBackpack::CBackpack()
{
	m_flags.set(FUsingCondition, FALSE);
}

CBackpack::~CBackpack()
{

}

void CBackpack::Load(LPCSTR section)
{
	inherited::Load(section);

	m_additional_weight = pSettings->r_float(section, "additional_inventory_weight");
	m_additional_weight2 = pSettings->r_float(section, "additional_inventory_weight2");
	m_fPowerRestoreSpeed = READ_IF_EXISTS(pSettings, r_float, section, "power_restore_speed", 0.0f);
	m_fPowerLoss = READ_IF_EXISTS(pSettings, r_float, section, "power_loss", 1.0f);
	clamp(m_fPowerLoss, EPS, 1.0f);

	m_flags.set(FUsingCondition, READ_IF_EXISTS(pSettings, r_bool, section, "use_condition", TRUE));
}

BOOL CBackpack::net_Spawn(CSE_Abstract* DC)
{
	return inherited::net_Spawn(DC);
}

void CBackpack::net_Export(NET_Packet& P)
{
	inherited::net_Export(P);
	P.w_float_q8(GetCondition(), 0.0f, 1.0f);
}

void CBackpack::net_Import(NET_Packet& P)
{
	inherited::net_Import(P);
	float _cond;
	P.r_float_q8(_cond, 0.0f, 1.0f);
	SetCondition(_cond);
}

void CBackpack::OnH_A_Chield()
{
	inherited::OnH_A_Chield();
}

void CBackpack::OnMoveToSlot(const SInvItemPlace& previous_place)
{
	inherited::OnMoveToSlot(previous_place);
	/*
	if (m_pInventory && (previous_place.type == eItemPlaceSlot))
	{
		CActor* pActor = smart_cast<CActor*> (H_Parent());
		if (pActor)
		{

		}
	}
	*/
}

void CBackpack::OnMoveToRuck(const SInvItemPlace& previous_place)
{
	inherited::OnMoveToRuck(previous_place);
	/*
	if (m_pInventory && (previous_place.type == eItemPlaceSlot))
	{
		CActor* pActor = smart_cast<CActor*> (H_Parent());
		if (pActor)
		{

		}
	}
	*/
}

void CBackpack::Hit(float hit_power, ALife::EHitType hit_type)
{
	if (IsUsingCondition() == false) return;
	hit_power *= GetHitImmunity(hit_type);
	ChangeCondition(-hit_power);
}