#pragma once

#include <array>

class c_cs_player_pawn;

struct ray_t
{
public:
	vector3d start;
	vector3d end;
	vector3d mins;
	vector3d maxs;
	char pad_001[0x4];
	uint8_t type;
};

struct surface_data_t
{
public:
	char pad_001[0x8];
	float penetration_data_modifier;
	float damage_modifier;
	char pad_002[0x4];
	int material;
};

struct trace_hitbox_data_t
{
public:
	char pad_001[0x38];
	int hit_group;
	char pad_002[0x4];
	int hitbox_id;
};

struct trace_array_element_t 
{
	char pad_001[0x30];
};

struct trace_data_t 
{
	int32_t unk1;
	float uk2{ 52.f };

	trace_array_element_t* trace_element_pointer{ };

	int32_t unk3{ 128 };
	int32_t unk4{ static_cast<int32_t>(0x80000000) };

	trace_array_element_t trace_elements[0x80];

	char pad_001[0x8];
	int64_t update_count;
	void* update_pointer;
	char pad_002[0xC8];
	vector3d start;
	vector3d end;
	char pad_003[0x50];
};

struct update_value_t 
{
	float previous_length_modifier;
	float current_length_modifier;
	char pad_001[0x8];
	short handle_index;
	char pad_002[0x6];
};

struct game_trace_t
{
public:
	void* surface;
	c_cs_player_pawn* hit_entity;
	trace_hitbox_data_t* hitbox_data;
	char pad_001[0x38];
	uint32_t contents;
	char pad_002[0x24];
	vector3d start;
	vector3d end;
	vector3d normal;
	vector3d pos;
	char pad_003[0x4];
	float fraction;
	char pad_004[0x6];
	bool all_solid;
	char pad_005[0x4D];

	game_trace_t() = default;

	surface_data_t* get_surface_data();
	int get_hitbox_id() const;
	int get_hit_group() const;
};

struct trace_filter_t
{
public:
	char pad_001[0x8];
	int64_t mask;
	int64_t ptr[2];
	int32_t skip_handle[2];
	int16_t collision_mask[4];
	int16_t ptr2;
	uint8_t layer;
	uint8_t ptr4;
	uint8_t ptr5;

	trace_filter_t() = default;
	trace_filter_t(uint64_t mask, c_cs_player_pawn* entity, c_cs_player_pawn* player, int layer);
};

namespace trace
{
	void init_trace(trace_filter_t& filter, c_cs_player_pawn* pawn, uint64_t mask, uint8_t layer, uint16_t unknown);
	void clip_trace_to_player(vector3d& start, vector3d&& end, trace_filter_t* filter, game_trace_t* trace, float min, int length, float max);
	void create_trace(trace_data_t* trace, vector3d start, vector3d end, const trace_filter_t& filter, int penetration_count);
	void init_trace_info(game_trace_t* hit);
	void get_trace_info(trace_data_t* trace, game_trace_t* hit, const float unknown_float, void* unknown);
}

class c_engine_trace
{
public:
	bool trace_shape(ray_t* ray, vector3d start, vector3d end, trace_filter_t* filter, game_trace_t* game_trace);
	bool clip_ray_entity(ray_t* ray, vector3d start, vector3d end, c_cs_player_pawn* pawn, trace_filter_t* filter, game_trace_t* game_trace);
};