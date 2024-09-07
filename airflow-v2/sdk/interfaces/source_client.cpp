#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "c_econ_item_system.h"
#include "source_client.h"

c_econ_item_system* c_source_client::get_econ_item_system()
{
	return vtable::call<c_econ_item_system*>(this, GET_ECON_ITEM_SYSTEM);
}

float c_source_client::get_lerp_time()
{
	return vtable::call<float>(this, GET_LERP_TIME);
}
