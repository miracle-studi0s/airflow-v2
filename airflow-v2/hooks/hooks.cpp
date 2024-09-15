#include <d3d11.h>

#include "../sdk/sdk.h"

#include "hooks.h"

namespace hooks
{
	HRESULT present(IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags) 
	{
		static auto original = find_original(&present);

		return original(swap_chain, sync_interval, flags);
	}

	void initialize()
	{
		MH_Initialize();

		hooks.reserve(MAX_HOOKS);

		volatile auto device = **patterns::rendersystem_device.as<uint8_t***>();
		volatile auto swap_chain = *address{ device }.add(0x170).as<IDXGISwapChain**>();
		volatile auto present_vtable_address = vtable::get(swap_chain, DX11_PRESENT);

		hook_function(present_vtable_address, reinterpret_cast<void*>(&present));

		for (auto& i : hooks)
			MH_EnableHook(std::get<HOOK_ORIGINAL>(i));
	}

	void destroy()
	{
		for (auto& i : hooks)
			MH_DisableHook(std::get<HOOK_ORIGINAL>(i));

		MH_Uninitialize();

		hooks.clear();
	}
}