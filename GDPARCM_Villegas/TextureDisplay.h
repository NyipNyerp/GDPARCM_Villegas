#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include <mutex>

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void onFinishedExecution() override;

	void spawnObject();
	void updateMusicProgressBar();

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;
	typedef std::mutex Mutex;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 10.0f;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0; //int counter = 0; same thing

	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	Mutex guard;
	
};

