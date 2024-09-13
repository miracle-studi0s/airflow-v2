#include <xor.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "../game_data.h"
#include "econ_item_view.h"

int c_econ_item_view::get_custom_paint_kit()
{
	return vtable::call<int>(this, GET_CUSTOM_PAINT_KIT);
}

c_econ_item_definition* c_econ_item_view::get_econ_item_definition()
{
	return vtable::call<c_econ_item_definition*>(this, GET_STATIC_ECON_ITEM_DEFINITION);
}