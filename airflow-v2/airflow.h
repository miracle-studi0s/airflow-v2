#pragma once

#include "sdk/sdk.h"
#include "hooks/hooks.h"
#include "render/render.h"

namespace af
{
	void initialize(HMODULE module);
	void destroy(HMODULE module);
}