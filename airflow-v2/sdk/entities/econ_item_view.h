#pragma once

enum econ_item_view_vfuncs
{
	GET_CUSTOM_PAINT_KIT = 2,
	GET_STATIC_ECON_ITEM_DEFINITION = 13,
};

class c_econ_item_definition;

class c_econ_item_view
{
public:
	SCHEMA(bool&, initialized, fnv_hash("C_EconItemView->m_bInitialized"));

	SCHEMA(uint16_t&, item_definition_index, fnv_hash("C_EconItemView->m_iItemDefinitionIndex"));
	SCHEMA(uint64_t&, item_id, fnv_hash("C_EconItemView->m_iItemID"));
	SCHEMA(uint32_t&, item_id_low, fnv_hash("C_EconItemView->m_iItemIDLow"));
	SCHEMA(uint32_t&, item_id_high, fnv_hash("C_EconItemView->m_iItemIDHigh"));
	SCHEMA(uint32_t&, account_id, fnv_hash("C_EconItemView->m_iAccountID"));

	SCHEMA(const char*, custom_name, fnv_hash("C_EconItemView->m_szCustomName"));
	SCHEMA(const char*, custom_name_override, fnv_hash("C_EconItemView->m_szCustomNameOverride"));

	int get_custom_paint_kit();
	c_econ_item_definition* get_econ_item_definition();
};