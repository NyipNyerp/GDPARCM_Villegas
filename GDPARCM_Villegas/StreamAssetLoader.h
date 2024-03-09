#pragma once
#include <iostream>
#include "IWorkerAction.h"

class IExecutionEvent;
class StreamAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;

public:
	StreamAssetLoader(int id, String path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	int workerID;
	String assetPath;
	IExecutionEvent* execEvent;
};