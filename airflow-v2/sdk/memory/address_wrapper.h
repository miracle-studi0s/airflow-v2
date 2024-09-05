#pragma once

#include <memory>

class address
{
private:
	uintptr_t pointer = 0;

public:
	address(uintptr_t pointer);
};