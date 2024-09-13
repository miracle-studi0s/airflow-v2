#pragma once

#include "base_entity.h"

class c_base_player_controller : public c_base_entity
{
public:
	SCHEMA(bool, is_local_player_controller, fnv_hash("CBasePlayerController->m_bIsLocalPlayerController"));
	SCHEMA(c_handle, pawn, fnv_hash("CBasePlayerController->m_hPawn"));
	SCHEMA(uint32_t, tickbase, fnv_hash("CBasePlayerController->m_nTickbase"));
};

class c_cs_player_controller : public c_base_player_controller
{
public:
	SCHEMA(const char*, sanitized_player_name, fnv_hash("CCSPlayerController->m_sSanitizedPlayerName"));
	SCHEMA(bool, pawn_is_alive, fnv_hash("CCSPlayerController->m_bPawnIsAlive"));

	void physics_run_think();
};