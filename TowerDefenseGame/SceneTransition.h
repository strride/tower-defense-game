#pragma once
#include "Scene.h"

using namespace sf;

class SceneTransition : public Scene
{
public:
	SceneTransition(RenderWindow& renderWindow, Event& event, int wave, Scene::scenes nextScene);
	scenes run() override;
	bool init() override;

private:
	static const int SECONDS_OPEN = 3;
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	View view;

	Font font;
	Text message;
	int wave;
	float timer;
	Scene::scenes next;
};