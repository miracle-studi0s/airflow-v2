#pragma once

#include <string>

#include "../game_data.h"

class c_draw_calls
{
public:
	int primitive_types; // 0x0000
	int base_vertex;	  // 0x0004
	int vertex_count;	  // 0x0008
	int start_index;	  // 0x000C
	int index_count;	  // 0x0010
	float uv_density;	  // 0x0014
	float tint_color[3];  // 0x0018
	float alpha;		  // 0x0024
	char pad_0x0028[0xC0]; // 0x0028
};