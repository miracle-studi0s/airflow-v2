#pragma once

#include <string>

#include "../game_data.h"
#include "../math/color.h"

class c_post_processing
{
public:
	SCHEMA(float, min_exposure, fnv_hash("C_PostProcessingVolume->m_flMinExposure"));
	SCHEMA(float, max_exposure, fnv_hash("C_PostProcessingVolume->m_flMaxExposure"));
	SCHEMA(float, exposure_fade_speed_up, fnv_hash("C_PostProcessingVolume->m_flExposureFadeSpeedUp"));
	SCHEMA(float, exposure_fade_speed_down, fnv_hash("C_PostProcessingVolume->m_flExposureFadeSpeedDown"));

	SCHEMA(bool, exposure_control, fnv_hash("C_PostProcessingVolume->m_bExposureControl"));
};