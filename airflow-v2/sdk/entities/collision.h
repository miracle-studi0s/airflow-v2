#pragma once

#include <string>
#include <fnv1a.hpp>

#include "../game_data.h"
#include "../math/vector3d.h"

enum collision_offsets : uintptr_t
{
	COLLISION_MASK = 0x38,
};

class c_collision
{
public:
	SCHEMA(vector3d, mins, fnv_hash("CCollisionProperty->m_vecMins"));
	SCHEMA(vector3d, maxs, fnv_hash("CCollisionProperty->m_vecMaxs"));
	SCHEMA(uint8_t, solid_flags, fnv_hash("CCollisionProperty->m_usSolidFlags"));
	SCHEMA(uint8_t, collision_group, fnv_hash("CCollisionProperty->m_CollisionGroup"));
	OFFSET(uint16_t, collision_mask, COLLISION_MASK);
};