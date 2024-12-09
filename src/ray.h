#ifndef RAY_H
#define RAY_H

#include "vector.h"

class ray {
public:
	// Public member
	point3d o;
	vec3d d;

	// Public method
	ray() {}
	ray(const point3d& o, const vec3d& d) : o{ o }, d{ d } {}

	point3d at(double t) const {
		return o + t * d;
	}
};
#endif