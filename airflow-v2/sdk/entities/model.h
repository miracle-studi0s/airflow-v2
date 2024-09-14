#pragma once

#include <string>

#include "../game_data.h"

#include "perm_model_data.h"

class c_model
{
public:
	void* vtable;
	c_perm_model_data perm_model_data;

	c_hitbox* get_hitbox(int index);
	const char* get_bone_name(int index);
	const char* get_hitbox_name(int index);
	int get_max_hitboxes();
	uint32_t get_bone_flags(std::uint32_t index);
	int get_bone_parent(std::uint32_t index);
};