#pragma once

#include "vector3d.h"
#include "vector2d.h"
#include "vector4d.h"
#include "color.h"
#include "mat3x4.h"
#include "mat2x4.h"

constexpr auto PI = 3.14f;
constexpr auto INTERVAL_PER_TICK = 0.015625f;

#define TIME_TO_TICKS(TIME) (static_cast<int>(0.5f + TIME / INTERVAL_PER_TICK))
#define TICKS_TO_TIME(TICKS) (INTERVAL_PER_TICK * static_cast<float>(TICKS))

namespace math
{
	float rad_to_deg(float radian);
	float deg_to_rad(float degree);

	float get_fov(vector3d view_angle, vector3d aim_angle);

	vector3d get_vector_transform(vector3d& in1, const matrix3x4_t& in2);
	void vector_transform(vector3d in1, const matrix3x4_t& in2, vector3d& out);

	void vector_to_angles(vector3d forward, vector3d& angles);
	void vector_to_angles(vector3d& forward, vector3d& up, vector3d& angles);
	void angle_to_vectors(vector3d angles, vector3d& forward);
	void angle_to_vectors(vector3d angles, vector3d& forward, vector3d& right, vector3d& up);

	bool is_near_equal(float v1, float v2, float toler);
	vector3d angle_from_vectors(vector3d a, vector3d b);

	float angle_diff(float dest, float src);

	float interpolate_inversed(float percent, const float& A, const float& B);
	float interpolate(const float& from, const float& to, const float& percent);

	void rotate_triangle_points(vector2d points[3], float rotation);

	float smoothstep_bounds(float edge0, float edge1, float x);
	float approach_to_angle(float target, float value, float speed);
	vector3d approach_to_vector(vector3d target, vector3d value, float speed);
}