#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "base_model_entity.h"

void c_base_model_entity::set_model(const char* name)
{
	using fn = void* (__fastcall*)(void*, const char*);
	patterns::set_model.as<fn>()(this, name);
}