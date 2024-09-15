#pragma once

#include "../math/vector3d.h"

class c_view_setup 
{
public:
    char pad_0000[0x04D8]; //0x0000
    float fov; //0x04D8
    float viewmodel_fov; //0x04DC
    vector3d origin; //0x04E0
    char pad_04EC[0xC]; //0x04EC
    vector3d angles; //0x04F8
    char pad_0504[0x14]; //0x0504
    float aspect_ratio; //0x0518
};