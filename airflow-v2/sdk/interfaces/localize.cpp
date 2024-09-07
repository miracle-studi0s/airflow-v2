#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "localize.h"

const char* c_localize::find_key(const char* key)
{
	return vtable::call<const char*>(this, FIND_KEY, key);
}