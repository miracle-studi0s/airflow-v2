#include <Windows.h>
#include <mutex>

#include "render.h"

namespace render
{
	bool initialized{ false };

	HWND window{ NULL };

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	ID3D11RenderTargetView* render_target{ nullptr };

	ImDrawList* draw_list_act{ nullptr };
	ImDrawList* draw_list_rendering{ nullptr };
	ImDrawData draw_data{};

	vector2d screen_size{};

	font test_font{};

	vector2d get_screen_size()
	{
		return screen_size;
	}

	std::mutex render_mutex{};

	bool available()
	{
		return initialized;
	}

	HWND get_window()
	{
		return window;
	}

	ID3D11Device* get_device()
	{
		return device;
	}

	ID3D11DeviceContext* get_device_context()
	{
		return device_context;
	}

	ID3D11RenderTargetView* get_render_target()
	{
		return render_target;
	}

	void init(IDXGISwapChain* swap_chain)
	{
		if (initialized)
			return;

		if (!SUCCEEDED(swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device))))
			return;

		device->GetImmediateContext(&device_context);

		DXGI_SWAP_CHAIN_DESC sd;
		swap_chain->GetDesc(&sd);
		window = sd.OutputWindow;

		ID3D11Texture2D* back_buffer{ nullptr };
		if (!SUCCEEDED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
			return;

		device->CreateRenderTargetView(back_buffer, NULL, &render_target);
		back_buffer->Release();

		ImGui::CreateContext();

		ImGui_ImplDX11_Init(device, device_context);
		ImGui_ImplWin32_Init(window);

		auto& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

		screen_size = io.DisplaySize;

		ImFontConfig cfg{};
		cfg.OversampleH = cfg.OversampleV = 1;
		cfg.PixelSnapH = true;

		io.Fonts->TexGlyphPadding = 2;

		test_font.init(io, "C:\\Windows\\Fonts\\consolab.ttf", 13.f, &cfg);

		io.FontDefault = test_font.imfont;

		ImGui_ImplDX11_CreateDeviceObjects();

		draw_list_act = new ImDrawList(ImGui::GetDrawListSharedData());
		draw_list_rendering = new ImDrawList(ImGui::GetDrawListSharedData());

		initialized = true;
	}

	// reference
	// https://github.com/maecry/asphyxia-cs2/blob/master/cstrike/core/interfaces.cpp
	void reset()
	{
		if (render_mutex.try_lock())
			render_mutex.unlock();

		render_target->Release();
	}

	void reinit(IDXGISwapChain* swap_chain)
	{
		ID3D11Texture2D* back_buffer{ nullptr };
		if (!SUCCEEDED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
			return;

		device->CreateRenderTargetView(back_buffer, NULL, &render_target);
		back_buffer->Release();

		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void destroy()
	{
		if (!initialized)
			return;

		if (render_mutex.try_lock())
			render_mutex.unlock();

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		ImGui::DestroyContext();

		delete draw_list_act;
		delete draw_list_rendering;

		initialized = false;
	}

	void begin()
	{
		if (!initialized)
			return;

		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
		ImGui::NewFrame();

		screen_size = ImGui::GetIO().DisplaySize;
	}

	void end()
	{
		ImGui::EndFrame();
		ImGui::Render();

		device_context->OMSetRenderTargets(1, &render_target, nullptr);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (draw_list_rendering->VtxBuffer.Size > 0) 
		{
			render_mutex.lock();

			ImDrawList* dl = draw_list_rendering;

			draw_data.Valid = true;
			draw_data.CmdLists = &dl;
			draw_data.CmdListsCount = 1;
			draw_data.TotalVtxCount = dl->VtxBuffer.size();
			draw_data.TotalIdxCount = dl->IdxBuffer.size();

			draw_data.DisplayPos = ImVec2{ 0.0f, 0.0f };
			draw_data.DisplaySize = ImVec2{ screen_size.x, screen_size.y };
			draw_data.FramebufferScale = ImVec2{ 1.0f, 1.0f };

			ImGui_ImplDX11_RenderDrawData(&draw_data);

			render_mutex.unlock();
		}
	}

	void begin_draw()
	{
		if (!initialized)
			return;

		draw_data.Valid = false;

		draw_list_act->_ResetForNewFrame();
		draw_list_act->PushClipRect({}, { screen_size.x, screen_size.y });
		draw_list_act->Flags = 0;
	}

	void end_draw()
	{
		if (!initialized)
			return;

		draw_list_act->PopClipRect();

		render_mutex.lock();
		*draw_list_rendering = *draw_list_act;
		draw_list_rendering->Flags = 0;
		render_mutex.unlock();
	}
}