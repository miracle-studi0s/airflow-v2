#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_freetype.h>

#include <d3d11.h>

#include "../sdk/math/math.h"

struct font
{
	ImFont* imfont{};
	float size{};

	void init(ImGuiIO& io, const char* path, float font_size, ImFontConfig* cfg) 
	{
		imfont = io.Fonts->AddFontFromFileTTF(path, font_size, cfg, io.Fonts->GetGlyphRangesCyrillic());
		size = font_size;
	}
};

namespace render
{
	bool available();

	HWND get_window();

	ID3D11Device* get_device();
	ID3D11DeviceContext* get_device_context();
	ID3D11RenderTargetView* get_render_target();

	vector2d get_screen_size();

	void init(IDXGISwapChain* swap_chain);
	void reset();
	void reinit(IDXGISwapChain* swap_chain);
	void destroy();

	void begin();
	void end();

	void begin_draw();
	void end_draw();
}