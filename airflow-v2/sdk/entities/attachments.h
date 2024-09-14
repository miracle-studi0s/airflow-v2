#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector4d.h"

class c_attachments
{
public:
	char pad_0x0000[0x10];		  // 0x0000
	const char* key;					  // 0x0010
	char pad_0x0018[0x8];		  // 0x0018
	const char* name;					  // 0x0020
	const char* influence_name[3];	  // 0x0028
	char pad_0x0030[0x10];		  // 0x0030
	vector4d influence_rotations[3]; // 0x0040
	vector3d influence_positons[3];	  // 0x0070
	float influences_count[3];	  // 0x0094
	char pad_0x00A0[0x10];		  // 0x00A0
};