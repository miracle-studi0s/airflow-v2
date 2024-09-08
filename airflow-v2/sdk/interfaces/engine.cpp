#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../math/vector3d.h"
#include "engine.h"

bool c_engine_client::is_in_game()
{
	return vtable::call<bool>(this, IS_IN_GAME);
}

bool c_engine_client::is_connected()
{
	return vtable::call<bool>(this, IS_CONNECTED);
}

int c_engine_client::get_local_player_index()
{
	int index{ -1 };

	vtable::call<void>(this, GET_LOCAL_PLAYER_INDEX, &index, 0);
	index++;

	return index;
}

c_networked_client_info* c_engine_client::get_networked_client_info()
{
	c_networked_client_info networked_client_info{};
	vtable::call<void*>(this, GET_NETWORKED_CLIENT_INFO, &networked_client_info);
	return &networked_client_info;
}