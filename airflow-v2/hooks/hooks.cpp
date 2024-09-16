#include <d3d11.h>

#include "../sdk/sdk.h"
#include "../render/render.h"

#include "hooks.h"

namespace hooks
{
	static HRESULT present(IDXGISwapChain* swap_chain, uint32_t sync_interval, uint32_t flags)
	{
		static auto original = find_original(&present);

		render::init(swap_chain);

		if (!render::available())
			return original(swap_chain, sync_interval, flags);

		render::begin();
		{

		}
		render::end();

		return original(swap_chain, sync_interval, flags);
	}

	static HRESULT resize_buffers(IDXGISwapChain* swap_chain, uint32_t buffer_count, 
		uint32_t w, uint32_t h, DXGI_FORMAT new_format, uint32_t flags)
	{
		auto original = find_original(&resize_buffers)(swap_chain, buffer_count, w, h, new_format, flags);
		if (SUCCEEDED(original))
			render::reinit(swap_chain);

		return original;
	}

	static HRESULT __stdcall create_swap_chain(IDXGIFactory* factory, IUnknown* device, DXGI_SWAP_CHAIN_DESC* desc, IDXGISwapChain** pp_swap_chain)
	{
		static auto original = find_original(&create_swap_chain);

		render::reset();

		return original(factory, device, desc, pp_swap_chain);
	}

	void initialize()
	{
		MH_Initialize();

		hooks.reserve(MAX_HOOKS);

		volatile auto dx11_swap_chain = **patterns::rendersystem_device.as<uint8_t***>();
		volatile auto swap_chain_ptr = *address{ dx11_swap_chain }.add(0x170).as<IDXGISwapChain**>();
		volatile auto present_vtable_address = vtable::get(swap_chain_ptr, DX11_PRESENT);
		volatile auto resize_buffers_vtable_address = vtable::get(swap_chain_ptr, DX11_RESIZE_BUFFERS);

		hook_function(present_vtable_address, reinterpret_cast<void*>(&present));
		hook_function(resize_buffers_vtable_address, reinterpret_cast<void*>(&resize_buffers));

		// reference
		// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/core/hooks.cpp
		{
			ID3D11Device* device_ptr{ nullptr };
			swap_chain_ptr->GetDevice(__uuidof(ID3D11Device), (void**)&device_ptr);

			IDXGIDevice* dxgi_device = NULL;
			device_ptr->QueryInterface(IID_PPV_ARGS(&dxgi_device));

			IDXGIAdapter* dxgi_adapter = NULL;
			dxgi_device->GetAdapter(&dxgi_adapter);

			IDXGIFactory* dxgi_factory = NULL;
			dxgi_adapter->GetParent(IID_PPV_ARGS(&dxgi_factory));

			volatile auto create_swap_chain_vtable_address = vtable::get(dxgi_factory, DXGI_CREATE_SWAP_CHAIN);
			hook_function(create_swap_chain_vtable_address, reinterpret_cast<void*>(&create_swap_chain));

			dxgi_device->Release();
			dxgi_device = nullptr;

			dxgi_adapter->Release();
			dxgi_adapter = nullptr;

			dxgi_factory->Release();
			dxgi_factory = nullptr;
		}

		for (auto& i : hooks)
			MH_EnableHook(i.original);
	}

	void destroy()
	{
		for (auto& i : hooks)
			MH_DisableHook(i.original);

		MH_Uninitialize();

		hooks.clear();
	}
}