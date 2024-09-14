#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

#include "draw_calls.h"
#include "bones.h"
#include "attachments.h"
#include "hitbox_sets.h"

class c_render_mesh
{
public:
	char pad_0x0000[0x28]; // 0x0000
	vector3d min_bounds; // 0x0028
	vector3d max_bounds; // 0x0034
	int draw_calls_count; // 0x0040
	char pad_0x0044[0x4];	// 0x0044
	c_draw_calls* draw_calls; // 0x0048
	char pad_0x0050[0x68]; // 0x0050
	int skeleton_count; // 0x00B8
	char pad_0x00BC[0x4];	// 0x00BC
	c_bones* skeleton; // 0x00C0
	char pad_0x00C8[0x8];	// 0x00C8
	int hashes_count; // 0x00D0
	char pad_0x00D4[0x4]; // 0x00D4
	uint32_t* hashes; // 0x00D8
	char pad_0x00E0[0x20]; // 0x00E0
	int	bone_wight_count;	// 0x0100
	char pad_0x0104[0xC];	// 0x0104
	c_attachments* attachments; // 0x0110
	int	attachments_count; // 0x0118
	char pad_0x011C[0x1C]; // 0x011C
	c_hitbox_sets* hitbox_sets; // 0x0138
	int hitbox_sets_count; // 0x0140
};