#include <lazy_importer.hpp>
#include <xor.hpp>

#include "memory/address_wrapper.h"
#include "memory/pattern_search.h"

#include "game_data.h"
#include "../sdk/sdk.h"

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
		entity_system = pattern::find(modules::client, xorstr_("48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 54 24 ? E8")).absolute(3, 7);
		get_base_entity = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 8B F8 48 85 C0 74 ? C6 44 24")).absolute(1, 5);
		get_local_player_pawn = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 83 7B")).absolute(1, 5);
		get_local_player_controller = pattern::find(modules::client, xorstr_("E8 ?? ?? ?? ?? 48 85 C0 74 12 8B CB")).absolute(1, 5);
		get_highest_entity_index = pattern::find(modules::client, xorstr_("8B 81 10 15 00"));

		get_csgo_input = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 8B 56 60")).absolute(1, 5);
		get_view_angles = pattern::find(modules::client, xorstr_("4C 8B C1 85 D2 74 08 48 8D 05 ? ? ? ? C3"));
		set_view_angles = pattern::find(modules::client, xorstr_("85 D2 75 3F 48"));

		update_subclass = pattern::find(modules::client, xorstr_("40 53 48 83 EC 30 48 8B 41 10 48 8B D9 8B 50 30"));
		set_model = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 41 8B 54 24 ? 49 8B 0C 24")).absolute(1, 5);
		physics_run_think = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 49 8B D6 48 8B CE E8 ? ? ? ? 48 8B 06")).absolute(1, 5);

		get_inaccuracy = pattern::find(modules::client, xorstr_("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 0F 29 B4 24"));
		get_spread = pattern::find(modules::client, xorstr_("48 83 EC ? 48 63 91"));
		update_accuracy_penalty = pattern::find(modules::client, xorstr_("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84 ? ? ? ? 44 0F 29 44 24"));

		get_bone_index = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 33 DB 89 47 08")).absolute(1, 5);
		get_bone_flags = pattern::find(modules::client, xorstr_("85 D2 78 16 3B 91"));
		get_bone_parent = pattern::find(modules::client, xorstr_("85 D2 78 17 3B 91 78"));

		calc_world_space_bones = pattern::find(modules::client, xorstr_("40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC D0"));
		set_mesh_group_mask = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 8B 5C 24 ? 4C 8B 7C 24 ? 4C 8B 74 24 ?")).absolute(0x1, 0x5);

		rendersystem_device = pattern::find(modules::rendersystem, xorstr_("66 0F 7F 0D ? ? ? ? 66 0F 7F 05 ? ? ? ? 0F 1F 40 00")).absolute(0x4, 0x8);
		should_render_cursor = pattern::find(modules::input_system, xorstr_("E8 ? ? ? ? 48 8B 5C 24 ? 49 8B C6")).absolute(0x1, 0x5);

		create_new_subtick_move_step = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 8B D0 48 8D 4F ? E8 ? ? ? ? 48 8B D0")).absolute(0x1, 0x5);
		add_to_move_step = pattern::find(modules::client, xorstr_("E8 ? ? ? ? 48 8B D0 8B 4A ? F3 41 0F 10 46")).absolute(0x1, 0x5);
	}
}

namespace schemas
{
	std::vector<std::string> dlls
	{
		xorstr_("client.dll"),
		xorstr_("animationsystem.dll"),
	};

	uintptr_t find_offset(uint64_t hash)
	{
		return offsets[hash];
	}

	void parse()
	{
		for (const auto& i : dlls)
		{
			auto type_scope = sdk::schema_system->find_type_scope_for_module(i.c_str());
			if (!type_scope)
				continue;

			auto binding_table = type_scope->get_class_bind_table();
			int count = binding_table.count();
			
			const auto elements = std::make_unique<utl_ts_hash_handle[]>(count);
			const auto elements_size = binding_table.get_elements(0, count, elements.get());

			for (int i = 0; i < elements_size; i++)
			{
				const auto element = elements[i];
				if (!element)
					continue;

				const auto class_binding = binding_table[element];

				if (!class_binding)
					continue;

				c_schema_class_binding_base* declared_class_info = type_scope->find_declared_class(class_binding->get_name());
				if (!declared_class_info)
					continue;

				int size = declared_class_info->get_fields_size();
				if (declared_class_info->get_fields_size() <= 0)
					continue;

				std::string name{};
				for (int j = 0; j < size; j++) 
				{
					const auto fields = declared_class_info->get_fields();

					{
						name = class_binding->get_name();

						name += xorstr_("->");
						name += fields[j].name;
					}

					offsets[fnv_hash(name.c_str())] = fields[j].offset;
				}
			}
		}
	}
}