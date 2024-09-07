#pragma once

#include <Windows.h>
#include <string>

namespace pattern
{ 
	address find(HMODULE module, const std::string_view& pattern);
}