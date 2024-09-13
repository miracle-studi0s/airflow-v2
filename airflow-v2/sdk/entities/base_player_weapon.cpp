#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "base_player_weapon.h"

bool c_base_player_weapon::is_throwing_nade()
{
	auto data = weapon_data();
	if (data && data->weapon_type() == WEAPONTYPE_GRENADE)
	{
		auto grenade = reinterpret_cast<c_base_cs_grenade*>(this);
		return grenade->throw_time() != 0.f;
	}

	return false;
}

float c_base_player_weapon::get_max_speed()
{
	return vtable::call<float>(this, GET_MAX_SPEED);
}

float c_base_player_weapon::get_inaccuracy()
{
	using fn = float(__fastcall*)(void*);
	return patterns::get_inaccuracy.as<fn>()(this);
}

float c_base_player_weapon::get_spread()
{
	using fn = float(__fastcall*)(void*);
	return patterns::get_spread.as<fn>()(this);
}

void c_base_player_weapon::update_accuracy_penalty()
{
	using fn = void(__fastcall*)(void*);
	patterns::update_accuracy_penalty.as<fn>()(this);
}