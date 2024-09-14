#pragma once

#include <string>

#include "../game_data.h"
#include "../math/vector3d.h"

#include "handle.h"
#include "../math/vector3d.h"

class c_player_camera_services
{
public:
	SCHEMA(c_handle, active_post_processing, fnv_hash("CPlayer_CameraServieces->m_hActivePostProcessingVolume"));
	SCHEMA(vector3d, view_punch_angles, fnv_hash("CPlayer_CameraServieces->m_vecCsViewPunchAngle"));
};