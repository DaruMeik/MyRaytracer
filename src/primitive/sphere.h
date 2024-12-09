#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
	// Public member
	point3d origin;
	double radius;

	// Public method
	sphere(const point3d& origin, double radius) : origin{ origin }, radius{ std::fmax(0, radius) } {};
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		vec3d oc = origin - r.o;
		double a = r.d.length_squared();
		double b = dot(r.d, oc);
		double c = oc.length_squared() - radius * radius;
		auto discriminant = b * b - a * c;
		if (discriminant < 0)
			return false;
		
		auto sqrtd = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (b - sqrtd) / a;
		if (!ray_t.surrounds(root)) {
			root = (b + sqrtd) / a;
			if (!ray_t.surrounds(root))
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3d outward_normal = (rec.p - origin) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
};
#endif