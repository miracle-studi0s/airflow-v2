#pragma once

#include <string>

#include "../game_data.h"
#include "../math/color.h"

#include "base_entity.h"

class c_env_sky : public c_base_entity
{
public:
	SCHEMA(c_byte_color, tint_color, fnv_hash("C_EnvSky->m_vTintColor"));
	SCHEMA(float, brightness_scale, fnv_hash("C_EnvSky->m_flBrightnessScale"));
	SCHEMA(int, fog_type, fnv_hash("C_EnvSky->m_nFogType"));
};