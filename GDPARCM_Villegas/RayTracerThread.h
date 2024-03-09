#pragma once
#include "IETThread.h"
#include "Semaphore.h"

class camera;

class RayTracerThread : public IETThread
{
public:
	RayTracerThread(int rowRef, camera* camRef);
	~RayTracerThread();

	//bool stillRunning();

private:
	void run() override;

	int row; // id = row
	camera* cam;

	//Semaphore* semaphore;
	//bool isRunning = false;
};

