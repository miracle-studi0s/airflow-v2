#include <d3d11.h>
#include <lazy_importer.hpp>

#include "../sdk/sdk.h"
#include "../render/render.h"

#include "../menu/configs.h"
#include "../menu/menu.h"

#include "hooks.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks
{
	WNDPROC wnd_proc_original{ NULL };

	static HRESULT present(IDXGISwapChain* swap_chain, uint32_t sync_interval, uint32_t flags)
	{
		static auto original = find_original(&present);

		render::init(swap_chain);

		if (!render::available())
			return original(swap_chain, sync_interval, flags);

		render::begin();
		{
			menu::render();
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

	static void create_move(c_csgo_input* csgo_input, int slot, bool frame_active)
	{
		static auto original = find_original(&create_move);
		original(csgo_input, slot, frame_active);

		return original(csgo_input, slot, frame_active);
	}

	static bool mouse_input(void* rcx)
	{
		static auto original = find_original(&mouse_input);

		if (cfg::get().ui.opened)
			return false;

		return original(rcx);
	}

	static void* enable_cursor(void* rcx, bool active) 
	{
		static auto original = find_original(&enable_cursor);

		cfg::get().ui.enable_cursor = active;
		if (cfg::get().ui.opened)
			active = false;

		return original(rcx, active);
	}

	static LRESULT wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYUP && wparam == VK_INSERT)
			cfg::get().ui.opened = !cfg::get().ui.opened;

		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
			return true;

		return WINCALL(CallWindowProcA)(wnd_proc_original, hwnd, msg, wparam, lparam);
	}

	static void hook_wnd_proc()
	{
		while (true)
		{
			auto window = render::get_window();
			if (window == NULL)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				continue;
			}

			wnd_proc_original = reinterpret_cast<WNDPROC>(WINCALL(SetWindowLongPtrA)(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc)));

			break;
		}
	}

	static void unhook_wnd_proc()
	{
		auto window = render::get_window();
		WINCALL(SetWindowLongPtrA)(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc_original));
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

		volatile auto createmove_vtable_address = vtable::get(sdk::csgo_input, INPUT_CREATEMOVE);
		volatile auto mouse_input_vtable_address = vtable::get(sdk::csgo_input, INPUT_MOUSE_INPUT);
		hook_function(createmove_vtable_address, reinterpret_cast<void*>(&create_move));
		hook_function(mouse_input_vtable_address, reinterpret_cast<void*>(&mouse_input));

		volatile auto enable_cursor_vtable_address = vtable::get(sdk::input_system, INPUTSYSTEM_ENABLE_CURSOR);
		hook_function(enable_cursor_vtable_address, reinterpret_cast<void*>(&enable_cursor));

		for (auto& i : hooks)
			MH_EnableHook(i.original);

		hook_wnd_proc();
	}

	void destroy()
	{
		static auto enable_cursor_original = find_original(&enable_cursor);
		enable_cursor_original(sdk::input_system, cfg::get().ui.enable_cursor);

		unhook_wnd_proc();

		for (auto& i : hooks)
			MH_DisableHook(i.original);

		MH_Uninitialize();

		hooks.clear();
	}
}