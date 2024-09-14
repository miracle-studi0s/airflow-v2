#pragma once

#include "../protobuf/cs_user_cmd.pb.h"
#include "../protobuf/user_cmd.pb.h"

class c_in_button_state
{
public:
    char pad_0000[8]; //0x0000
    uint64_t button_state; //0x0008
    uint64_t button_state2; //0x0010
    uint64_t button_state3; //0x0018
};

class c_user_cmd
{
public:
    char pad_valve_shizo[0x10];
    c_csgo_user_cmd_pb pb;
    c_in_button_state button_state; //0x0040
    char pad_0068[0x8]; //0x0068
    uint32_t random_seed; //0x0070
    float current_time;//0x0074
    char pad_78[16];//0x0078
};

class c_subitck_moves
{
public:
    float when; //0x0000
    float delta; //0x0004
    uint64_t button; //0x0008
    bool pressed; //0x0010
    char pad_0011[7]; //0x0011
};

class c_cs_input_moves
{
public:
    uint64_t current_bits; //0x0000
    char pad_0008[24]; //0x0008
    float forward_move; //0x0020
    float side_move; //0x0024
    char pad_0028[16]; //0x0028
    float fraction; //0x0038
    char pad_003C[4]; //0x003C
    int32_t last_buttons; //0x0040
    char pad_0044[4]; //0x0044
    bool in_move; //0x0048
    char pad_0074[255]; //0x0074
    vector3d view_angles; //0x0158
    char pad_0164[48]; //0x0164
}; 

class c_csgo_input
{
public:
    char pad_0000[592]; //0x0000
    c_user_cmd commands[150]; //0x0250
    c_user_cmd global_command; //0x5B60
    bool block_shot; //0x5BF8
    bool in_third_person; //0x5BF9
    char pad_5BFA[6]; //0x5BFA
    vector3d third_person_angles; //0x5C00
    char pad_5C0C[16]; //0x529C
    int32_t sequence_number; //0x5C1C
    float real_time; //0x5CD0

    vector3d get_view_angles();
    void set_view_angles(vector3d& value);

    c_user_cmd* get_user_cmd();
    c_user_cmd* get_next_user_cmd();
};