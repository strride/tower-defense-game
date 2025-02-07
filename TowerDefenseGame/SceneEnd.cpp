#include "SceneEnd.h"
#include "ContentPipeline.h"

SceneEnd::SceneEnd(RenderWindow& renderWindow, Event& event, const int wave, const int score, const int highWave, const int highScore, const bool victory) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->wave = wave;
	this->score = score;
	this->highWave = highWave;
	this->highScore = highScore;
	this->isVictory = victory;
}

Scene::scenes SceneEnd::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload()) return scenes::FAIL;

	return transitionToScene;
}

bool SceneEnd::init()
{
	//--Image et musique-------------------------------------------------------------------------//
	if (isVictory)
	{
		if (!themeSong.openFromFile("Ressources\\Sounds\\Music\\VictoryTheme.ogg")) return false;
		endGameScreen.setTexture(ContentPipeline::getInstance().getVictoryScreenTexture());
	}
	else
	{
		if (!themeSong.openFromFile("Ressources\\Sounds\\Music\\EndGameTheme.ogg")) return false;
		endGameScreen.setTexture(ContentPipeline::getInstance().getGameOverScreenTexture());
	}

	//--Pr�paration de la font-------------------------------------------------------------------------//
	instructions[0].setFont(ContentPipeline::getInstance().getComiciFont());
	instructions[0].setCharacterSize(50);
	instructions[0].setOutlineThickness(4.0f);

	if (isVictory)
	{
		instructions[0].setOutlineColor(Color(232, 161, 10, 255));
		instructions[0].setFillColor(Color::Yellow);
	}
	else
	{
		instructions[0].setOutlineColor(Color(93, 31, 4, 255));
		instructions[0].setFillColor(Color::Red);
	}

	//Utilisation du constructeur de copie
	for (int i = 1; i < INSTRUCTIONS_NUMBER; i++) instructions[i] = instructions[0];

	instructions[0].setString("Score - " + std::to_string(score) + " (Wave - " + std::to_string(wave) + ")");
	instructions[1].setString("HighScore - " + std::to_string(highScore) + " (Wave - " + std::to_string(highWave) + ")");
	instructions[2].setString("Press Enter to go back to title screen");
	instructions[3].setString("Press Escape to exit");

	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
		instructions[i].setOrigin(instructions[i].getGlobalBounds().width / 2.0f, instructions[i].getGlobalBounds().height / 2.0f);

	if (isVictory)
	{
		instructions[0].setPosition(SCREEN_WIDTH / 2, 70);
		instructions[1].setPosition(SCREEN_WIDTH / 2, 170);
		instructions[2].setPosition(SCREEN_WIDTH / 2, 850);
		instructions[3].setPosition(SCREEN_WIDTH / 2, 950);
	}
	else
	{
		instructions[0].setPosition(SCREEN_WIDTH / 2, 160);
		instructions[1].setPosition(SCREEN_WIDTH / 2, 310);
		instructions[2].setPosition(SCREEN_WIDTH / 2, 770);
		instructions[3].setPosition(SCREEN_WIDTH / 2, 920);
	}

	themeSong.setLoop(true);
	themeSong.play();

	return true;
}

void SceneEnd::getInputs()
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Enter) 
			{
				transitionToScene = scenes::TITLE;
				isRunning = false;
			}
			if (event.key.code == Keyboard::Escape) 
			{
				transitionToScene = scenes::EXIT;
				isRunning = false;
			}
		}
	}
}

void SceneEnd::update()
{
}

void SceneEnd::draw()
{
	renderWindow.clear();
	renderWindow.draw(endGameScreen);
	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++) renderWindow.draw(instructions[i]);
	renderWindow.display();
}

bool SceneEnd::unload()
{
	return true;
}