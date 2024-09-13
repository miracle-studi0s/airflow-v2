#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"

#include "collision.h"
#include "base_player_weapon.h"
#include "player_pawn.h"

#include "../sdk.h"

bool c_cs_player_pawn::is_alive()
{
	return health() > 0;
}

bool c_cs_player_pawn::has_armor(int hitgroup)
{
	// REPLACE TO ENUM LATER!
	if (hitgroup == 1)
		return item_services()->has_helmet();

	return armor_value();
}

int c_cs_player_pawn::get_bone_index(const char* name)
{
	using fn = int(__fastcall*)(void*, const char*);
	return patterns::get_bone_index.as<fn>()(this, name);
}

uint32_t c_cs_player_pawn::get_collision_owner_index()
{
	const auto player_collision = collision();
	if (player_collision && !(player_collision->solid_flags() & 4))
		return owner_entity().get_entry_index();

	return std::numeric_limits<uint32_t>::max();
}

vector3d c_cs_player_pawn::get_eye_pos()
{
	vector3d eye_pos{};
	vtable::call<void>(this, GET_EYE_POS, &eye_pos);
	return eye_pos;
}

c_base_player_weapon* c_cs_player_pawn::get_active_weapon()
{
	const auto player_weapon_services = weapon_services();
	if (player_weapon_services)
	{
		const auto active_weapon = player_weapon_services->active_weapon();
		const auto entry_index = active_weapon.get_entry_index();

		auto entity = sdk::entity_system->get_base_entity(entry_index).as<c_base_player_weapon*>();
		if (entity && entity->is_weapon())
			return entity;
	}

	return nullptr;
}
