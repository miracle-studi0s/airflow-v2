#include "mat2x4.h"

void matrix2x4_t::set_origin(int index, vector3d vec)
{
	this[index]._11 = vec.x;
	this[index]._12 = vec.y;
	this[index]._13 = vec.z;
}

vector3d matrix2x4_t::get_origin() {
	return vector3d(_11, _12, _13);
}