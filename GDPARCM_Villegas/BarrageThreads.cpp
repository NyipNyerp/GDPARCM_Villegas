#include "BarrageThreads.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "StringUtils.h"
#include "TextureManager.h"
#include <random>

BarrageThreads::BarrageThreads(int id, std::string path, TextureDisplay* texDisplay)
{
	this->id = id;
	this->assetPath = path;
	this->textureDisplay = texDisplay;
}

BarrageThreads::~BarrageThreads()
{
}

void BarrageThreads::run()
{
	std::random_device seed;
	std::mt19937 eng(seed());
	std::uniform_int_distribution<> distr(1000, 5000);

	this->sleep(distr(eng));

	std::vector<std::string> tokens = StringUtils::split(assetPath, '/');
	std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(assetPath, assetName, true);
	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	textureDisplay->spawnObject();

	delete this;
}
