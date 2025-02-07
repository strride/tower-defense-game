#include "SceneTransition.h"
#include "ContentPipeline.h"

SceneTransition::SceneTransition(RenderWindow& renderWindow, Event& event, int wave, Scene::scenes nextScene) : Scene(renderWindow, event)
{
	view = renderWindow.getDefaultView();
	this->wave = wave;
	this->next = nextScene;
}

Scene::scenes SceneTransition::run()
{
	while (isRunning)
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	return transitionToScene;
}

bool SceneTransition::init()
{
	timer = 0;
	message.setString("Wave " + std::to_string(this->wave));
	message.setCharacterSize(80);
	
	//message.setString("Minions of the Dark Lord march on our lands.\n\n             Defend the King's Tower!\n\n                           Wave 1");
	//message.setCharacterSize(60);

	message.setFont(ContentPipeline::getInstance().getComiciFont());
	message.setColor(Color::White);
	message.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
	return true;
}

void SceneTransition::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();
	}
}

void SceneTransition::update()
{
	timer += Scene::getDeltaTime();
	if (timer >= SECONDS_OPEN)
	{
		isRunning = false;
		transitionToScene = next;
	}
}

void SceneTransition::draw()
{
	renderWindow.clear();
	renderWindow.draw(message);
	renderWindow.display();
}

bool SceneTransition::unload()
{
	return true;
}