#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record {
public:
	// Public member
	point3d p;
	vec3d normal;
	double t;
	bool front_face;

	// Public method
	void set_face_normal(const ray& r, const vec3d& outward_normal) {
		// Sets the hit record normal vector.
		// NOTE: the parameter `outward_normal` is assumed to have unit length.

		front_face = dot(r.d, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
#endif