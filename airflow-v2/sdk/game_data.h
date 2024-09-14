#pragma once

#include <Windows.h>
#include <unordered_map>
#include <fnv1a.hpp>

#undef min
#undef max

#define SCHEMA(type, name, hash) \
	type name() \
	{ \
		static auto schema_offset = schemas::find_offset(hash); \
		return *(std::remove_reference_t<type>*)(reinterpret_cast<uintptr_t>(this) + schema_offset);\
	} \

#define OFFSET(type, name, offset) \
	type name() \
	{ \
		return *(std::remove_reference_t<type>*)(reinterpret_cast<uintptr_t>(this) + offset);\
	} \

#define SCHEMA_PTR(type, name, hash) \
	type* name() \
	{ \
		static auto schema_offset = schemas::find_offset(hash); \
		return (std::remove_reference_t<type>*)(reinterpret_cast<uintptr_t>(this) + schema_offset);\
	} \

#define OFFSET_PTR(type, name, offset) \
	type name() \
	{ \
		return (std::remove_reference_t<type>*)(reinterpret_cast<uintptr_t>(this) + offset);\
	} \

class address;

namespace modules
{
	inline HMODULE client{};
	inline HMODULE engine2{};
	inline HMODULE schemasystem{};
	inline HMODULE tier0{};
	inline HMODULE navsystem{};
	inline HMODULE rendersystem{};
	inline HMODULE localize{};
	inline HMODULE scenesystem{};
	inline HMODULE materialsystem2{};
	inline HMODULE resourcesystem{};
	inline HMODULE input_system{};
	inline HMODULE animation_system{};

	void parse();
}

namespace patterns
{
	inline address global_vars{};
	inline address engine_trace{};
	inline address get_surface_data{};
	inline address init_trace{};
	inline address clip_trace_to_player{};
	inline address create_trace{};
	inline address init_trace_info{};
	inline address get_trace_info{};
	inline address trace_shape{};
	inline address clip_ray_entity{};
	inline address entity_system{};
	inline address get_base_entity{};
	inline address get_local_player_pawn{};
	inline address get_local_player_controller{};
	inline address get_highest_entity_index{};
	inline address get_csgo_input{};
	inline address get_view_angles{};
	inline address set_view_angles{};
	inline address update_subclass{};
	inline address set_model{};
	inline address physics_run_think{};
	inline address get_inaccuracy{};
	inline address get_spread{};
	inline address update_accuracy_penalty{};
	inline address get_bone_index{};
	inline address get_bone_flags{};
	inline address get_bone_parent{};
	inline address calc_world_space_bones{};
	inline address set_mesh_group_mask{};

	void parse();
}

namespace schemas
{
	inline std::unordered_map<uint64_t, uintptr_t> offsets{};

	uintptr_t find_offset(uint64_t hash);
	void parse();
}