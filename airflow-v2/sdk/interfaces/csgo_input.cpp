#include <fnv1a.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"

#include "../math/math.h"

#include "csgo_input.h"

vector3d c_csgo_input::get_view_angles()
{
	using fn = void* (__fastcall*)(c_csgo_input*, int);
	return *reinterpret_cast<vector3d*>(patterns::get_view_angles.as<fn>()(this, 0));
}

void c_csgo_input::set_view_angles(vector3d& value)
{
	using fn = void* (__fastcall*)(c_csgo_input*, int, vector3d&);
	patterns::set_view_angles.as<fn>()(this, 0, value);
}

c_user_cmd* c_csgo_input::get_user_cmd()
{
	return &commands[sequence_number % 150];
}

c_user_cmd* c_csgo_input::get_next_user_cmd()
{
	return &commands[(sequence_number + 1) % 150];
}