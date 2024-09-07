#pragma once

enum source_client_vfuncs
{
	GET_ECON_ITEM_SYSTEM = 123,
	GET_LERP_TIME = 166,
};

class c_econ_item_system;

class c_source_client 
{
public:
	c_econ_item_system* get_econ_item_system();
	float get_lerp_time();
};