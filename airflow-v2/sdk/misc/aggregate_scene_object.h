#pragma once

#include "../math/color.h"

class c_aggregate_scene_object
{
public:
	char pad_0000[0x38]; // 0x0
	c_byte_color color; // 0x38
	char pad_0038[0x9];
};