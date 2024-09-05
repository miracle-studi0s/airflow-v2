#include "sdk.h"

#include "../dependencies/lazy_importer.hpp"
#include "../dependencies/xor.hpp"

#include <Windows.h>

namespace sdk
{
	template <typename T = void>
	T* create_interface(const char* dll, const char* name)
	{
		const HINSTANCE module_handle = WINCALL(GetModuleHandleA)(dll);
		if (!module_handle)
			return nullptr;

		using fn = T*(*)(const char*, int*);
		const auto func = reinterpret_cast<fn>(WINCALL(GetProcAddress)(module_handle, xorstr_("CreateInterface")));
		if (!func)
			return nullptr;

		return func(name, nullptr);
	}

	void initialize()
	{
		address new_pointer = 0xFFFF;
	}

	void destroy()
	{

	}
}