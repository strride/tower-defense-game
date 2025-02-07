#include "Game.h"
#include "ContentPipeline.h"
#include "SceneTitle.h"
#include "SceneTransition.h"
#include "SceneGame.h"
#include "SceneEnd.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"

Game::Game()
{
	renderWindow.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Tower Defense Game");

	renderWindow.setKeyRepeatEnabled(false);
	srand((int)time(0));

	icon.loadFromFile("Ressources\\Sprites\\Misc\\Icon.png");
	renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int Game::run()
{
	if (!ContentPipeline::getInstance().loadContent()) return EXIT_FAILURE;

	Scene::scenes sceneSelector = Scene::scenes::TITLE;
	Scene* activeScene = nullptr;
	int highScore = 0;
	int highWave = 0;
	int score = 0;
	int wave = 0;
	bool victory = false;
	bool restart = false;

	while (true)
	{
		if (sceneSelector == Scene::scenes::EXIT) return EXIT_SUCCESS;
		if (sceneSelector == Scene::scenes::FAIL) return EXIT_FAILURE;

		switch (sceneSelector)
		{
		case Scene::scenes::TITLE:
			activeScene = new SceneTitle(renderWindow, event);
			break;
		case Scene::scenes::TRANSITION:
			if (wave % 2 == 0) 
			{
				activeScene = new SceneTransition(renderWindow, event, SceneGame::getWave(), Scene::scenes::LEVEL2);
			}
			else if (wave % 2 == 1) 
			{
				activeScene = new SceneTransition(renderWindow, event, SceneGame::getWave(), Scene::scenes::LEVEL1);
			}
			break;
		case Scene::scenes::LEVEL1:
			activeScene = new SceneLevel1(renderWindow, event, highScore, restart);
			restart = false;
			break;
		case Scene::scenes::LEVEL2:
			activeScene = new SceneLevel2(renderWindow, event, highScore, restart);
			restart = false;
			break;
		case Scene::scenes::END:
			activeScene = new SceneEnd(renderWindow, event, wave, score, highWave, highScore, victory);
			break;
		}
		
		if (activeScene->init())
		{
			sceneSelector = activeScene->run();

			SceneGame* tempScene = dynamic_cast<SceneGame*>(activeScene);
			if (tempScene != nullptr)
			{
				score = SceneGame::getScore();
				wave = SceneGame::getWave();
				victory = tempScene->isVictory();
				if (score > highScore) highScore = score;
				if (wave > highWave) highWave = wave;
			}

			SceneTitle* tempSceneTitle = dynamic_cast<SceneTitle*>(activeScene);
			if (tempSceneTitle != nullptr)
			{
				restart = true;
			}
		}
		else
		{
			sceneSelector = Scene::scenes::FAIL;
		}		

		delete activeScene;
		activeScene = nullptr;
	}
}