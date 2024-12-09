#ifndef VECTOR3_H
#define VECTOR3_H

class vec3d {
public:
	// Public members
	double x{}, y{}, z{};

	// Public method
	vec3d() : x{ 0 }, y{ 0 }, z{ 0 } {}
	vec3d(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}

	vec3d operator-() const { return vec3d(-x, -y, -z); }
	
	double operator[](int i) const { 
		switch (i) {
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
		}
	}
	double& operator[](int i) {
		switch (i) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		}
	}

	vec3d& operator+=(const vec3d& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3d& operator*=(double t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	vec3d& operator/=(double t) {
		return *this *= 1/t;
	}

	double length_squared() const{
		return x * x + y * y + z * z;
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	static vec3d random() {
		return vec3d(randomd(), randomd(), randomd());
	}

	static vec3d random(double min, double max) {
		return vec3d(randomd(min, max), randomd(min, max), randomd(min, max));
	}
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3d = vec3d;

inline std::ostream& operator<<(std::ostream& out, const vec3d& v) {
	return out << v.x << " " << v.y << " " << v.z;
}

inline vec3d operator+(const vec3d& v, const vec3d& u) {
	return vec3d(v.x + u.x, v.y + u.y, v.z + u.z);
}
inline vec3d operator-(const vec3d& v, const vec3d& u) {
	return vec3d(v.x - u.x, v.y - u.y, v.z - u.z);
}
inline vec3d operator*(const vec3d& v, double t) {
	return vec3d(v.x * t, v.y * t, v.z * t);
}
inline vec3d operator*(double t, const vec3d& v) {
	return v * t;
}
inline vec3d operator*(const vec3d& v, const vec3d& u) {
	return vec3d(v.x * u.x, v.y * u.y, v.z * u.z);
}
inline vec3d operator/(const vec3d& v, double t) {
	return v * (1 / t);
}
inline double dot(const vec3d& v, const vec3d& u) {
	return v.x * u.x + v.y * u.y + v.z * u.z;
}
inline vec3d cross(const vec3d& v, const vec3d& u) {
	return vec3d(
		v.y * u.z - v.z * u.y,
		v.z * u.x - v.x * u.z,
		v.x * u.y - v.y * u.x
	);
}
inline vec3d normalize(const vec3d& v) {
	if (v.length() == 0)
		return vec3d();
	return v / v.length();
}
inline vec3d random_unit_vector() {
	while (true) {
		auto p = vec3d::random(-1, 1);
		auto lensq = p.length_squared();
		if (1e-160 < lensq && lensq <= 1)
			return p / sqrt(lensq);
	}
}
inline vec3d random_on_hemisphere(const vec3d& normal) {
	vec3d on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}
#endif