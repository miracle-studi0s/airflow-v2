#pragma once

#include "../game_data.h"
#include "../math/vector3d.h"
#include "../math/vector4d.h"

#include "strong_handle.h"

class c_model;

class c_transform
{
public:
	vector3d position;
	vector4d rotate;
};

class c_perm_model_ext_part
{
public:
	c_transform transform; // 0x0	
	const char* name; // 0x20	
	int32_t parent; // 0x28	
	uint8_t __pad002c[0x4]; // 0x2c
	c_strong_handle< c_model > ref_model; // 0x30	
};