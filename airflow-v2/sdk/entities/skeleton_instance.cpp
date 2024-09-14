#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "skeleton_instance.h"

c_model* c_skeleton_instance::get_model()
{
	auto ptr = *reinterpret_cast<void**>((uintptr_t)this + GET_MODEL);

	if (!ptr)
		return nullptr;

	return *reinterpret_cast<c_model**>(ptr);
}

void c_skeleton_instance::calc_world_space_bones(std::uint32_t bone_mask)
{
	using fn_t = void(__fastcall*)(void*, std::uint32_t);
	patterns::calc_world_space_bones.as<fn_t>()(this, bone_mask);
}