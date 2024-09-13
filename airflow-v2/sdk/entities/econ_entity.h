#pragma once

#include "base_entity.h"

class c_econ_item_view;

class c_attribute_container 
{
public:
	SCHEMA_PTR(c_econ_item_view, item, fnv_hash("C_AttributeContainer->m_Item"));
};

class c_econ_entity : public c_base_entity
{
public:
	SCHEMA(int&, seed, fnv_hash("C_EconEntity->m_nFallbackSeed"));
	SCHEMA(int&, paint_kit, fnv_hash("C_EconEntity->m_nFallbackPaintKit"));
	SCHEMA(int&, stat_track, fnv_hash("C_EconEntity->m_nFallbackStatTrak"));

	SCHEMA(float&, wear, fnv_hash("C_EconEntity->m_flFallbackWear"));

	SCHEMA(uint32_t&, xuid_low, fnv_hash("C_EconEntity->m_OriginalOwnerXuidLow"));
	SCHEMA(uint32_t&, xuid_high, fnv_hash("C_EconEntity->m_OriginalOwnerXuidHigh"));

	SCHEMA_PTR(c_attribute_container, attribute_manager, fnv_hash("C_EconEntity->m_AttributeManager"));
};