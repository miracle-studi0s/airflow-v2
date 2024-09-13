#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"

#include "player_controller.h"

void c_cs_player_controller::physics_run_think()
{
	using fn = void* (__fastcall*)(void*);
	patterns::physics_run_think.as<fn>()(this);
}