#include <algorithm>

#include "math.h"

namespace math
{
	float rad_to_deg(float radian)
	{
		return radian * 180.f / PI;
	}

	float deg_to_rad(float degree)
	{
		return degree * PI / 180.f;
	}

	float get_fov(vector3d view_angle, vector3d aim_angle)
	{
		vector3d delta = aim_angle - view_angle;
		delta = delta.normalized();
		return std::min(std::sqrtf(std::powf(delta.x, 2.0f) + std::powf(delta.y, 2.0f)), 180.0f);
	}

	void vector_transform(vector3d in1, const matrix3x4_t& in2, vector3d& out)
	{
		out = 
		{ 
			in1.dot_product(vector3d(in2.arr_data[0][0], in2.arr_data[0][1], in2.arr_data[0][2])) + in2.arr_data[0][3],
			in1.dot_product(vector3d(in2.arr_data[1][0], in2.arr_data[1][1], in2.arr_data[1][2])) + in2.arr_data[1][3],
			in1.dot_product(vector3d(in2.arr_data[2][0], in2.arr_data[2][1], in2.arr_data[2][2])) + in2.arr_data[2][3]
		};
	}

	vector3d get_vector_transform(vector3d& in1, const matrix3x4_t& in2)
	{
		return 
		{ 
			in1.dot_product(vector3d(in2.arr_data[0][0], in2.arr_data[0][1], in2.arr_data[0][2])) + in2.arr_data[0][3], 
			in1.dot_product(vector3d(in2.arr_data[1][0], in2.arr_data[1][1], in2.arr_data[1][2])) + in2.arr_data[1][3],
			in1.dot_product(vector3d(in2.arr_data[2][0], in2.arr_data[2][1], in2.arr_data[2][2])) + in2.arr_data[2][3] 
		};
	}

	void vector_to_angles(vector3d forward, vector3d& angles)
	{
		float tmp{}, yaw{}, pitch{};
		if (forward.y == 0.f && forward.x == 0.f)
		{
			yaw = 0.f;
			if (forward.z > 0.f)
				pitch = 270.f;
			else
				pitch = 90.f;
		}
		else
		{
			yaw = (std::atan2f(forward.y, forward.x) * 180.f / PI);
			if (yaw < 0.f)
				yaw += 360.f;

			tmp = std::sqrtf(forward.x * forward.x + forward.y * forward.y);
			pitch = (std::atan2f(-forward.z, tmp) * 180.f / PI);
			if (pitch < 0.f)
				pitch += 360.f;
		}

		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0.f;
	}

	vector3d cross_product(const vector3d& a, const vector3d& b)
	{
		return vector3d(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	void vector_to_angles(vector3d& forward, vector3d& up, vector3d& angles)
	{
		vector3d left = cross_product(up, forward);
		left = left.normalized();

		float forward_dist = forward.length_2d();
		if (forward_dist > 0.001f)
		{
			angles.x = std::atan2f(-forward.z, forward_dist) * 180.f / PI;
			angles.y = std::atan2f(forward.y, forward.x) * 180.f / PI;

			float upz = (left.y * forward.x) - (left.x * forward.y);
			angles.z = std::atan2f(left.z, upz) * 180.f / PI;
		}
		else
		{
			angles.x = std::atan2f(-forward.z, forward_dist) * 180.f / PI;
			angles.y = std::atan2f(-left.x, left.y) * 180.f / PI;
			angles.z = 0;
		}
	}

	void angle_to_vectors(vector3d angles, vector3d& forward)
	{
		float sp{}, sy{}, cp{}, cy{};

		sy = std::sinf(math::deg_to_rad(angles.y));
		cy = std::cosf(math::deg_to_rad(angles.y));

		sp = std::sinf(math::deg_to_rad(angles.x));
		cp = std::cosf(math::deg_to_rad(angles.x));

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	void angle_to_vectors(vector3d angles, vector3d& forward, vector3d& right, vector3d& up)
	{
		float angle{};
		float sp{}, sy{}, cp{}, cy{};

		angle = angles.x * (PI / 180.f);
		sp = std::sinf(angle);
		cp = std::cosf(angle);

		angle = angles.y * (PI / 180.f);
		sy = std::sinf(angle);
		cy = std::cosf(angle);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;

		float sr{}, cr{};
		angle = angles.z * (PI / 180.f);

		sr = std::sinf(angle);
		cr = std::cosf(angle);

		right.x = -1 * sr * sp * cy + -1 * cr * -sy;
		right.y = -1 * sr * sp * sy + -1 * cr * cy;
		right.z = -1 * sr * cp;

		up.x = cr * sp * cy + -sr * -sy;
		up.y = cr * sp * sy + -sr * cy;
		up.z = cr * cp;
	}

	bool is_near_equal(float v1, float v2, float toler)
	{
		return std::abs(v1 - v2) <= std::abs(toler);
	}

	vector3d angle_from_vectors(vector3d a, vector3d b)
	{
		vector3d angles{};

		vector3d delta = a - b;
		float hyp = delta.length_2d();

		// 57.295f - pi in degrees
		angles.y = std::atan(delta.y / delta.x) * 57.2957795131f;
		angles.x = std::atan(-delta.z / hyp) * -57.2957795131f;
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		return angles;
	}

	float angle_diff(float dest, float src)
	{
		float delta = std::fmodf(dest - src, 360.0f);
		if (dest > src)
		{
			if (delta >= 180.f)
				delta -= 360.f;
		}
		else
		{
			if (delta <= -180.f)
				delta += 360.f;
		}
		return delta;
	}

	float interpolate_inversed(float percent, const float& A, const float& B)
	{
		return A + (B - A) * percent;
	}

	float interpolate(const float& from, const float& to, const float& percent)
	{
		return to * percent + from * (1.f - percent);
	}

	vector3d interpolate(vector3d from, vector3d to, const float& percent)
	{
		return to * percent + from * (1.f - percent);
	}

	// thanks to https://www.unknowncheats.me/forum/counterstrike-global-offensive/282111-offscreen-esp.html
	void rotate_triangle_points(vector2d points[3], float rotation)
	{
		const auto points_center = (points[0] + points[1] + points[2]) / vector2d(3.f, 3.f);
		for (int i = 0; i < 3; i++)
		{
			vector2d& point = points[i];

			point -= points_center;

			const auto temp_x = point.x;
			const auto temp_y = point.y;

			const auto theta = rotation;
			const auto c = std::cos(theta);
			const auto s = std::sin(theta);

			point.x = temp_x * c - temp_y * s;
			point.y = temp_x * s + temp_y * c;

			point += points_center;
		}
	}

	float smoothstep_bounds(float edge0, float edge1, float x)
	{
		x = std::clamp<float>((x - edge0) / (edge1 - edge0), 0, 1);
		return x * x * (3 - 2 * x);
	}

	float approach_to_angle(float target, float value, float speed)
	{
		float delta = target - value;

		if (delta > speed)
			value += speed;
		else if (delta < -speed)
			value -= speed;
		else
			value = target;

		return value;
	}

	vector3d approach_to_vector(vector3d target, vector3d value, float speed)
	{
		vector3d diff = (target - value);
		float delta = diff.length();

		if (delta > speed)
			value += diff.normalized() * speed;
		else if (delta < -speed)
			value -= diff.normalized() * speed;
		else
			value = target;

		return value;
	}
}