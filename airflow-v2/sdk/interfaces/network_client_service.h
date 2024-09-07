#pragma once

enum network_client_vfuncs
{
	GET_CLIENT_TICK = 5,
	GET_SERVER_TICK = 6,
};

enum network_client_offsets : uintptr_t
{
	IS_PREDICTED = 0xF8,
	MAP_NAME = 0x240,
	DELTA_TICK = 0x25C,
};

enum network_client_service_vfuncs
{
	GET_NETWORK_CLIENT = 23,
};

class c_network_client
{
public:
	bool is_connected();

	bool is_predicted();
	void set_is_predicted(bool value);

	int get_client_tick();
	int get_server_tick();

	int get_gelta_tick();
	void set_delta_tick(int value);

	const char* get_map_name();
};

class c_network_client_service
{
public:
	c_network_client* get_network_client();
};