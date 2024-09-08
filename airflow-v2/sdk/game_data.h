#pragma once

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

	void parse();
}