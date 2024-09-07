#include <string>
#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "network_client_service.h"

bool c_network_client::is_connected()
{
	return std::string_view{ get_map_name() }.find(xorstr_("maps/<empty>.vpk")) == std::string::npos;
}

bool c_network_client::is_predicted()
{
	return *address{ this }.add(IS_PREDICTED).as<bool*>();
}

void c_network_client::set_is_predicted(bool value)
{
	*address{ this }.add(IS_PREDICTED).as<bool*>() = value;
}

int c_network_client::get_client_tick()
{
	return vtable::call<int>(this, GET_CLIENT_TICK);
}

int c_network_client::get_server_tick()
{
	return vtable::call<int>(this, GET_SERVER_TICK);
}

int c_network_client::get_gelta_tick()
{
	return *address{ this }.add(DELTA_TICK).as<int*>();
}

void c_network_client::set_delta_tick(int value)
{
	*address{ this }.add(DELTA_TICK).as<int*>() = value;
}

const char* c_network_client::get_map_name()
{
	return *address{ this }.add(MAP_NAME).as<const char**>();
}

c_network_client* c_network_client_service::get_network_client()
{
	return vtable::call<c_network_client*>(this, GET_NETWORK_CLIENT);
}
