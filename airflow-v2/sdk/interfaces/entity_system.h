#pragma once

class address;

class c_entity_system
{
public:
	address get_base_entity(int index);
	address get_local_player_pawn();
	address get_local_player_controller();
	int get_highest_entity_index();
};