#pragma once

#include <string>

#include "../game_data.h"

#include "hitbox.h"

class c_hitbox_sets
{
public:
	char pad_0x0000[0x20]; // 0x0000
	uint32_t name_hash;		// 0x0020
	char pad_0x0024[0x4];	// 0x0024
	int	hitbox_count;	// 0x0028
	char pad_0x002C[0x4];	// 0x002C
	c_hitbox* hitbox;			// 0x0030
	char pad_0x0038[0x18]; // 0x0038
};