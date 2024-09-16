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

struct hook
{
	void* original{ nullptr };
	void* target{ nullptr };
	void* old_original{ nullptr };
};

enum hook_vfuncs
{
	DX11_PRESENT = 8,
	DX11_RESIZE_BUFFERS = 13,

	DXGI_CREATE_SWAP_CHAIN = 10,

	INPUT_CREATEMOVE = 5,
};

namespace hooks
{
	inline std::vector<hook> hooks{};

	inline void hook_function(void* original, void* target)
	{
		hook new_hook{ original, target, nullptr };
		if (MH_CreateHook(original, target, &new_hook.old_original))
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
				return hk.target == fn;
			});

		if (found_hook != hooks.end())
			return reinterpret_cast<T>(found_hook->old_original);

		return nullptr;
	}

	void initialize();
	void destroy();
}