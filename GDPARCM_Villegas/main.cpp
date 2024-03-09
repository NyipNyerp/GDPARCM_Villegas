#include "main.h"
#include "BaseRunner.h"

#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main()
{
    BaseRunner runner;
    runner.run();
    runner.getFPS();

    //hittable_list world;

    //auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    //world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    //// comment out for P1_stack
    //for (int a = 5; a < 5; a++) { // 100 small spheres (10x10)
    //    for (int b = 5; b < 5; b++) {
    //        auto choose_mat = random_double();
    //        point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

    //        if ((center - point3(4, 0.2, 0)).length() > 0.9) {
    //            shared_ptr<material> sphere_material;

    //            if (choose_mat < 0.8) {
    //                // diffuse
    //                auto albedo = color::random() * color::random();
    //                sphere_material = make_shared<lambertian>(albedo);
    //                world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //            }
    //            else if (choose_mat < 0.95) {
    //                // metal
    //                auto albedo = color::random(0.5, 1);
    //                auto fuzz = random_double(0, 0.5);
    //                sphere_material = make_shared<metal>(albedo, fuzz);
    //                world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //            }
    //            else {
    //                // glass
    //                sphere_material = make_shared<dielectric>(1.5);
    //                world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //            }
    //        }
    //    }
    //}

    ////auto material1 = make_shared<dielectric>(1.5);
    ////world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    ////auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    ////world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    ////auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.5);
    ////world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    ////auto material4 = make_shared<metal>(color(1.0, 1.0, 1.0), 0.0); // Mirror-like sphere
    ////world.add(make_shared<sphere>(point3(0, 1, 2), 1.0, material4));

    //float y = 0.2;
    //shared_ptr<material> sphere_material;
    //for (int i = 0; i < 5; i++)
    //{
    //    point3 center(0, y, 0);
    //    y += 0.4;
    //    std::cout << "y = " << y << std::endl;
    //    // metal
    //    auto albedo = color::random(0.0, 1.0);
    //    auto fuzz = random_double(0.5, 1.0);
    //    sphere_material = make_shared<metal>(albedo, fuzz);
    //    world.add(make_shared<sphere>(center, 0.2, sphere_material));
    //}

    //camera cam;

    //cam.aspect_ratio = 1 / 1;
    //cam.image_width = 1080;
    //cam.samples_per_pixel = 100;
    //cam.max_depth = 50;

    //cam.vfov = 20;
    //cam.lookfrom = point3(13, 2, 3);
    //cam.lookat = point3(0, 0, 0);
    //cam.vup = vec3(0, 1, 0);

    //cam.defocus_angle = 0.5;
    //cam.focus_dist = 10;

    //cam.render(world);
}