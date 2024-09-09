#pragma once

#include "../utl/hash_map.h"

enum schema_class_info_offsets : uintptr_t
{
    CLASS_NAME = 0x8,
    CLASS_FIELDS_SIZE = 0x1C,
    CLASS_FIELDS_PTR = 0x28,
};

enum schema_type_scope_vfuns : uintptr_t
{
    FIND_DECLARED_CLASS = 2,
};

enum schema_system_vfuncs : uintptr_t
{
    FIND_TYPE_SCOPE_FOR_MODULE = 13,
};

struct schema_class_field_t
{
    const char* name;
    char pad0[0x8];
    short offset;
    char pad1[0xE];
};

class c_schema_class_info
{
public:
    short get_fields_size();
    const char* get_name();
    schema_class_field_t* get_fields();
};

class c_schema_type_scope
{
public:
    c_schema_class_info* find_declared_class(const char* name);
};

class c_schema_system
{
public:
    c_schema_type_scope* find_type_scope_for_module(const char* name);
};