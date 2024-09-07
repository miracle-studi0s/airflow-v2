#include "sdk.h"

#include "../dependencies/lazy_importer.hpp"
#include "../dependencies/xor.hpp"

#include <Windows.h>

namespace sdk
{
	namespace modules
	{
		void parse()
		{
			client				= WINCALL(GetModuleHandleA)(xorstr_("client.dll"));
			engine2				= WINCALL(GetModuleHandleA)(xorstr_("engine2.dll"));
			schemasystem		= WINCALL(GetModuleHandleA)(xorstr_("schemasystem.dll"));
			tier0				= WINCALL(GetModuleHandleA)(xorstr_("tier0.dll"));
			navsystem			= WINCALL(GetModuleHandleA)(xorstr_("navsystem.dll"));
			rendersystem		= WINCALL(GetModuleHandleA)(xorstr_("rendersystemdx11.dll"));
			localize			= WINCALL(GetModuleHandleA)(xorstr_("localize.dll"));
			scenesystem			= WINCALL(GetModuleHandleA)(xorstr_("scenesystem.dll"));
			materialsystem2		= WINCALL(GetModuleHandleA)(xorstr_("materialsystem2.dll"));
			resourcesystem		= WINCALL(GetModuleHandleA)(xorstr_("resourcesystem.dll"));
			input_system		= WINCALL(GetModuleHandleA)(xorstr_("inputsystem.dll"));
			animation_system	= WINCALL(GetModuleHandleA)(xorstr_("animationsystem.dll"));
		}
	}

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
	}

	void parse_patterns()
	{

	}

	void initialize()
	{
		modules::parse();

		parse_interfaces();
		parse_patterns();
	}

	void destroy()
	{

	}
}