#pragma once

#include <string>

#include "../game_data.h"

enum entity_instance_vfuncs : uintptr_t
{
	GET_CLASS_BINDING_BASE = 38,
};

class c_schema_class_binding_base;
class c_handle;

class c_entity_identity
{
public:
	SCHEMA(uint32_t, flags, fnv_hash("CEntityIdentity->m_flags"));

	OFFSET(int, index, 0x10);

	bool is_valid();
	int get_serial_number();
	int get_entry_index();
};

class c_entity_instance
{
public:
	SCHEMA(c_entity_identity*, entity_identity, fnv_hash("CEntityInstance->m_pEntity"));

	template<typename T>
	T as()
	{
		return reinterpret_cast<T*>(this);
	}

	c_handle get_handle();
	c_schema_class_binding_base* get_class_binding_base();

	std::string_view get_class_name();

	bool is_player();
	bool is_player_pawn();
	bool is_player_controller();
};