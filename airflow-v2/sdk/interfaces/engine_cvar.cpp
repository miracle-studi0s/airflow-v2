#include <fnv1a.hpp>

#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "engine_cvar.h"

bool c_convar::get_bool() const
{
	return value.i1;
}

int c_convar::get_int() const 
{
	return value.i32;
}

float c_convar::get_float() const
{
	return value.fl;
}

cvar_iterator c_engine_cvar::get_first()
{
	cvar_iterator iterator{ 0 };
	vtable::call<void>(this, GET_FIRST, &iterator);
	return iterator;
}

cvar_iterator c_engine_cvar::get_next(cvar_iterator previous)
{
	cvar_iterator iterator{ 0 };
	vtable::call<void>(this, GET_NEXT, &iterator, previous);
	return iterator;
}

c_convar* c_engine_cvar::find(cvar_iterator iterator)
{
	return vtable::call<c_convar*>(this, FIND, iterator);
}

c_convar* c_engine_cvar::find_by_hash(uint64_t hash)
{
	auto iterator = get_first();

	while (true) 
	{
		auto cvar = find(iterator);
		if (!cvar)
			break;

		if (fnv1a::hash_64(cvar->name) == hash)
			return cvar;

		iterator = get_next(iterator);
	}

	return nullptr;
}

void c_engine_cvar::lock_hidden_vars()
{
	for (auto i : hidden_cvars)
		i->flags |= hidden_cvar_flags;
}

void c_engine_cvar::unlock_hidden_vars()
{
	auto iterator = get_first();

	while (true)
	{
		auto cvar = find(iterator);
		if (!cvar)
			break;

		if (cvar->flags & hidden_cvar_flags)
		{
			hidden_cvars.push_back(cvar);
			cvar->flags &= ~hidden_cvar_flags;
		}

		iterator = get_next(iterator);
	}
}