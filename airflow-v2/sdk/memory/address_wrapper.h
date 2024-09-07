#pragma once

#include <memory>

class address
{
private:
	uintptr_t pointer = 0;

public:
	template<typename T = uintptr_t>
	address(T pointer)
	{
		this->pointer = reinterpret_cast<uintptr_t>(pointer);
	}

	address add(ptrdiff_t offset)
	{
		pointer += offset;
		return *this;
	}

	address sub(ptrdiff_t offset)
	{
		pointer -= offset;
		return *this;
	}

	address deref()
	{
		pointer = *reinterpret_cast<uintptr_t*>(pointer);
		return *this;
	}

	address absolute(int offset, int size)
	{
		pointer += *reinterpret_cast<int32_t*>(pointer + offset);
		pointer += size;

		return *this;
	}

	template<typename T>
	T as()
	{
		return reinterpret_cast<T>(pointer);
	}

	uintptr_t raw()
	{
		return pointer;
	}
};