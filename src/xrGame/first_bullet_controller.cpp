#include "stdafx.h"
#include "first_bullet_controller.h"
#include "level.h"

first_bullet_controller::first_bullet_controller()
{
	m_last_short_time	= 0;
	m_shot_timeout		= 0;
	m_fire_dispertion	= 0;
}

void first_bullet_controller::load(shared_str const & section)
{
	m_use_first_bullet	= pSettings->r_bool	(section, "use_first_bullet") ? true : false;
	if (!m_use_first_bullet)
		return;
	m_fire_dispertion		= pSettings->r_float(section, "first_bullet_dispertion");
	m_shot_timeout			= pSettings->r_u32	(section, "first_bullet_timeout");
	m_actor_velocity_limit	= pSettings->r_float(section, "first_bullet_velocity_limit");
}

bool first_bullet_controller::is_bullet_first(float actor_linear_velocity) const
{
	return false;
}

void first_bullet_controller::make_shot()
{
	m_last_short_time = Device.dwTimeGlobal;
}





