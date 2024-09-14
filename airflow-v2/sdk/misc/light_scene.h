#pragma once

#include "../math/color.h"

class c_light_scene
{
public:
	char pad_0000[0xE4]; // 0x0
	c_color color; // 0xE4
};