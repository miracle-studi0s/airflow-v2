#pragma once

#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

class c_perm_model_info
{
public:
	uint32_t flags; // 0x0	
	vector3d hull_min; // 0x4	
	vector3d hull_max; // 0x10	
	vector3d view_min; // 0x1c	
	vector3d view_max; // 0x28	
	float mass; // 0x34	
	vector3d eye_position; // 0x38	
	float max_eye_deflection; // 0x44	
	const char* surface_property; // 0x48
};