#pragma once

#include <iostream>

#ifdef _DEBUG
#define  DEBUG_LOG(text)
#else
#define DEBUG_LOG(text)
#endif

#include "memory/address_wrapper.h"
#include "memory/pattern_search.h"
#include "memory/vtable.h"

#include "constants.h"
#include "math/math.h"
#include "interfaces/interfaces.h"
#include "entities/entities.h"

#include "game_data.h"

namespace sdk
{
	inline void* input_system{ nullptr };

	inline c_localize* localize{ nullptr };
	inline c_engine_cvar* engine_cvar{ nullptr };
	inline c_engine_client* engine_client{ nullptr };
	inline c_source_client* source_client{ nullptr };
	inline c_schema_system* schema_system{ nullptr };
	inline c_network_client_service* network_client_service{ nullptr };

	inline c_global_vars* global_vars{ nullptr };
	inline c_engine_trace* engine_trace{ nullptr };
	inline c_entity_system* entity_system{ nullptr };

	inline c_csgo_input* csgo_input{ nullptr };

	inline c_mem_alloc* mem_alloc{ nullptr };

	void initialize();
	void destroy();
}