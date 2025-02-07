#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

/// <summary>
/// Classe abstraite avec aucune m�thode concr�tis�e, sauf le constructeur et le destructeur
/// (qui restent tr�s simples)  Un .h suffit donc.
/// </summary>
class Scene
{

public:
	//Quand vos ajouterez des sc�nes, ajouter un enum ici.  Exit et Fail sont des marqueurs de sortie
	//GAME est tr�s g�n�rique et est valable si on a une seule sc�ne de jeu.
	//Sinon on pourrait parler de "LEVEL1, LEVEL2, ou encore GAME_SCENE1, GAME_SCENE2, etc.
	//EXIT et FAIL devraient toujours �tre pr�sents.
	enum scenes { TITLE, LEVEL1, LEVEL2, TRANSITION, END, EXIT, FAIL };

	//apr�s le : on fait appel au constructeur de la super classe
	//qui doit �tre aussi dans la liste d'initialisation
	Scene(RenderWindow& renderWindow, Event& event) : renderWindow(renderWindow), event(event) {}

	virtual ~Scene() {}  //Pour que le destructeur de l'objet en m�moire soit apell�
	virtual scenes run() = 0;
	virtual bool init() = 0;

	static const float getDeltaTime() { return deltaTime; }
	static float applyDeltaTime(const float value) { return value * deltaTime * 60.0f; }
	void exitGame()
	{
		isRunning = false;
		transitionToScene = Scene::scenes::EXIT;
	}

protected:
	//La boucle de jeu est maintenant g�r�e par la sc�ne
	void calculateDeltaTime() { deltaTime = clock.restart().asSeconds(); }
	virtual void getInputs() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool unload() = 0;

	//Chaque sc�ne aura une r�f�rence de ces objets port�e par la game elle-m�me.
	RenderWindow& renderWindow;
	Event& event;

	Clock clock;

	/// <summary>
	/// � la fin de chaque sc�ne, on indique � Game quelle nouvelle sc�ne elle doit charger.
	/// </summary>
	Scene::scenes transitionToScene;
	bool isRunning = true;
private:
	static float deltaTime;
};

