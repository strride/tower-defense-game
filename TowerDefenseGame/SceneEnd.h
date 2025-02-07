#pragma once
#include "Scene.h"

using namespace sf;

class SceneEnd : public Scene
{
public:
	SceneEnd(RenderWindow& renderWindow, Event& event, const int wave, const int score, const int highWave, const int highScore, const bool victory);
	scenes run() override;
	bool init() override;

private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	View view;

	Sprite endGameScreen;
	static const int INSTRUCTIONS_NUMBER = 4;
	Text instructions[INSTRUCTIONS_NUMBER];
	Music themeSong;

	bool isVictory = true;
	int wave;
	int score;
	int highWave;
	int highScore;
};