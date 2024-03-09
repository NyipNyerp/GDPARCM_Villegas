#pragma once
#include "IETThread.h"
#include "TextureDisplay.h"

class BarrageThreads : public IETThread
{
public:
	BarrageThreads(int id, std::string path, TextureDisplay* texDisplay);
	~BarrageThreads();

private:
	void run() override;

	int id;

	std::string assetPath;
	TextureDisplay* textureDisplay;
};

