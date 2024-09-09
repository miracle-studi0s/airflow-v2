#include <Windows.h>

#include "sdk.h"

#include "../dependencies/lazy_importer.hpp"
#include "../dependencies/xor.hpp"

namespace sdk
{
	template <typename T = void*>
	T find_interface(HMODULE module_handle, const char* name)
	{
		using fn = T(*)(const char*, int*);
		const auto func = reinterpret_cast<fn>(WINCALL(GetProcAddress)(module_handle, xorstr_("CreateInterface")));
		if (!func)
			return nullptr;

		return func(name, nullptr);
	}

	void parse_interfaces()
	{
		input_system = find_interface<void*>(modules::input_system, xorstr_("InputSystemVersion001"));

		localize = find_interface<c_localize*>(modules::localize, xorstr_("Localize_001"));
		engine_cvar = find_interface<c_engine_cvar*>(modules::tier0, xorstr_("VEngineCvar007"));
		engine_client = find_interface<c_engine_client*>(modules::engine2, xorstr_("Source2EngineToClient001"));
		source_client = find_interface<c_source_client*>(modules::client, xorstr_("Source2Client002"));
		schema_system = find_interface<c_schema_system*>(modules::schemasystem, xorstr_("SchemaSystem_001"));

		network_client_service = find_interface<c_network_client_service*>(modules::engine2, xorstr_("NetworkClientService_001"));

		global_vars = *patterns::global_vars.as<c_global_vars**>();
		engine_trace = *patterns::engine_trace.as<c_engine_trace**>();
		entity_system = *patterns::entity_system.as<c_entity_system**>();

		using fn = c_csgo_input*(__fastcall*)();
		csgo_input = patterns::get_csgo_input.as<fn>()();

		mem_alloc = *reinterpret_cast<c_mem_alloc**>(WINCALL(GetProcAddress)(modules::tier0, xorstr_("g_pMemAlloc")));
	}

	void initialize()
	{
		modules::parse();
		patterns::parse();

		parse_interfaces();
	}

	void destroy()
	{

	}
}