project(MyRaytracer)

add_executable(MyRaytracer "src/main.cpp" "src/vector.h" "src/color.h" "src/ray.h" "src/primitive/hittable.h" "src/primitive/sphere.h" "src/primitive/hittable_list.h" "src/util/my_math.h" "src/camera.h" "src/util/interval.h")