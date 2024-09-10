#pragma once
#include <cstdint>

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
#define ENT_ENTRY_MASK 0x7FFF
#define NUM_SERIAL_NUM_SHIFT_BITS 15
#define ENT_MAX_NETWORKED_ENTRY 16384

class c_handle
{
public:
	c_handle() noexcept;
	c_handle(const int entry, const int serial) noexcept;
	bool operator!=(const c_handle& other) const noexcept;
	bool operator==(const c_handle& other) const noexcept;
	bool operator<(const c_handle& other) const noexcept;
	bool is_valid() const noexcept;
	int get_entry_index() const noexcept;
	int get_serial_number() const noexcept;
	inline int to_int() const;

private:
	std::uint32_t index;
};