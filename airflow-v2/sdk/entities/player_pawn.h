#pragma once

#include "base_entity.h"
#include "player_weapon_services.h"
#include "player_view_model_services.h"
#include "player_item_services.h"
#include "base_player_weapon.h"

enum cs_player_pawn_vfuncs
{
	GET_EYE_POS = 166,
};

class c_econ_item_view;

class c_cs_player_pawn : public c_base_entity
{
public:
	SCHEMA(bool&, is_scoped, fnv_hash("C_CSPlayerPawn->m_bIsScoped"));
	SCHEMA(bool&, need_to_reapply_glove, fnv_hash("C_CSPlayerPawn->m_bNeedToReApplyGloves"));
	SCHEMA(int, armor_value, fnv_hash("C_CSPlayerPawn->m_ArmorValue"));
	SCHEMA(float, last_spawn_time, fnv_hash("C_CSPlayerPawnBase->m_flLastSpawnTimeIndex"));

	SCHEMA(c_player_item_services*, item_services, fnv_hash("C_BasePlayerPawn->m_pItemServices"));
	SCHEMA(c_player_weapon_services*, weapon_services, fnv_hash("C_BasePlayerPawn->m_pWeaponServices"));

	SCHEMA(c_econ_item_view&, econ_glove, fnv_hash("C_CSPlayerPawn->m_EconGloves"));
	SCHEMA(c_player_view_model_services*, view_model_services, fnv_hash("C_CSPlayerPawnBase->m_pViewModelServices"));

	bool is_alive();
	bool has_armor(int hitgroup);

	int get_bone_index(const char* name);
	uint32_t get_collision_owner_index();

	vector3d get_eye_pos();

	c_base_player_weapon* get_active_weapon();
};