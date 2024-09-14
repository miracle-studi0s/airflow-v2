#pragma once

#include <string>

#include "../game_data.h"
#include "../math/mat2x4.h"

#include "model.h"

enum skeleton_instance_offsets : uintptr_t
{
	BONE_DATA = 0X80,
	GET_MODEL = 0x210,
};

struct alignas(16) c_bone_data
{
	vector3d pos;
	float scale;
	vector4d rot;
};

class c_model_state 
{
public:
	SCHEMA(c_strong_handle<c_model>, model, fnv_hash("CModelState->m_hModel"));

	OFFSET(c_bone_data*, bone_data, BONE_DATA);
};

class c_skeleton_instance
{
public:
	std::byte pad_003[0x1CC]; //0x0000
	int bone_count; //0x01CC
	std::byte pad_002[0x18]; //0x01D0
	int mask; //0x01E8
	std::byte pad_001[0x4]; //0x01EC
	matrix2x4_t* bone_cache; //0x01F0

	SCHEMA(c_model_state, model_state, fnv_hash("CSkeletonInstance->m_modelState"));
	SCHEMA(uint8_t, hitbox_set, fnv_hash("CSkeletonInstance->m_nHitboxSet"));

	c_model* get_model();
	void calc_world_space_bones(std::uint32_t bone_mask);
};