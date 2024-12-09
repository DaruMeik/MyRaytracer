#ifndef CAMERA_H
#define CAMERA_H

#include "primitive/hittable.h"

class camera {
public:
	// Public member
	int image_h = 360;
	int image_w = 640;
	int samples_per_pixel = 10;   // Count of random samples for each pixel
	int max_depth = 2;

	// Public method
	void render(const hittable& world) {
		initialize();

		std::cout << "P3\n" << image_w << " " << image_h << "\n255\n";

		for (int j = 0; j < image_h; j++) {
			std::clog << "\rScanlines remaining: " << (image_h - j) << " " << std::flush;
			for (int i = 0; i < image_w; i++) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}
		std::clog << "\rDone.                 \n";
	}
private:
	// Private member
	double aspect_ratio;
	double pixel_samples_scale;
	point3d position;
	point3d pixel00_loc;
	vec3d pixel_delta_u;
	vec3d pixel_delta_v;

	// Private method
	void initialize() {
		// Image
		aspect_ratio = (double)image_w / (double)image_h;
		pixel_samples_scale = 1.0 / samples_per_pixel;

		// Camera
		auto camera_center = point3d(0, 0, 0);
		auto focal_length = 1.0;

		auto viewport_h = 2.0;
		auto viewport_w = viewport_h * (double(image_w) / image_h);

		// Screen coordinate
		auto viewport_u = vec3d(viewport_w, 0., 0.);
		auto viewport_v = vec3d(0., -viewport_h, 0.);

		// Unit per pixel
		pixel_delta_u = viewport_u / (double)image_w;
		pixel_delta_v = viewport_v / (double)image_h;

		// Upper left pixel position
		auto viewport_upper_left =
			position - vec3d(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	ray get_ray(int i, int j) {
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc
			+ ((i + offset.x) * pixel_delta_u)
			+ ((j + offset.y) * pixel_delta_v);

		auto ray_o = position;
		auto ray_d = normalize(pixel_sample - ray_o);

		return ray(ray_o, ray_d);
	}
	
	vec3d sample_square() const {
		// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
		return vec3d(randomd() - 0.5, randomd() - 0.5, 0);
	}

	color ray_color(const ray& r, int depth, const hittable& world) const {
		if (depth <= 0)
			return color(0., 0., 0.);
		hit_record rec;
		if (world.hit(r, interval(0.001, infinity), rec)) {
			vec3d dir = normalize(rec.normal + random_unit_vector());
			return 0.75 * ray_color(ray(rec.p, dir), depth-1, world);
		}

		// Sky-ish background
		vec3d unit_direction = normalize(r.d);
		auto a = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};

#endif