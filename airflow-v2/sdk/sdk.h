#pragma once

#ifdef _DEBUG
#define DEBUG_LOG(text, ...) printf(text, __VA_ARGS__)
#define WINCALL(func) func
#else
#define DEBUG_LOG(text)
#define WINCALL(func) LI_FN(func).cached()
#endif

#include "memory/address_wrapper.h"

namespace sdk
{
	void initialize();
	void destroy();
}