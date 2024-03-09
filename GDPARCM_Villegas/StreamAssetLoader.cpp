#include "StreamAssetLoader.h"
#include "StringUtils.h"
#include "TextureManager.h"
#include "IExecutionEvent.h"
#include "IETThread.h"
#include <vector>
#include <random>

StreamAssetLoader::StreamAssetLoader(int id, String path, IExecutionEvent* executionEvent)
{
	this->workerID = id;
	this->assetPath = path;
	this->execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//std::cout << "Destroying stream asset laoder." << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	//std::cout << "Running stream asset laoder." << std::endl;

	std::random_device seed;
	std::mt19937 eng(seed());
	std::uniform_int_distribution<> distr(500, 1500);

	IETThread::sleep(distr(eng));

	std::vector<std::string> tokens = StringUtils::split(assetPath, '/');
	//std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	std::string assetName = "Frame" + std::to_string(this->workerID+1);
	//std::cout << "AssetID: " << assetName << std::endl;

	TextureManager::getInstance()->instantiateAsTexture(assetPath, assetName, true);
	//std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	this->execEvent->onFinishedExecution();

	delete this;
}
