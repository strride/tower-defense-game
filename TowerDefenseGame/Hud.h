#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class Hud
{
public:
	Hud() {}
	void hudInit(const Texture& hudMaskTexture, const Font& font);
	void draw(sf::RenderWindow& renderWindow);
	void selectOption(const Options option);
	void setPaused(const bool pause);
	void setMana(const int mana);
	void setScore(const int score);
	void setKills(const int kills);
	void setWave(const int wave);
	void setHighscore(const int highscore);
	void setVictory();
	void setDefeat();
private:
	void resetSelected();
	static const int INSTRUCTIONS_NUMBER = 6;
	static const int TEXT_POSITION_X = 1250;
	
	sf::Text specialStateText;

	sf::Text manaText;
	sf::Text scoreText;
	sf::Text killsText;

	sf::Text instructionTexts[INSTRUCTIONS_NUMBER];

	sf::Text highScoreText;
	sf::Text waveText;

	Sprite hudMask;
};
