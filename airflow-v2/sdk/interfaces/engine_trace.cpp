#include "../memory/address_wrapper.h"
#include "../memory/pattern_search.h"

#include "../math/math.h"
#include "../game_data.h"

#include "../entities/entities.h"

#include "engine_trace.h"

surface_data_t* game_trace_t::get_surface_data()
{
	using fn = surface_data_t*(__fastcall*)(void*);
	return patterns::get_surface_data.as<fn>()(this);
}

int game_trace_t::get_hitbox_id() const
{
	if (hitbox_data)
		return hitbox_data->hitbox_id;

	return 0;
}

int game_trace_t::get_hit_group() const
{
	if (hitbox_data)
		return hitbox_data->hit_group;

	return 0;
}

trace_filter_t::trace_filter_t(uint64_t mask, c_cs_player_pawn* entity, c_cs_player_pawn* player, int layer)
{
	this->mask = mask;
	this->ptr[0] = ptr[1] = 0;
	this->ptr2 = 7;
	this->layer = layer;
	this->ptr4 = 0x49;
	this->ptr5 = 0;

	if (entity != nullptr)
	{
		skip_handle[0] = entity->get_handle().get_entry_index();
		skip_handle[2] = entity->get_collision_owner_index();
		collision_mask[0] = entity->collision()->collision_mask();
	}

	if (player != nullptr)
	{
		skip_handle[0] = player->get_handle().get_entry_index();
		skip_handle[2] = player->get_collision_owner_index();
		collision_mask[0] = player->collision()->collision_mask();
	}
}

void trace::init_trace(trace_filter_t& filter, c_cs_player_pawn* pawn, uint64_t mask, uint8_t layer, uint16_t unknown)
{
	using fn = trace_filter_t*(__fastcall*)(trace_filter_t&, void*, uint64_t, uint8_t, uint16_t);
	patterns::init_trace.as<fn>()(filter, pawn, mask, layer, unknown);
}

void trace::clip_trace_to_player(vector3d& start, vector3d&& end, trace_filter_t* filter, game_trace_t* trace, float min, int length, float max)
{
	using fn = void(__fastcall*)(vector3d&, vector3d&, trace_filter_t*, game_trace_t*, float, int, float);
	patterns::clip_trace_to_player.as<fn>()(start, end, filter, trace, min, length, max);
}

void trace::create_trace(trace_data_t* trace, vector3d start, vector3d end, const trace_filter_t& filter, int penetration_count)
{
	using fn = void(__fastcall*)(trace_data_t*, vector3d, vector3d, trace_filter_t, void*, void*, void*, void*, int);
	patterns::create_trace.as<fn>()(trace, start, end, filter, nullptr, nullptr, nullptr, nullptr, penetration_count);
}

void trace::init_trace_info(game_trace_t* hit)
{
	using fn = void(__fastcall*)(game_trace_t*);
	patterns::init_trace_info.as<fn>()(hit);
}

void trace::get_trace_info(trace_data_t* trace, game_trace_t* hit, const float unknown_float, void* unknown)
{
	using fn = void(__fastcall*)(trace_data_t*, game_trace_t*, float, void*);
	patterns::get_trace_info.as<fn>()(trace, hit, unknown_float, unknown);
}

bool c_engine_trace::trace_shape(ray_t* ray, vector3d start, vector3d end, trace_filter_t* filter, game_trace_t* game_trace)
{
	using fn = bool(__fastcall*)(c_engine_trace*, ray_t*, vector3d*, vector3d*, trace_filter_t*, game_trace_t*);
	return patterns::trace_shape.as<fn>()(this, ray, &start, &end, filter, game_trace);
}

bool c_engine_trace::clip_ray_entity(ray_t* ray, vector3d start, vector3d end, c_cs_player_pawn* pawn, trace_filter_t* filter, game_trace_t* game_trace)
{
	using fn = bool(__fastcall*)(c_engine_trace*, ray_t*, vector3d*, vector3d*, c_cs_player_pawn*, trace_filter_t*, game_trace_t*);
	return patterns::clip_ray_entity.as<fn>()(this, ray, &start, &end, pawn, filter, game_trace);
}