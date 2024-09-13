#pragma once

#include "../utl/vector.h"

class c_player_weapon_services
{
public:
	SCHEMA(c_handle, active_weapon, fnv_hash("CPlayer_WeaponServices->m_hActiveWeapon"));
	SCHEMA(c_handle, last_weapon, fnv_hash("CPlayer_WeaponServices->m_hLastWeapon"));
	SCHEMA(c_network_utl_vector<c_handle*>, my_weapons, fnv_hash("CPlayer_WeaponServices->m_hMyWeapons"));
};