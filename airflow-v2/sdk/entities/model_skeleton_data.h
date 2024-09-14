#pragma once

#include "../game_data.h"
#include "../utl/vector.h"
#include "../math/vector3d.h"
#include "../math/vector4d.h"

class c_model_skeleton_data
{
public:
	c_utl_vector< const char* > bone_name; // 0x0	
	char pad[0x8];
	c_utl_vector< int16_t > parnt; // 0x18	
	char pad2[0x8];
	c_utl_vector< float > bone_sphere; // 0x30	
	char pad3[0x8];
	c_utl_vector< std::uint32_t > flag; // 0x48	
	char pad4[0x8];
	c_utl_vector< vector3d > bone_pos_parent; // 0x60	
	char pad5[0x8];
	c_utl_vector< vector4d > bone_rot_parent; // 0x78	
	char pad6[0x8];
	c_utl_vector< float > bonse_scale_parent; // 0x90	
	char pad7[0x8];
};