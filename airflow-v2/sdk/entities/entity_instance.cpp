#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../interfaces/schema_system.h"

#include "handle.h"
#include "entity_instance.h"

bool c_entity_identity::is_valid()
{
	return index() != INVALID_EHANDLE_INDEX;
}

int c_entity_identity::get_serial_number()
{
	return index() >> NUM_SERIAL_NUM_SHIFT_BITS;
}

int c_entity_identity::get_entry_index()
{
	if (is_valid())
		return index() & ENT_ENTRY_MASK;

	return ENT_ENTRY_MASK;
}

c_handle c_entity_instance::get_handle()
{
	auto identity = entity_identity();
	if (identity)
		return c_handle(identity->index(), identity->get_serial_number() - (identity->flags() & 1));

	return {};
}

c_schema_class_binding_base* c_entity_instance::get_class_binding_base()
{
	c_schema_class_binding_base* class_binding_base = nullptr;
	vtable::call<void>(this, GET_CLASS_BINDING_BASE, &class_binding_base);
	return class_binding_base;
}

std::string_view c_entity_instance::get_class_name()
{
	const auto class_binding_base = get_class_binding_base();
	if (class_binding_base)
		return class_binding_base->get_name();

	return "";
}

bool c_entity_instance::is_player()
{
	return is_player_pawn() || is_player_controller();
}

bool c_entity_instance::is_player_pawn()
{
	return get_class_name().find(xorstr_("C_CSPlayerPawn")) != std::string::npos;
}

bool c_entity_instance::is_player_controller()
{
	return get_class_name().find(xorstr_("CCSPlayerController")) != std::string::npos;
}