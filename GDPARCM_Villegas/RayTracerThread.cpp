#include "RayTracerThread.h"
#include "camera.h"

RayTracerThread::RayTracerThread(int rowRef, camera* camRef)
{
	this->row = rowRef;
    this->cam = camRef;
    //this->semaphore = semaphoreRef;

    std::cout << "Thread_" << this->row << " has been created...\n";
}

RayTracerThread::~RayTracerThread()
{
}

//bool RayTracerThread::stillRunning()
//{
//    return this->isRunning;
//}

void RayTracerThread::run()
{
    //this->isRunning = true;
    for (int col = 0; col < cam->image_width; ++col) {
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < cam->samples_per_pixel; ++sample) {
            ray r = cam->get_ray(col, row);
            pixel_color += cam->ray_color(r, cam->max_depth, *cam->world);
        }
        std::lock_guard<std::mutex> lock(cam->imageMutex);
        cam->image->setPixel(
            col, 
            row, 
            pixel_color.x(), 
            pixel_color.y(), 
            pixel_color.z(), 
            cam->samples_per_pixel);
    }
    //this->isRunning = false;

    std::cout << "Thread_" << this->row << " has finished...\n";

    cam->threadSemaphore.release();
}
