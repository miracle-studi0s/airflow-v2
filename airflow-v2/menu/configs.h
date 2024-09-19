#pragma once

#include <unordered_map>
#include <fstream>
#include <json/json.h>
#include <xor.hpp>
#include <string>

#include "../sdk/math/color.h"

using json = nlohmann::json;

template<typename T>
struct config_variable
{
    T value{};
    T* ptr{};

    void init(T* b)
    {
        ptr = b;
    }

    void update()
    {
        value = *ptr;
    }

    void update_ptr(T b)
    {
        *ptr = b;
    }

    T get()
    {
        return value;
    }
};

struct cfg
{
    bool auto_jump{ false };
    bool auto_strafe{ false };

    struct
    {
        bool opened{ false };
        bool enable_cursor{ false };
    } ui;
};

inline cfg g_cfg{};

namespace configs
{
	void init_folder();
	void init_configs();

	void save(const std::string& name);
	void load(const std::string& name);
}