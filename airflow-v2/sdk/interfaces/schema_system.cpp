#include "../memory/address_wrapper.h"
#include "../memory/vtable.h"

#include "schema_system.h"

short c_schema_class_binding_base::get_fields_size()
{
	return *address{ this }.add(CLASS_FIELDS_SIZE).as<short*>();
}

const char* c_schema_class_binding_base::get_name()
{
	return *address{ this }.add(CLASS_NAME).as<const char**>();
}

schema_class_field_t* c_schema_class_binding_base::get_fields()
{
	return *address{ this }.add(CLASS_FIELDS_PTR).as<schema_class_field_t**>();
}

c_schema_class_binding_base* c_schema_type_scope::find_declared_class(const char* name)
{
	c_schema_class_binding_base* declared_class{ nullptr };
	vtable::call<void>(this, FIND_DECLARED_CLASS, &declared_class, name);
	return declared_class;
}

c_utl_ts_hash<c_schema_class_binding_base*, 256, unsigned int> c_schema_type_scope::get_class_bind_table()
{
	return *address{ this }.add(GET_BINDING_TABLE).as<c_utl_ts_hash<c_schema_class_binding_base*, 256, unsigned int>*>();
}

c_schema_type_scope* c_schema_system::find_type_scope_for_module(const char* name)
{
	return vtable::call<c_schema_type_scope*>(this, FIND_TYPE_SCOPE_FOR_MODULE, name, nullptr);
}