#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"
#include "player_movement_services.h"

void c_player_movement_services::set_prediction_command(c_user_cmd* cmd)
{
	vtable::call<void>(this, SET_PREDICTION_COMMAND, cmd);
}

void c_player_movement_services::reset_prediction_command()
{
	vtable::call<void>(this, RESET_PREDICTION_COMMAND);
}