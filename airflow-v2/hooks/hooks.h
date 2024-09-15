#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <minhook/MinHook.h>

constexpr int MAX_HOOKS = 200;

enum hook_information
{
	HOOK_ORIGINAL,
	HOOK_TARGET,
	HOOK_ORIGINAL_PTR
};

using hook = std::tuple<void*, void*, void*>;

enum hook_vfuncs
{
	DX11_PRESENT = 8,
};

namespace hooks
{
	inline std::vector<hook> hooks{};

	inline void hook_function(void* original, void* target)
	{
		auto new_hook = std::make_tuple(original, target, reinterpret_cast<void*>(0));
		if (MH_CreateHook(original, target, &std::get<HOOK_ORIGINAL_PTR>(new_hook)))
		{
#ifdef _DEBUG
			MessageBoxA(0, "Failed to hook function", 0, 0);
			exit(0);
#endif

			return;
		}

		hooks.emplace_back(new_hook);
	}

	template<typename T>
	inline T find_original(T fn)
	{
		auto found_hook = std::find_if(hooks.begin(), hooks.end(), 
			[&fn](const hook& hk)
			{
				return std::get<HOOK_TARGET>(hk) == fn;
			});

		if (found_hook != hooks.end())
			return reinterpret_cast<T>(std::get<HOOK_ORIGINAL_PTR>(*found_hook));

		return nullptr;
	}

	void initialize();
	void destroy();
}