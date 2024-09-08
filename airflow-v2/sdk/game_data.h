#pragma once

#include <Windows.h>

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

	void parse();
}