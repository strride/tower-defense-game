#pragma once
#include "Scene.h"
#include "Hud.h"
#include "Inputs.h"
#include "Constants.h"
#include "KingTower.h"
#include "TowerEmplacement.h"
#include "Waypoint.h"
#include "Demon.h"
#include "IObserver.h"
#include "Spell.h"

class SceneGame : public Scene, public IObserver
{
public:
	SceneGame(RenderWindow& renderWindow, Event& event, int highscore, bool reset);
	~SceneGame();
	scenes run() override;
	bool init() override;
	static const int getWave() { return wave; }
	static const int getScore() { return score; }
	void notify(Subject* subject) override;
	bool isVictory() const { return victory; }
	static const int MAX_ATTACK_DISTANCE = 300;
private:
	void getInputs() override;
	void update() override;
	void draw() override;
	bool unload() override;

	static const int NB_DEMONS = 20;
	static const int DEFAULT_NB_SPELLS = 1;
	const float DEMON_SPAWN_COOLDOWN = 3.0f;
	static const int STARTING_MANA = 500;
	static const int KILL_MANA = 25;
	static const int KILL_SCORE = 50;
	const float SECONDS_PER_MANA = 0.2f;
	static const int KILLS_TO_WIN = 50;
	static const int WAVES_TO_END = 10;
	static const int ARCHER_TOWER_PRICE = 70;
	static const int MAGE_TOWER_PRICE = 100;
	static const int LIGHT_SPELL_PRICE = 60;
	static const int PLAGUE_SPELL_PRICE = 20;

	View view;
	Hud hud;
	Inputs inputs;
	Sprite map;

	static int wave;
	static int score;
	int highScore;
	int mana;
	int kills;
	int spawnedDemons;

	bool gameOver;
	bool victory;

	float manaTimer;

	TowerType selectedTower;
	SpellType selectedSpell;
	bool isUsingSpell = false;
	bool isUsingTower = false;

	bool showWaypoints = false;
	bool isPaused = false;
	KingTower kingTower;
	TowerEmplacement* towerEmplacements;
	std::vector<AttackTower*> towers;
	int towerAmount;
	Waypoint* waypoints;
	int waypointAmount;
	Vector2f demonStartPos;
	Demon demons[NB_DEMONS];
	float demonSpawnCooldown = DEMON_SPAWN_COOLDOWN;
	std::vector<Spell*> spells;

	String musicSounds[3] = { "Ressources\\Sounds\\Music\\Theme01.ogg", "Ressources\\Sounds\\Music\\Theme02.ogg", "Ressources\\Sounds\\Music\\Theme03.ogg" };
	Music music;

	void spawnDemonIfAvailable();
	void manageDemons();
	void manageOptions();
	void makeEnemiesAttackEachOther();
	void manageProjectiles();
	void manageTowers();
	AttackTower* placeTower(Vector2f position, TowerType towerType);
	void manageClick();
	void manageSpells();
	void manageMana();
	void manageHud();
	void checkVictory();
	int calculateTotalDemonsHealth();
protected:
	void setMap(const Maps map);
	void setKingTowerPos(const Vector2f pos);
	void setTowersPos(const float pos[][2], const int nbElements);
	void setWaypoints(Waypoint waypoints[], const int nbElement);
	void setDemonStartPos(const Vector2f pos);
};