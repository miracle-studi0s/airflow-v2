#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "mem_alloc.h"

void* c_mem_alloc::alloc(size_t size)
{
	return vtable::call<void*>(this, ALLOC, size);
}

void* c_mem_alloc::realloc(void* memory, size_t size)
{
	return vtable::call<void*>(this, REALLOC, memory, size);
}

void* c_mem_alloc::free(void* memory)
{
	return vtable::call<void*>(this, FREE, memory);
}