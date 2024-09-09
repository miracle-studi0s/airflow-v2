#pragma once

enum mem_alloc_vfuns
{
	ALLOC = 1,
	REALLOC = 2,
	FREE = 3,
};

class c_mem_alloc 
{
public:
	void* alloc(size_t size);
	void* realloc(void* memory, size_t size);
	void* free(void* memory);
};