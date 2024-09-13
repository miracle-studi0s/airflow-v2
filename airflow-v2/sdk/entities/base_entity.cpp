#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../interfaces/schema_system.h"

#include "base_entity.h"

bool c_base_entity::is_weapon()
{
	return vtable::call<bool>(this, IS_WEAPON);
}