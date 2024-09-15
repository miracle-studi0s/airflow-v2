#pragma once

#include "sdk/sdk.h"
#include "hooks/hooks.h"

namespace af
{
	void initialize(HMODULE module);
	void destroy(HMODULE module);
}