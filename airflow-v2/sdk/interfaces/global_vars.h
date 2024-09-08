#pragma once

class c_global_vars 
{
public:
    float real_time; //0x0000
    int frame_count; //0x0004
    float absolute_frame_time; //0x0008
    float absolute_frame_start_time_std_dev; //0x000C
    int max_clients; //0x0010
    char pad_0014[0x14]; //0x0014
    void* current_time_update; //0x0028
    float frame_time; //0x0030
    int current_time; //0x0034
    int player_time; //0x0038
    char pad_003C[0x4];
    float N00000236; //0x0040
    char pad_0044[0x4]; //0x0044
    int32_t tick_count; //0x0048
    char pad_004C[0x8]; //0x004C
    float tick_fraction; //0x0054
    void* net_channel; //0x0058
    char pad_0060[0x108]; //0x0060
    void* network_string_table_container; //0x0168
    char pad_0170[0x40]; //0x0170
    char* current_map; //0x01B0
    char* current_map_name; //0x01B8
};