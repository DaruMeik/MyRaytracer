#include "util/my_math.h"

#include "camera.h"
#include "primitive/hittable.h"
#include "primitive/hittable_list.h"
#include "primitive/sphere.h"

#include <iostream>
int main() {
	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

	// Camera
	camera cam;

	cam.image_h = 360;
	cam.image_w = 640;
	cam.samples_per_pixel = 100;

	cam.render(world);
}