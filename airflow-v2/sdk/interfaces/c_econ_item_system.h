#pragma once

#include "../utl/map.h"

class c_econ_item_definition
{
public:
	char pad_001[0x8];  // vtable
	void* kv_item; // 0x8
	uint16_t definition_index; // 0x10
	char pad_002[0x1e];
	bool enabled; // 0x30
	char pad_003[0xf];
	uint8_t min_itelevel; // 0x40
	uint8_t max_itelevel; // 0x41
	uint8_t iterarity; // 0x42
	uint8_t itequality; // 0x43
	uint8_t forced_itequality; // 0x44
	uint8_t default_drop_itequality; // 0x45
	uint8_t default_drop_quantity; // 0x46
	char pad_004[0x19];
	uint8_t popularity_seed; // 0x60
	char pad_005[0x7];
	void* portraits_kv; // 0x68
	char* item_base_name; // 0x70
	bool proper_name; // 0x78
	char pad_006[0x7];
	char* item_type_name; // 0x80
	char pad_007[0x8];
	char* item_desc; // 0x90
	uint32_t expiration_time_stamp; // 0x98
	uint32_t creation_time_stamp; // 0x9c
	char* inventory_model; // 0xa0
	char* inventory_image; // 0xa8
	char pad_008[0x18];
	int inventory_image_position[2]; // 0xc8
	int inventory_image_size[2]; // 0xd0
	char* base_display_model; // 0xd8
	bool load_on_demand; // 0xe0
	char pad_009[0x1];
	bool hide_body_groups_deployed_only; // 0xe2
	char pad_010[0x5];
	char* world_display_model; // 0xe8
	char* holstered_model; // 0xf0
	char* world_extra_wearable_model; // 0xf8
	uint32_t sticker_slots; // 0x100
	char pad_011[0x4];
	char* icon_default_image; // 0x108
	bool attach_to_hands; // 0x110
	bool attach_to_hands_vonly; // 0x111
	bool flip_view_model; // 0x112
	bool act_as_wearable; // 0x113
	char pad_012[0x24];
	uint32_t item_type; // 0x138
	char pad_013[0x4];
	char* brass_model_override; // 0x140
	char* zooin_sound_path; // 0x148
	char* zooout_sound_path; // 0x150
	char pad_014[0x18];
	uint32_t sound_material_id; // 0x170
	bool disable_style_selection; // 0x174
	char pad_015[0x13];
	char* particle_file; // 0x188
	char* particle_snapshot_file; // 0x190
	char pad_016[0x40];
	char* item_classname; // 0x1d8
	char* item_log_classname; // 0x1e0
	char* item_icon_classname; // 0x1e8
	char* definition_name; // 0x1f0
	bool hidden; // 0x1f8
	bool should_show_in_armory; // 0x1f9
	bool base_item; // 0x1fa
	bool flexible_loadout_default; // 0x1fb
	bool imported; // 0x1fc
	bool one_per_account_cdkey; // 0x1fd
	char pad_017[0xa];
	char* armory_desc; // 0x208
	char pad_018[0x8];
	char* armory_remap; // 0x218
	char* store_remap; // 0x220
	char* class_token; // 0x228
	char* slot_token; // 0x230
	uint32_t drop_type; // 0x238
	char pad_019[0x4];
	char* holiday_restriction; // 0x240
	uint32_t sub_type; // 0x248
	char pad_020[0xc];
	uint32_t equip_region_mask; // 0x258
	uint32_t equip_region_conflict_mask; // 0x25c
	char pad_021[0x50];
	bool public_item; // 0x2b0
	bool ignore_in_collection_view; // 0x2b1
	char pad_022[0x36];
	int loadout_slot; // 0x2e8
	char pad_023[0x94];

	bool is_weapon();
	bool is_agent();
	bool is_knife(bool exclude_default);
	bool is_glove(bool exclude_default);
	bool is_weapon_case();
	bool is_key();

	const char* get_model_name();
	const char* get_simple_weapon_name();

	int get_stickers_supported_count();
	int get_loadout_slot();
};

struct c_alternate_icon_data
{
	const char* simple_name;
	const char* large_simple_name;
	char pad_001[0x10];
};

struct c_paint_kit
{
	uint64_t id;
	const char* name;
	const char* description_string;
	const char* description_tag;
	char pad_001[0x8];
	const char* pattern;
	const char* normal;
	const char* logo_material;
	char pad_002[0x4];
	uint32_t rarity;
	uint32_t style;
	float rgba_color[4][4];
	float rgba_logo_color[4][4];
	float wear_default;
	float wear_remap_min;
	float wear_remap_max;
	uint8_t fixed_seed;
	uint8_t phong_exponent;
	uint8_t phong_albedo_boost;
	uint8_t phong_intensity;
	float pattern_scale;
	float pattern_offset_x_start;
	float pattern_offset_x_end;
	float pattern_offset_y_start;
	float pattern_offset_y_end;
	float pattern_rotate_start;
	float pattern_rotate_end;
	float logo_scale;
	float logo_offset_x;
	float logo_offset_y;
	float logo_rotation;
	bool ignore_weapon_size_scale;
	char pad_003[0x3];
	uint32_t view_model_exponent_override_size;
	bool only_first_material;
	bool use_normal_model;
	bool use_legacy_model;
	char pad_004[0x1];
	float pearlescent;
	const char* vmt_path;
	char pad_005[0x8];
	const char* composite_material_path;
	void* vmt_overrides;
	char pad_006[0x8];
};

class c_sticker_kit
{
public:
	int id;
	int rarity;
	const char* name;
	const char* description;
	const char* item_name;
	const char* material_path;
	const char* material_path_no_drips;
	const char* inventory_image;
	int tournament_id;
	int tournament_team_id;
	int tournament_player_id;
	bool material_path_is_absolute;
	bool cannot_trade;
	char pad_001[0x2];
	float rotate_start;
	float rotate_end;
	float scale_min;
	float scale_max;
	float wear_min;
	float wear_max;
	const char* icon_url_small;
	const char* icon_url_large;
	void* kv_item;
};

class c_econ_item_schema 
{
public:
	char pad_001[0x128];
	c_utl_map<int, c_econ_item_definition*> sorted_item_definition_map;
	char pad_002[0x128];
	c_utl_map<uint64_t, c_alternate_icon_data> alternate_icons_map;
	char pad_003[0x50];
	c_utl_map<int, c_paint_kit*> paint_kits;
	c_utl_map<int, c_sticker_kit*> sticker_kits;

	static inline constexpr uint64_t get_alternate_icon_key_for_weapon_paint_wear_item(uint16_t def_idx, uint32_t paint_id, uint32_t wear)
	{
		return (def_idx << 16) + (paint_id << 2) + wear;
	}
};

class c_econ_item_system
{
public:
	c_econ_item_schema* get_econ_item_schema();
};