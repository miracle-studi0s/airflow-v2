#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"

#include "entity_system.h"

address c_entity_system::get_base_entity(int index)
{
	using fn = void*(__fastcall*)(c_entity_system*, int);
	return { patterns::get_base_entity.as<fn>()(this, index) };
}

address c_entity_system::get_local_player_pawn()
{
	using fn = void*(__fastcall*)(int);
	return { patterns::get_local_player_pawn.as<fn>()(0) };
}

address c_entity_system::get_local_player_controller()
{
	using fn = void*(__fastcall*)(int);
	return { patterns::get_local_player_controller.as<fn>()(0) };
}

int c_entity_system::get_highest_entity_index()
{
	using fn = int(__thiscall*)(c_entity_system*, int*);

	int highest_entity_index{ -1 };
	patterns::get_highest_entity_index.as<fn>()(this, &highest_entity_index);
	return highest_entity_index;
}