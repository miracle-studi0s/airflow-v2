#pragma once

#include "econ_entity.h"

enum base_player_weapon_offsets : uintptr_t
{
	WEAPON_BASE_V_DATA = 0x360,
};

enum base_player_weapon_vfuns
{
	GET_MAX_SPEED = 340,
};

using firing_float_t = float[2];

class c_cs_weapon_base_v_data
{
public:
	SCHEMA(int, damage, fnv_hash("CCSWeaponBaseVData->m_nDamage"));
	SCHEMA(int, bullets, fnv_hash("CCSWeaponBaseVData->m_nNumBullets"));
	SCHEMA(int, weapon_type, fnv_hash("CCSWeaponBaseVData->m_WeaponType"));

	SCHEMA(int32_t, max_clip1, fnv_hash("CBasePlayerWeaponVData->m_iMaxClip1"));
	SCHEMA(int32_t, max_clip2, fnv_hash("CBasePlayerWeaponVData->m_iMaxClip2"));
	SCHEMA(int32_t, default_clip1, fnv_hash("CBasePlayerWeaponVData->m_iDefaultClip1"));
	SCHEMA(int32_t, default_clip2, fnv_hash("CBasePlayerWeaponVData->m_iDefaultClip2"));
	SCHEMA(int32_t, weight, fnv_hash("CBasePlayerWeaponVData->m_iWeight"));

	SCHEMA(float, armor_ratio, fnv_hash("CCSWeaponBaseVData->m_flArmorRatio"));
	SCHEMA(float, range, fnv_hash("CCSWeaponBaseVData->m_flRange"));
	SCHEMA(float, range_modifier, fnv_hash("CCSWeaponBaseVData->m_flRangeModifier"));
	SCHEMA(float, penetration, fnv_hash("CCSWeaponBaseVData->m_flPenetration"));
	SCHEMA(float, headshot_multiplier, fnv_hash("CCSWeaponBaseVData->m_flHeadshotMultiplier"));
	SCHEMA(float, spread, fnv_hash("CCSWeaponBaseVData->m_flSpread"));

	SCHEMA(const char*, name, fnv_hash("CCSWeaponBaseVData->m_szName"));
	SCHEMA(firing_float_t&, cycle_time, fnv_hash("CCSWeaponBaseVData->m_flCycleTime"));
};

class c_base_player_weapon : public c_econ_entity
{
public:
	SCHEMA(bool, in_reload, fnv_hash("C_CSWeaponBase->m_bInReload"));
	SCHEMA(bool, in_burst_mode, fnv_hash("C_CSWeaponBase->m_bBurstMode"));

	SCHEMA(int, burst_shots_remaining, fnv_hash("C_CSWeaponBaseGun->m_iBurstShotsRemaining"));

	SCHEMA(int32_t, clip1, fnv_hash("C_BasePlayerWeapon->m_iClip1"));
	SCHEMA(int32_t, clip2, fnv_hash("C_BasePlayerWeapon->m_iClip2"));

	SCHEMA(int32_t&, next_primary_attack, fnv_hash("C_BasePlayerWeapon->m_nNextPrimaryAttackTick"));
	SCHEMA(int32_t&, next_secondary_attack, fnv_hash("C_BasePlayerWeapon->m_nNextSecondaryAttackTick"));

	SCHEMA(float&, next_secondary_attack_ratio, fnv_hash("C_BasePlayerWeapon->m_flNextSecondaryAttackTickRatio"));
	SCHEMA(float&, next_primary_attack_ratio, fnv_hash("C_BasePlayerWeapon->m_flNextPrimaryAttackTickRatio"));

	OFFSET(c_cs_weapon_base_v_data*, weapon_data, WEAPON_BASE_V_DATA);

	bool is_throwing_nade();

	float get_max_speed();
	float get_inaccuracy();
	float get_spread();

	void update_accuracy_penalty();
};

class c_cs_weapon_base : public c_base_player_weapon
{
public:
	SCHEMA(bool, burst_mode, fnv_hash("C_CSWeaponBase->m_bBurstMode"));
	SCHEMA(int, zoom_level, fnv_hash("C_CSWeaponBaseGun->m_zoomLevel"));
};

class c_base_cs_grenade : public c_cs_weapon_base
{
public:
	SCHEMA(bool, held_by_player, fnv_hash("C_BaseCSGrenade->m_bIsHeldByPlayer"));
	SCHEMA(bool, pin_pulled, fnv_hash("C_BaseCSGrenade->m_bPinPulled"));

	SCHEMA(float, throw_time, fnv_hash("C_BaseCSGrenade->m_fThrowTime"));
	SCHEMA(float, throw_strength, fnv_hash("C_BaseCSGrenade->m_flThrowStrength"));
};