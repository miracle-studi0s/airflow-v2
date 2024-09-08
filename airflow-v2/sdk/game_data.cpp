#include <lazy_importer.hpp>
#include <xor.hpp>

#include "memory/address_wrapper.h"
#include "memory/pattern_search.h"

#include "game_data.h"

namespace modules
{
	void parse()
	{
		client			= WINCALL(GetModuleHandleA)(xorstr_("client.dll"));
		engine2			= WINCALL(GetModuleHandleA)(xorstr_("engine2.dll"));
		schemasystem	= WINCALL(GetModuleHandleA)(xorstr_("schemasystem.dll"));
		tier0			= WINCALL(GetModuleHandleA)(xorstr_("tier0.dll"));
		navsystem		= WINCALL(GetModuleHandleA)(xorstr_("navsystem.dll"));
		rendersystem	= WINCALL(GetModuleHandleA)(xorstr_("rendersystemdx11.dll"));
		localize		= WINCALL(GetModuleHandleA)(xorstr_("localize.dll"));
		scenesystem		= WINCALL(GetModuleHandleA)(xorstr_("scenesystem.dll"));
		materialsystem2 = WINCALL(GetModuleHandleA)(xorstr_("materialsystem2.dll"));
		resourcesystem	= WINCALL(GetModuleHandleA)(xorstr_("resourcesystem.dll"));
		input_system	= WINCALL(GetModuleHandleA)(xorstr_("inputsystem.dll"));
		animation_system = WINCALL(GetModuleHandleA)(xorstr_("animationsystem.dll"));
	}
}

namespace patterns
{
	void parse()
	{
		global_vars = pattern::find(modules::client, xorstr_("48 89 0D ? ? ? ? 48 89 41")).absolute(3, 7);
		engine_trace = pattern::find(modules::client, xorstr_("4C 8B 3D ? ? ? ? 24 ? 0C ? 66 0F 7F 45 ? 49 8B CE")).absolute(3, 7);
		get_surface_data = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 85 C0 74 ? 44 38 60")).absolute(1, 5);
		init_trace = pattern::find(modules::client, xorstr_("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 0F B6 41 37 33"));
		clip_trace_to_player = pattern::find(modules::client, xorstr_("48 8B C4 55 56 48 8D A8 58"));
		create_trace = pattern::find(modules::client, xorstr_("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 41 56 41 57 48 83 EC 40 F2"));
		init_trace_info = pattern::find(modules::client, xorstr_("48 89 5C 24 08 57 48 83 EC 20 48 8B D9 33 FF 48 8B 0D"));
		get_trace_info = pattern::find(modules::client, xorstr_("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 60 48 8B E9 0F"));
		trace_shape = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 80 7D ? ? 75 ? F3 0F 10 45")).absolute(1, 5);
		clip_ray_entity = pattern::find(modules::client, xorstr_("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 81 EC C0 00 00 00 48 8B 9C"));
	}
}