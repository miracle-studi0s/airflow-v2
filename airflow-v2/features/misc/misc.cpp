#include "../menu/configs.h"
#include "../cmd_proto.h"
#include "misc.h"

namespace misc
{
	void auto_jump(c_user_cmd* cmd)
	{
		auto local_pawn = sdk::entity_system->get_local_player_pawn().as<c_cs_player_pawn*>();
		if (!local_pawn)
			return;

		if (!g_cfg.auto_jump)
			return;

		const auto is_jumping = cmd->button_state.button_state & IN_JUMP;
		if (!is_jumping)
			return;

		cmd->button_state.button_state &= ~IN_JUMP;
		cmd->button_state.button_state2 &= ~IN_JUMP;
		cmd->button_state.button_state3 &= ~IN_JUMP;

		if (local_pawn->flags() & FL_ONGROUND)
		{
			cmd->button_state.button_state |= IN_JUMP;
			cmd->button_state.button_state3 |= IN_JUMP;

			auto cmd_push = cmd_pb::add_subtick_move_step(cmd);
			cmd_push->set_button(IN_JUMP);
			cmd_push->set_pressed(true);
			cmd_push->set_when(0.999f);

			auto cmd_release = cmd_pb::add_subtick_move_step(cmd);
			cmd_release->set_button(IN_JUMP);
			cmd_release->set_pressed(false);
			cmd_release->set_when(0.999f);
		}
	}

	void auto_strafe(c_user_cmd* cmd)
	{
		if (!g_cfg.auto_strafe)
			return;

		auto local_pawn = sdk::entity_system->get_local_player_pawn().as<c_cs_player_pawn*>();
		if (!local_pawn)
			return;

		if (local_pawn->flags() & FL_ONGROUND)
			return;

		auto base_user_cmd = cmd->pb.mutable_base();
		base_user_cmd->set_forwardmove(0.f);

		static float previous_yaw{};
		float strafe_rotation{ 0.f };

		vector3d viewangles = base_user_cmd->viewangles();
		vector3d velocity = local_pawn->abs_velocity();

		float speed = velocity.length_2d();
		float strafe_step = 0.f;
		if (speed > 0.f)
			strafe_step = std::min(90.f, std::asinf(15.f / speed));
		else
			strafe_step = 90.f;

		strafe_step = std::clamp(strafe_step, 0.f, 90.f);

		float yaw_delta = viewangles.y - previous_yaw;
		if (std::fabsf(yaw_delta) < strafe_step)
		{
			static bool change_dir = false;

			if (change_dir)
			{
				strafe_rotation += strafe_step;
				base_user_cmd->set_leftmove(1.f);
			}
			else
			{
				strafe_rotation -= strafe_step;
				base_user_cmd->set_leftmove(-1.f);
			}
		}
		else
		{
			if (yaw_delta < 0.f)
				base_user_cmd->set_leftmove(1.f);
			else if (yaw_delta > 0.f)
				base_user_cmd->set_leftmove(-1.f);
		}

		rotate_movement(base_user_cmd, viewangles.y, strafe_rotation);

		previous_yaw = viewangles.y;
	}

	void rotate_movement(CBaseUserCmdPB* base_user_cmd, float initial_angle, float current_angle)
	{
		const float rotation_angle_rad = math::deg_to_rad(initial_angle - current_angle);
		const float forward_move = base_user_cmd->forwardmove();
		const float side_move = base_user_cmd->leftmove();

		float rotated_forward_move = forward_move * std::cosf(rotation_angle_rad) - side_move * std::sinf(rotation_angle_rad);
		float rotaded_side_move = forward_move * std::sinf(rotation_angle_rad) + side_move * std::cosf(rotation_angle_rad);

		base_user_cmd->set_forwardmove(rotated_forward_move);
		base_user_cmd->set_leftmove(rotaded_side_move);
	}
}