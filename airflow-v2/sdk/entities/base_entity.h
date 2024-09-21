#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

#include "handle.h"
#include "entity_instance.h"
#include "scene_node.h"

class c_collision;

enum base_entity_instance_vfuncs : uintptr_t
{
	IS_WEAPON = 156,
};

class c_base_entity : public c_entity_instance
{
public:
	SCHEMA(int, team_num, fnv_hash("C_BaseEntity->m_iTeamNum"));
	SCHEMA(c_handle, owner_entity, fnv_hash("C_BaseEntity->m_hOwnerEntity"));
	SCHEMA(int, flags, fnv_hash("C_BaseEntity->m_fFlags"));
	SCHEMA(int, move_type, fnv_hash("C_BaseEntity->m_MoveType"));
	SCHEMA(int, actual_move_type, fnv_hash("C_BaseEntity->m_nActualMoveType"));
	SCHEMA(int, health, fnv_hash("C_BaseEntity->m_iHealth"));
	SCHEMA(vector3d, velocity, fnv_hash("C_BaseEntity->m_vecVelocity"));
	SCHEMA(vector3d, abs_velocity, fnv_hash("C_BaseEntity->m_vecAbsVelocity"));
	SCHEMA(c_collision*, collision, fnv_hash("C_BaseEntity->m_pCollision"));
	SCHEMA(uint32_t, subclass_id, fnv_hash("C_BaseEntity->m_nSubclassID"));
	SCHEMA(c_game_scene_node*, game_scene_node, fnv_hash("C_BaseEntity->m_pGameSceneNode"));

	bool is_weapon();
	void update_subclasses();
};