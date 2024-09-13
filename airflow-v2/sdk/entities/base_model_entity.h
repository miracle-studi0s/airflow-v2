#pragma once

#include "base_entity.h"

class c_base_model_entity : public c_base_entity
{
public:
	SCHEMA(vector3d, view_offset, fnv_hash("C_BaseModelEntity->m_vecViewOffset"));

	void set_model(const char* name);
};