#pragma once

enum localize_vfuncs
{
	FIND_KEY = 17,
};

class c_localize
{
public:
	const char* find_key(const char* key);
};