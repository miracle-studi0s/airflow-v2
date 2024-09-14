#pragma once

#include "../math/color.h"

#include "material.h"

class c_scene_object
{
public:
    char pad_0000[184]; //0x0000
    uint8_t r; //0x00B8
    uint8_t g; //0x00B9
    uint8_t b; //0x00BA
    uint8_t a; //0x00BB
    char pad_00BC[196]; //0x00BC
}; //Size: 0x0180

class c_base_scene_object
{
public:
    char pad_0000[24]; //0x0000
    c_scene_object* scene_object; //0x0018
    c_material2* material; //0x0020 
    c_material2* material2; //0x0028
    char pad_0030[16]; //0x0030
    uint8_t r; //0x0040
    uint8_t g; //0x0041
    uint8_t b; //0x0042
    uint8_t a; //0x0043
    char pad_0044[36]; //0x0044
};