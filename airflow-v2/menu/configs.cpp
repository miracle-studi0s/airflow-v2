#include <Windows.h>
#include <lazy_importer.hpp>

#include "configs.h"

#define ADD_BOOL(var) bools[xorstr_(#var)].init(&var);
#define ADD_INT(var) ints[xorstr_(#var)].init(&var);
#define ADD_FLAGS(var) bits[xorstr_(#var)].init(&var);
#define ADD_STRING(var) strings[xorstr_(#var)].init(var);
#define ADD_COLOR(var) colors[xorstr_(#var)].init(&var);
 
namespace configs
{
	using bool_map = std::unordered_map<std::string, config_variable<bool>>;
	using int_map = std::unordered_map<std::string, config_variable<int>>;
	using float_map = std::unordered_map<std::string, config_variable<float>>;
	using flags_map = std::unordered_map<std::string, config_variable<unsigned int>>;
	using color_map = std::unordered_map<std::string, config_variable<c_color>>;
	using string_map = std::unordered_map<std::string, config_variable<std::string>>;

	bool_map bools{};
	int_map ints{};
	float_map floats{};
	flags_map flags{};
	string_map strings{};
	color_map colors{};

	std::string folder{};

	template<typename T>
	void save(T& map, json& values)
	{
		for (auto& i : map)
		{
			auto& cfg = i.second;
			cfg.update();
			values[i.first] = cfg.get();
		}
	}

	template<>
	void save(color_map& map, json& values)
	{
		for (auto& i : map)
		{
			auto& cfg = i.second;
			cfg.update();
			values[i.first] = cfg.get().to_hex();
		}
	}

	template<typename T>
	void load(T& map, json& values)
	{
		for (auto& i : map)
		{
			auto& object = values[i.first];
			if (object.is_null())
				continue;

			auto& cfg = i.second;
			cfg.update_ptr(object);
		}
	}

	template<>
	void load(color_map& map, json& values)
	{
		for (auto& i : map)
		{
			auto& object = values[i.first];
			if (object.is_null())
				continue;

			auto r = static_cast<float>((object & 0xff) >> 24);
			auto g = static_cast<float>((object & 0xff) >> 16);
			auto b = static_cast<float>((object & 0xff) >> 8);
			auto a = static_cast<float>((object & 0xff));

			c_color clr{ r, g, b, a };

			auto& cfg = i.second;
			cfg.update_ptr(clr);
		}
	}

	static bool directory_exist(const TCHAR* dir)
	{
		uintptr_t flag = WINCALL(GetFileAttributesA)(dir);
		if (flag == 0xFFFFFFFFUL)
		{
			if (WINCALL(GetLastError)() == ERROR_FILE_NOT_FOUND)
				return false;
		}

		if (!(flag & FILE_ATTRIBUTE_DIRECTORY))
			return false;

		return true;
	}

	void init_folder()
	{
		folder = xorstr_("airflow\\");
		if (directory_exist(folder.c_str()))
			return;

		WINCALL(CreateDirectoryA)(folder.c_str(), NULL);
	}

	void init_configs()
	{
		ADD_BOOL(g_cfg.auto_jump);
		ADD_BOOL(g_cfg.auto_strafe);

		ADD_BOOL(g_cfg.ui.opened);
	}

	void save(const std::string& name)
	{
		json output{};

		auto& json_bools = output[xorstr_("bools")];
		auto& json_ints = output[xorstr_("ints")];
		auto& json_flags = output[xorstr_("flags")];
		auto& json_clr = output[xorstr_("colors")];
		auto& json_str = output[xorstr_("strings")];

		save(bools, json_bools);
		save(ints, json_ints);
		save(flags, json_flags);
		save(colors, json_clr);
		save(strings, json_str);

		std::string file = folder + name;

		std::ofstream file_out(file);
		if (file_out.good())
			file_out << output;
		file_out.close();
	}

	void load(const std::string& name)
	{
		std::string file = folder + name;
		std::ifstream input_file(file);
		if (!input_file.is_open())
			return;

		auto output = json::parse(input_file);

		auto& json_bools = output[xorstr_("bools")];
		auto& json_ints = output[xorstr_("ints")];
		auto& json_flags = output[xorstr_("flags")];
		auto& json_clr = output[xorstr_("colors")];
		auto& json_str = output[xorstr_("strings")];

		load(bools, json_bools);
		load(ints, json_ints);
		load(flags, json_flags);
		load(colors, json_clr);
		load(strings, json_str);
	}
}