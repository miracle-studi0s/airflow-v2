#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "scene_node.h"

c_skeleton_instance* c_game_scene_node::get_skeleton_instance()
{
    return vtable::call<c_skeleton_instance*>(this, GET_SKELETON_INSTANCE);
}

void c_game_scene_node::set_mesh_group_mask(uint64_t mask)
{
    using fn_t = void(__fastcall*)(void*, uint64_t);
    patterns::set_mesh_group_mask.as<fn_t>()(this, mask);
}