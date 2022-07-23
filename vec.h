#pragma once
#include <cmath>
class vec3
{
public:
	float x, y, z;
	vec3(float x, float y, float z) :
		x(x),
		y(y),
		z(z)
	{}

	vec3() :
		x(0),
		y(0),
		z(0)
	{}

	vec3 operator+(const vec3& v) const {
		return vec3(
			x + v.x,
			y + v.y,
			z + v.z
		);
	}

	vec3 operator*(const vec3& v) const {
		return vec3(
			x * v.x,
			y * v.y,
			z * v.z
		);
	}

	vec3 operator-(const vec3& v) const {
		return vec3(
			x - v.x,
			y - v.y,
			z - v.z
		);
	}

	vec3 operator/(const vec3& v) const {
		return vec3(
			x / v.x,
			y / v.y,
			z / v.z
		);
	}

	vec3 operator+(float f) const {
		return vec3(
			x + f,
			y + f,
			z + f
		);
	}

	vec3 operator-(float f) const {
		return vec3(
			x - f,
			y - f,
			z - f
		);
	}

	vec3 operator*(float f) const {
		return vec3(
			x * f,
			y * f,
			z * f
		);
	}

	vec3 operator/(float f) const {
		return vec3(
			x / f,
			y / f,
			z / f
		);
	}

	bool isZero() const {
		return (
			x == 0.f &&
			y == 0.f &&
			z == 0.f
		);
	}


	vec3 toAngle() const
	{
		#define pi 3.141592653589793238463f

		return vec3{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / pi),
			std::atan2(y, x) * (180.0f / pi),
			0
		};
	}

	friend std::ostream& operator<<(std::ostream&& os,const vec3& vec);

};

std::ostream& operator<<(std::ostream& os,const vec3& vec) {
	return os << "X : " << vec.x << " -- Y : " << vec.y << " -- Z : " << vec.z;
}

class vec4
{
public:
	float x, y, z,w;
	vec4(float x, float y, float z,float w) :
		x(x),
		y(y),
		z(z),
		w(w)
	{}

	vec4() :
		x(0),
		y(0),
		z(0),
		w(0)
	{}

	vec4 operator+(const vec4& v) const {
		return vec4(
			x + v.x,
			y + v.y,
			z + v.z,
			w + v.w
		);
	}

	vec4 operator*(const vec4& v) const {
		return vec4(
			x * v.x,
			y * v.y,
			z * v.z,
			w * v.w
		);
	}

	vec4 operator-(const vec4& v) const {
		return vec4(
			x - v.x,
			y - v.y,
			z - v.z,
			w - v.w
		);
	}

	vec4 operator/(const vec4& v) const {
		return vec4(
			x / v.x,
			y / v.y,
			z / v.z,
			w / v.w
		);
	}

	vec4 operator+(float f) const {
		return vec4(
			x + f,
			y + f,
			z + f,
			w + f
		);
	}

	vec4 operator-(float f) const {
		return vec4(
			x - f,
			y - f,
			z - f,
			w - f
		);
	}

	vec4 operator*(float f) const {
		return vec4(
			x * f,
			y * f,
			z * f,
			w + f
		);
	}

	vec4 operator/(float f) const {
		return vec4(
			x / f,
			y / f,
			z / f,
			w / f
		);
	}

	bool isZero() const {
		return (
			x == 0.f &&
			y == 0.f &&
			z == 0.f &&
			w == 0.f
			);
	}
};