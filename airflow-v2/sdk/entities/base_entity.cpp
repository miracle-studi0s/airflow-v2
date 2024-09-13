#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"
#include "base_entity.h"

bool c_base_entity::is_weapon()
{
	return vtable::call<bool>(this, IS_WEAPON);
}

void c_base_entity::update_subclasses()
{
	using fn = void(__fastcall*)(void*);
	patterns::update_subclass.as<fn>()(this);
}