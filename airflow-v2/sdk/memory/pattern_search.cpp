#include <memory>
#include <vector>

#include "address_wrapper.h"
#include "pattern_search.h"

namespace pattern
{
    static std::vector<int> ida_to_bytes(const std::string_view& pattern)
    {
        std::vector<int> bytes{};

        char* start = const_cast<char*>(pattern.data());
        char* end = const_cast<char*>(pattern.data()) + pattern.size();

        for (char* current = start; current < end; ++current) 
        {
            if (*current == '?') 
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else 
                bytes.push_back(strtoul(current, &current, 16));
        }

        return bytes;
    }

	address find(HMODULE module, const std::string_view& pattern)
	{
        PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(module) + dos_header->e_lfanew);

        auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto pattern_bytes = ida_to_bytes(pattern);
        auto scan_bytes = reinterpret_cast<uint8_t*>(module);

        auto pattern_size = pattern_bytes.size();
        auto pattern_data = pattern_bytes.data();

        for (int i = 0; i < size_of_image - pattern_size; i++) 
        {
            bool found = true;

            for (int j = 0; j < pattern_size; ++j) 
            {
                if (pattern_data[j] == -1)
                    continue;

                if (scan_bytes[i + j] != pattern_data[j]) 
                {
                    found = false;
                    break;
                }
            }

            if (found)
                return &scan_bytes[i];
        }

        return nullptr;
	}
}