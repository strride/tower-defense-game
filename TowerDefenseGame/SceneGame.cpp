#include "SceneGame.h"
#include "ContentPipeline.h"
#include <iostream>
#include "MageTower.h"
#include "ArcherTower.h"
#include "Fireball.h"

int SceneGame::wave = 1;
int SceneGame::score = 0;

SceneGame::SceneGame(RenderWindow& renderWindow, Event& event, int highscore, bool reset) : Scene(renderWindow, event)
{
	highScore = highscore;
	view = renderWindow.getDefaultView();
	Subject::addObserver(this);
	if (reset) 
	{
		wave = 1;
		score = 0;
	}
}

SceneGame::~SceneGame()
{
	delete[] towerEmplacements;
	delete[] waypoints;
	for (int i = 0; i < towers.size(); i++)
	{
		delete towers[i];
	}
	for (int i = 0; i < Demon::fireballs.size(); i++)
	{
		delete Demon::fireballs[i];
	}
	for (int i = 0; i < MageTower::blasts.size(); i++)
	{
		delete MageTower::blasts[i];
	}
	for (int i = 0; i < ArcherTower::arrows.size(); i++) {
		delete ArcherTower::arrows[i];
	}
	for (int i = 0; i < spells.size(); i++)
	{
		delete spells[i];
	}
	Demon::fireballs.clear();
	MageTower::blasts.clear();
	ArcherTower::arrows.clear();
	spells.clear();
	towers.clear();

	Subject::removeAllObservers();
}

Scene::scenes SceneGame::run()
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

bool SceneGame::init()
{
	gameOver = false;
	spawnedDemons = 0;
	victory = false;
	mana = STARTING_MANA;
	kills = 0;
	manaTimer = 0;
	hud.hudInit(ContentPipeline::getInstance().getHudmaskTexture(), ContentPipeline::getInstance().getComiciFont());
	hud.setWave(wave);
	kingTower.init();
	for (int i = 0; i < towerAmount; i++)
	{
		towerEmplacements[i].init();
	}

	for (int i = 0; i < towerAmount; i++) 
	{

		MageTower* mageTower = new MageTower();
		ArcherTower* archerTower = new ArcherTower();
		mageTower->init();
		archerTower->init();
		towers.push_back(mageTower);
		towers.push_back(archerTower);
	}
	
	for (int i = 0; i < waypointAmount; i++)
	{
		waypoints[i].init();
	}

	for (int i = 0; i < NB_DEMONS; i++)
	{
		demons[i].init();
	}

	for (int i = 0; i < DEFAULT_NB_SPELLS; i++)
	{
		Spell* plague = new Spell(SpellType::plague);
		Spell* sacredLight = new Spell(SpellType::sacredLight);
		plague->init();
		sacredLight->init();
		spells.push_back(plague);
		spells.push_back(sacredLight);
	}

	String musicPath = musicSounds[rand() % 3];
	music.openFromFile(musicPath);
	music.setLoop(true);
	music.setVolume(20);
	music.play();

	return true;
}

void SceneGame::notify(Subject* subject)
{
	if (typeid(*subject) == typeid(Demon)) 
	{
		score += KILL_SCORE;
		mana += KILL_MANA;
		kills++;
	}

	if (typeid(*subject) == typeid(KingTower)) 
	{
		gameOver = true;
		hud.setDefeat();
		transitionToScene = scenes::END;
	}
}

void SceneGame::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	inputs.reset();
	while (renderWindow.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed) exitGame();

		if (event.type == Event::KeyPressed) 
		{
			if (Keyboard::isKeyPressed(Keyboard::W)) inputs.enableWaypoints = true;

			if (Keyboard::isKeyPressed(Keyboard::Z)) inputs.enableOption = Options::towerArcher;

			if (Keyboard::isKeyPressed(Keyboard::X)) inputs.enableOption = Options::towerMage;

			if (Keyboard::isKeyPressed(Keyboard::C)) inputs.enableOption = Options::spellPlague;

			if (Keyboard::isKeyPressed(Keyboard::V)) inputs.enableOption = Options::spellSacredLight;

			if (Keyboard::isKeyPressed(Keyboard::P)) inputs.pause = true;

			if (Keyboard::isKeyPressed(Keyboard::Enter)) inputs.next = true;
		}

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				inputs.mouseLeftButtonClicked = true;
				inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
			}
		}

	}
}

void SceneGame::update()
{
	if (inputs.next && (victory || gameOver)) 
	{
		isRunning = false;
		return;
	}

	if (inputs.pause) 
	{
		isPaused = !isPaused;
		hud.setPaused(isPaused);
		music.pause();
	}

	if (inputs.enableWaypoints) showWaypoints = !showWaypoints;
	if (isPaused) return;
	if(gameOver) return;
	if (music.getStatus() == Music::Paused) music.play();

	if (!victory) 
	{
		manageOptions();
		manageMana();
		if (inputs.mouseLeftButtonClicked) manageClick();
	}

	spawnDemonIfAvailable();
	int totalHealth = calculateTotalDemonsHealth();
	makeEnemiesAttackEachOther();
	manageDemons();
	manageProjectiles();
	manageTowers();
	manageSpells();
	int healthDifference = totalHealth - calculateTotalDemonsHealth();
	score += healthDifference;
	manageHud();
	checkVictory();
}

void SceneGame::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.draw(map);

	kingTower.draw(renderWindow);
	for (int i = 0; i < towerAmount; i++)
	{
		towerEmplacements[i].draw(renderWindow);
	}

	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->draw(renderWindow);
	}

	if (showWaypoints) 
	{
		for (int i = 0; i < waypointAmount; i++)
		{
			waypoints[i].draw(renderWindow);
		}
	}

	for (int i = 0; i < NB_DEMONS; i++)
	{
		demons[i].draw(renderWindow);
	}

	for (int i = 0; i < Demon::fireballs.size(); i++)
	{
		Demon::fireballs[i]->draw(renderWindow);
	}

	for (int i = 0; i < MageTower::blasts.size(); i++)
	{
		MageTower::blasts[i]->draw(renderWindow);
	}

	for (int i = 0; i < ArcherTower::arrows.size(); i++)
	{
		ArcherTower::arrows[i]->draw(renderWindow);
	}

	for (int i = 0; i < spells.size(); i++)
	{
		spells[i]->draw(renderWindow);
	}

	hud.draw(renderWindow);
	renderWindow.display();
}

bool SceneGame::unload()
{
	return true;
}

void SceneGame::manageOptions()
{
	if (inputs.enableOption == Options::none) return;
	isUsingTower = false;
	isUsingSpell = false;

	switch (inputs.enableOption)
	{
	case Options::towerArcher:
		isUsingTower = true;
		selectedTower = TowerType::archer;
		break;
	case Options::towerMage:
		isUsingTower = true;
		selectedTower = TowerType::mage;
		break;
	case Options::spellPlague:
		isUsingSpell = true;
		selectedSpell = SpellType::plague;
		break;
	case Options::spellSacredLight:
		isUsingSpell = true;
		selectedSpell = SpellType::sacredLight;
		break;
	default:
		break;
	}

	hud.selectOption(inputs.enableOption);
}

void SceneGame::makeEnemiesAttackEachOther()
{
	for (int i = 0; i < NB_DEMONS; i++)
	{
		if (!demons[i].isActive()) continue;
		AttackTower* closestTower = nullptr;
		float distance = 0;
		for (int j = 0; j < towers.size(); j++)
		{
			if (!towers[j]->isActive()) continue;
			float currentDistance = towers[j]->getDistanceFrom(demons[i]);
			if (currentDistance <= MAX_ATTACK_DISTANCE)
			{
				towers[j]->setTarget(&demons[i]);
				if (closestTower == nullptr)
				{
					closestTower = towers[j];
					distance = currentDistance;
				}
				else
				{
					if (currentDistance < distance)
					{
						closestTower = towers[j];
						distance = currentDistance;
					}
				}
			}
		}
		float kingTowerDistance = kingTower.getDistanceFrom(demons[i]);
		if (kingTowerDistance <= MAX_ATTACK_DISTANCE && (closestTower == nullptr || distance > kingTowerDistance)) 
		{
			demons[i].setTarget(&kingTower);
		}
		else if (closestTower != nullptr) 
		{
			demons[i].setTarget(closestTower);
		}
	}
}

void SceneGame::manageProjectiles()
{
	for (int i = 0; i < Demon::fireballs.size(); i++)
	{
		Demon::fireballs[i]->update();
	}
	for (int i = 0; i < MageTower::blasts.size(); i++)
	{
		MageTower::blasts[i]->update();
	}
	for (int i = 0; i < ArcherTower::arrows.size(); i++)
	{
		ArcherTower::arrows[i]->update();
	}
}

void SceneGame::manageTowers()
{
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->update();
	}
}

void SceneGame::spawnDemonIfAvailable()
{
	if (demonSpawnCooldown <= 0 && spawnedDemons < KILLS_TO_WIN)
	{
		for (int i = 0; i < NB_DEMONS; i++)
		{
			if (!demons[i].isActive())
			{
				demons[i].spawn(demonStartPos, waypoints);
				demonSpawnCooldown = DEMON_SPAWN_COOLDOWN;
				spawnedDemons++;
				break;
			}
		}
	}
	else
	{
		demonSpawnCooldown -= Scene::getDeltaTime();
	}
}

void SceneGame::manageDemons()
{
	for (int i = 0; i < NB_DEMONS; i++)
	{
		demons[i].update();
	}
}

AttackTower* SceneGame::placeTower(Vector2f position, TowerType towerType)
{
	for (int i = 0; i < towers.size(); i++)
	{
		TowerType typeTest = towers[i]->getType();
		if (!towers[i]->isActive() && towers[i]->getType() == towerType) 
		{
			towers[i]->spawn(position);
			return towers[i];
		}
	}
}

void SceneGame::manageClick()
{
	if (isUsingTower) {
		for (int i = 0; i < towerAmount; i++)
		{
			if (!towerEmplacements[i].isActive()) continue;

			if (towerEmplacements[i].getGlobalBounds().contains(inputs.mousePosition)) 
			{
				int price = 0;
				switch (selectedTower)
				{
				case archer:
					price = ARCHER_TOWER_PRICE;
					break;
				case mage:
					price = MAGE_TOWER_PRICE;
					break;
				}
				if (price > mana) return;
				AttackTower* tower = placeTower(towerEmplacements[i].getPosition(), selectedTower);
				towerEmplacements[i].setTower(tower);
				mana -= price;
				return;
			}
		}
	}
	else if (isUsingSpell) {
		for (int i = 0; i < spells.size(); i++)
		{
			if (!spells[i]->isActive() && spells[i]->getSpellType() == selectedSpell) 
			{
				int price = 0;
				switch (selectedSpell)
				{
				case plague:
					price = PLAGUE_SPELL_PRICE;
					break;
				case sacredLight:
					price = LIGHT_SPELL_PRICE;
					break;
				}
				if (price > mana) return;
				spells[i]->spawn(inputs.mousePosition);
				mana -= price;
				return;
			}
		}
	}
}

void SceneGame::manageSpells()
{
	for (int i = 0; i < spells.size(); i++)
	{
		spells[i]->update();
	}
}

void SceneGame::setMap(const Maps map)
{
	this->map.setTexture(ContentPipeline::getInstance().getMapTexture(map));
}

void SceneGame::manageMana()
{
	manaTimer += Scene::getDeltaTime();
	if (manaTimer >= SECONDS_PER_MANA)
	{
		mana++;
		manaTimer = 0;
	}
}

void SceneGame::setKingTowerPos(const Vector2f pos)
{
	kingTower.spawn(pos);
}

void SceneGame::manageHud()
{
	if (score > highScore) highScore = score;
	hud.setHighscore(highScore);
	hud.setScore(score);
	hud.setMana(mana);
	hud.setKills(kills);
}

void SceneGame::setTowersPos(const float pos[][2], const int nbElements)
{
	towerAmount = nbElements;
	towerEmplacements = new TowerEmplacement[nbElements];
	for (int i = 0; i < nbElements; i++)
	{
		towerEmplacements[i].setPosition(pos[i][0], pos[i][1]);
	}
}

void SceneGame::setWaypoints(Waypoint waypoints[], const int nbElements)
{
	this->waypoints = waypoints;
	waypointAmount = nbElements;
}

void SceneGame::checkVictory()
{
	if (kills >= KILLS_TO_WIN && !victory) 
	{
		if (wave < WAVES_TO_END) 
		{
			wave++;
			transitionToScene = scenes::TRANSITION;
		}
		else 
		{
			transitionToScene = scenes::END;
		}
		victory = true;
		hud.setVictory();
	}
}

void SceneGame::setDemonStartPos(const Vector2f pos)
{
	demonStartPos = pos;
}

int SceneGame::calculateTotalDemonsHealth()
{
	int totalHealth = 0;
	for (int i = 0; i < NB_DEMONS; i++)
	{
		if (demons[i].isAlive()) totalHealth += demons[i].getHealth();
	}
	return totalHealth;
}
