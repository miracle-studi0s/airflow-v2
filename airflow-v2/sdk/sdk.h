#pragma once

#ifdef _DEBUG
#define DEBUG_LOG(text, ...) printf(text, __VA_ARGS__)
#define WINCALL(func) func
#else
#define DEBUG_LOG(text)
#define WINCALL(func) LI_FN(func).cached()
#endif

#include "memory/address_wrapper.h"
#include "memory/pattern_search.h"
#include "memory/vtable.h"

#include "interfaces/interfaces.h"

namespace sdk
{
	namespace modules
	{
		inline HMODULE client{};
		inline HMODULE engine2{};
		inline HMODULE schemasystem{};
		inline HMODULE tier0{};
		inline HMODULE navsystem{};
		inline HMODULE rendersystem{};
		inline HMODULE localize{};
		inline HMODULE scenesystem{};
		inline HMODULE materialsystem2{};
		inline HMODULE resourcesystem{};
		inline HMODULE input_system{};
		inline HMODULE animation_system{};

		void parse();
	}

	inline c_source_client* source_client{ nullptr };

	void initialize();
	void destroy();
}