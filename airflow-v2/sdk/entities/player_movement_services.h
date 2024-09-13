#pragma once

enum player_movement_services_vfuncs
{
	SET_PREDICTION_COMMAND = 34,
	RESET_PREDICTION_COMMAND = 35,
};

class c_user_cmd;

class c_player_movement_services
{
public:
	SCHEMA(float, max_speed, fnv_hash("CPlayer_MovementServices-m_flMaxSpeed"));
	SCHEMA(float, surface_friction, fnv_hash("CPlayer_MovementServices-m_flSurfaceFriction"));

	void set_prediction_command(c_user_cmd* cmd);
	void reset_prediction_command();
};