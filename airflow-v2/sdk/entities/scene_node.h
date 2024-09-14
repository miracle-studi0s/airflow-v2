#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

#include "skeleton_instance.h"

enum game_scene_node_vfuncs : uintptr_t
{
	GET_SKELETON_INSTANCE = 9,
};

class c_game_scene_node
{
public:
	SCHEMA(vector3d, origin, fnv_hash("CGameSceneNode->m_vecOrigin"));
	SCHEMA(vector3d, abs_origin, fnv_hash("CGameSceneNode->m_vecAbsOrigin"));

	c_skeleton_instance* get_skeleton_instance();
	void set_mesh_group_mask(uint64_t mask);
};