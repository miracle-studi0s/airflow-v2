#pragma once

#include <string>

#include "../game_data.h"
#include "../utl/vector.h"

#include "perm_model_info.h"
#include "render_mesh.h"
#include "model_skeleton_data.h"
#include "perm_model_ext_part.h"

class c_perm_model_data
{
public:
	const char* name;
	c_perm_model_info model_info;
	c_utl_vector<c_perm_model_ext_part> ext_parts;
	c_utl_vector< c_render_mesh* >  ref_meshes;
	char pad2[0x8];
	c_utl_vector< uint64_t > mesh_group_mask;
	char pad3[0x8];
	c_utl_vector< uint64_t > phys_group_mask;
	char pad5[0x30];
	c_utl_vector< void* > anim_groups; // 0x120	
	char pad9[0x70];
	c_model_skeleton_data model_skeleton; // 0x188	
};