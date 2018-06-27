////////////////////////////////////////////////////////////////////////////
//	Module 		: space_restrictor_inline.h
//	Created 	: 17.08.2004
//  Modified 	: 17.08.2004
//	Author		: Dmitriy Iassenev
//	Description : Space restrictor inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

IC	CSpaceRestrictor::CSpaceRestrictor		()
{
	m_space_restrictor_type = RestrictionSpace::eRestrictorTypeNone;
	m_selfbounds.P.set(0.f, 0.f, 0.f);
	m_selfbounds.R = 1.f;
	m_actuality = false;
}

IC	bool CSpaceRestrictor::actual			() const
{
	return							(m_actuality);
}

IC	void CSpaceRestrictor::actual			(bool value) const
{
	m_actuality						= value;
}

IC RestrictionSpace::ERestrictorTypes CSpaceRestrictor::restrictor_type	() const
{
	return RestrictionSpace::ERestrictorTypes(m_space_restrictor_type);
}

IC void CSpaceRestrictor::change_restrictor_type(RestrictionSpace::ERestrictorTypes restrictor_type) 
{
	m_space_restrictor_type = u8(restrictor_type);
}