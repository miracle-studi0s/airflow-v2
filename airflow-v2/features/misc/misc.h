#pragma once

#include "../../sdk/sdk.h"

namespace misc
{
	void auto_jump(c_user_cmd* cmd);
	void auto_strafe(c_user_cmd* cmd);
	void rotate_movement(CBaseUserCmdPB* base_user_cmd, float initial_angle, float current_angle);
}