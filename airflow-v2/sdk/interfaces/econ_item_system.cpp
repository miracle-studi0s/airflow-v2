#include <fnv1a.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "econ_item_system.h"

bool c_econ_item_definition::is_weapon()
{
	return get_stickers_supported_count() >= 4;
}

bool c_econ_item_definition::is_agent()
{
	constexpr auto type_custom_player = fnv_hash("#Type_CustomPlayer");
	if (fnv_hash(item_type_name) != type_custom_player)
		return false;

	return get_stickers_supported_count() >= 1;
}

bool c_econ_item_definition::is_knife(bool exclude_default)
{
	constexpr auto csgo_type_knife = fnv_hash("#CSGO_Type_Knife");
	if (fnv_hash(item_type_name) != csgo_type_knife)
		return false;

	return exclude_default ? definition_index >= 500 : true;
}

bool c_econ_item_definition::is_glove(bool exclude_default)
{
	constexpr auto type_hands = fnv_hash("#Type_Hands");
	if (fnv_hash(item_type_name) != type_hands)
		return false;

	const bool custom_glove = definition_index != 5028 && definition_index != 5029;
	return exclude_default ? custom_glove : true;
}

bool c_econ_item_definition::is_weapon_case()
{
	constexpr auto type_weapon_case = fnv_hash("#CSGO_Type_WeaponCase");
	return fnv_hash(item_type_name) == type_weapon_case;
}

bool c_econ_item_definition::is_key()
{
	constexpr auto tool_weapon_case_key_tag = fnv_hash("#CSGO_Tool_WeaponCase_KeyTag");
	return fnv_hash(item_type_name) == tool_weapon_case_key_tag;
}

const char* c_econ_item_definition::get_model_name()
{
	return *address{ this }.add(MODEL_NAME).as<const char**>();
}

const char* c_econ_item_definition::get_simple_weapon_name()
{
	return *address{ this }.add(SIMPLE_WEAPON_NAME).as<const char**>();
}

int c_econ_item_definition::get_stickers_supported_count()
{
	return *address{ this }.add(STICKERS_SUPPORTED_COUNT).as<int*>();
}

int c_econ_item_definition::get_loadout_slot()
{
	return *address{ this }.add(LOADOUT_SLOT).as<int*>();
}

c_econ_item_schema* c_econ_item_system::get_econ_item_schema()
{
	return *address{ this }.add(ECON_ITEM_SCHEMA).as<c_econ_item_schema**>();
}