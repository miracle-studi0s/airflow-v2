#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

class c_bones
{
public:
	const char* bone_name;		   // 0x0000
	const char* parent_name;	   // 0x0008
	float bind_pose[12]; // 0x0010
	vector3d center;	   // 0x0040
	vector3d size;		   // 0x004C
	float sphere_radius;  // 0x0058
	char pad_0x005C[0x4];   // 0x005C
};