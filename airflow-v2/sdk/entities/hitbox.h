#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

class c_hitbox
{
public:
	char* name; //0x0000
	char* surface_property; //0x0008
	char* bone_name; //0x0010
	vector3d vec_min; //0x0018
	vector3d vec_maxs; //0x0024
	float shape_radius; //0x0030
	uint32_t bone_hash; //0x0034
	int32_t hitgroup; //0x0038
	uint8_t shape_type; //0x003C
	bool translation_only; //0x003D
	char pad_003E[50]; //0x003E
};