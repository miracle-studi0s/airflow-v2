#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../interfaces/schema_system.h"

#include "model.h"

c_hitbox* c_model::get_hitbox(int index)
{
	if (perm_model_data.ref_meshes.size <= 0)
		return nullptr;

	auto mesh = perm_model_data.ref_meshes.at(0);
	if (!mesh)
		return nullptr;

	auto hitboxsets = mesh->hitbox_sets;
	if (!hitboxsets)
		return nullptr;

	if (hitboxsets[0].hitbox_count <= 0 || index > hitboxsets[0].hitbox_count)
		return nullptr;

	auto& hitbox = hitboxsets[0].hitbox;
	if (!&hitbox)
		return nullptr;

	return &hitbox[index];
}

const char* c_model::get_bone_name(int index)
{
	if (perm_model_data.model_skeleton.bone_name.size <= 0 || perm_model_data.model_skeleton.bone_name.size > index)
		return "root";

	return perm_model_data.model_skeleton.bone_name.at(index);
}

const char* c_model::get_hitbox_name(int index)
{
	auto hitbox = get_hitbox(index);

	if (!hitbox)
		return nullptr;

	return hitbox->name;
}

int c_model::get_max_hitboxes()
{
	if (perm_model_data.ref_meshes.size <= 0)
		return -1;

	auto meshes = perm_model_data.ref_meshes.at(0);
	if (!meshes)
		return -1;

	auto hithoxsets = meshes->hitbox_sets;
	if (!hithoxsets)
		return -1;

	return hithoxsets[0].hitbox_count;
}

uint32_t c_model::get_bone_flags(std::uint32_t index)
{
	using fn_t = uint32_t(__fastcall*)(void*, uint32_t);
	return patterns::get_bone_flags.as<fn_t>()(this, index);
}

int c_model::get_bone_parent(std::uint32_t index)
{
	using fn_t = uint32_t(__fastcall*)(void*, uint32_t);
	return patterns::get_bone_parent.as<fn_t>()(this, index);
}