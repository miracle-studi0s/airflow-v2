#pragma once
#include <vector>

enum cvar_flags
{
	FCVAR_NONE = 0,
	FCVAR_UNREGISTERED = (1 << 0),
	FCVAR_DEVELOPMENTONLY = (1 << 1),
	FCVAR_GAMEDLL = (1 << 2),
	FCVAR_CLIENTDLL = (1 << 3),
	FCVAR_HIDDEN = (1 << 4),
	FCVAR_PROTECTED = (1 << 5),
	FCVAR_SPONLY = (1 << 6),
	FCVAR_ARCHIVE = (1 << 7),
	FCVAR_NOTIFY = (1 << 8),
	FCVAR_USERINFO = (1 << 9),
	FCVAR_CHEAT = (1 << 14),
	FCVAR_PRINTABLEONLY = (1 << 10),
	FCVAR_UNLOGGED = (1 << 11),
	FCVAR_NEVER_AS_STRING = (1 << 12),
	FCVAR_REPLICATED = (1 << 13),
	FCVAR_DEMO = (1 << 16),
	FCVAR_DONTRECORD = (1 << 17),
	FCVAR_RELOAD_MATERIALS = (1 << 20),
	FCVAR_RELOAD_TEXTURES = (1 << 21),
	FCVAR_NOT_CONNECTED = (1 << 22),
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23),
	FCVAR_ARCHIVE_XBOX = (1 << 24),
	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25),
	FCVAR_SERVER_CAN_EXECUTE = (1 << 28),
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29),
	FCVAR_CLIENTCMD_CAN_EXECUTE = (1 << 30),
	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};

enum engine_cvar_vfuncs
{
	GET_FIRST = 12,
	GET_NEXT = 13,

	FIND = 37,
};

using cvar_iterator = unsigned long long;

union convar_value
{
	bool i1;
	short i16;
	unsigned short u16;
	int i32;
	unsigned int u32;
	long long i64;
	unsigned long long u64;
	float fl;
	double db;
	const char* sz;
};

class c_convar
{
public:
	const char* name;
	c_convar* next;
	std::byte pad_0008[0x10];
	const char* description;
	unsigned int type;
	unsigned int registered;
	unsigned int flags;
	char padding_2[0x8];
	convar_value value;

	bool get_bool() const;
	int get_int() const;
	float get_float() const;
};

namespace
{
	constexpr auto hidden_cvar_flags = (FCVAR_HIDDEN | FCVAR_DEVELOPMENTONLY);
}

class c_engine_cvar
{
private:
	std::vector<c_convar*> hidden_cvars{};

public:
	cvar_iterator get_first();
	cvar_iterator get_next(cvar_iterator previous);

	c_convar* find(cvar_iterator iterator);
	c_convar* find_by_hash(uint64_t hash);

	void lock_hidden_vars();
	void unlock_hidden_vars();
};