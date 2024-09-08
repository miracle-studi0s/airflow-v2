#pragma once

enum render_frame_stage : int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE,
	FRAME_RENDER_START,
	FRAME_RENDER_END,
	FRAME_NET_UPDATE_END,
	FRAME_NET_CREATION,
	FRAME_SIMULATE_END
};

enum engine_vfuncs
{
	IS_IN_GAME = 35,
	IS_CONNECTED = 36,

	GET_LOCAL_PLAYER_INDEX = 47,
	GET_NETWORKED_CLIENT_INFO = 176,
};

class c_networked_client_info
{
public:
	char pad_001[0x4];
	int render_tick;
	float render_tick_fraction;
	int player_tick_count;
	float player_tick_fraction;
	char pad_002[0x4];

	struct 
	{
		char pad_022[0xC];
		vector3d* eye_pos;
	} *local_data;

	char pad_003[0x8];
};

class c_engine_client
{
public:
	bool is_in_game();
	bool is_connected();

	int get_local_player_index();

	c_networked_client_info* get_networked_client_info();
};