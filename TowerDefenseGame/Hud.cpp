#include "Hud.h"

void Hud::hudInit(const Texture& hudMaskTexture, const Font& font)
{
	hudMask.setTexture(hudMaskTexture);

	specialStateText.setFont(font);
	specialStateText.setCharacterSize(25);
	specialStateText.setFillColor(Color::White);
	specialStateText.setPosition(TEXT_POSITION_X, 10);
	specialStateText.setString("");

	manaText = specialStateText;
	scoreText = specialStateText;
	killsText = specialStateText;
	waveText = specialStateText;
	highScoreText = specialStateText;

	waveText.setPosition(TEXT_POSITION_X, 110);
	manaText.setPosition(TEXT_POSITION_X, 210);
	killsText.setPosition(TEXT_POSITION_X, 250);
	scoreText.setPosition(TEXT_POSITION_X, 290);
	highScoreText.setPosition(TEXT_POSITION_X, 330);

	waveText.setString("Wave - 1");
	manaText.setString("Mana - 0");
	killsText.setString("Kills - 0");
	scoreText.setString("Score - 0");
	highScoreText.setString("HighScore - 0");

	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
	{
		instructionTexts[i] = specialStateText;
		instructionTexts[i].setPosition(TEXT_POSITION_X, 430 + i * 40);
	}

	instructionTexts[0].setStyle(Text::Underlined);
	instructionTexts[0].setString("Instructions");
	instructionTexts[1].setString("Z: Create archer tower (70 manas)");
	instructionTexts[2].setString("X: Create mage tower (100 manas)");
	instructionTexts[3].setString("C: Plague spell (20 manas)");
	instructionTexts[4].setString("V: Sacred light spell (60 manas)");
	instructionTexts[5].setString("P: Pause");

	specialStateText.setCharacterSize(35);
}

void Hud::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(hudMask);
	renderWindow.draw(specialStateText);
	renderWindow.draw(manaText);
	renderWindow.draw(scoreText);
	renderWindow.draw(killsText);
	renderWindow.draw(highScoreText);
	renderWindow.draw(waveText);

	for (int i = 0; i < INSTRUCTIONS_NUMBER; i++)
		renderWindow.draw(instructionTexts[i]);
}

void Hud::selectOption(const Options option)
{
	resetSelected();

	switch (option)
	{
	case Options::towerArcher:
		instructionTexts[1].setFillColor(Color(212, 175, 55, 255));
		break;
	case Options::towerMage:
		instructionTexts[2].setFillColor(Color(212, 175, 55, 255));
		break;
	case Options::spellPlague:
		instructionTexts[3].setFillColor(Color(212, 175, 55, 255));
		break;
	case Options::spellSacredLight:
		instructionTexts[4].setFillColor(Color(212, 175, 55, 255));
		break;
	default:
		break;
	}
}

void Hud::setPaused(const bool pause)
{
	if (pause)
		specialStateText.setString("Pause");
	else
		specialStateText.setString("");
}

void Hud::setMana(const int mana)
{
	manaText.setString("Mana - " + std::to_string(mana));
}

void Hud::setScore(const int score)
{
	scoreText.setString("Score - " + std::to_string(score));
}

void Hud::setKills(const int kills)
{
	killsText.setString("Kills - " + std::to_string(kills));
}

void Hud::setWave(const int wave)
{
	waveText.setString("Wave - " + std::to_string(wave));
}

void Hud::setHighscore(const int highscore)
{
	highScoreText.setString("Highscore - " + std::to_string(highscore));
}

void Hud::setVictory()
{
	specialStateText.setString("Victory!\nPress Enter to Continue");
}

void Hud::setDefeat()
{
	specialStateText.setString("Game Over\nPress Enter to Exit");
}

void Hud::resetSelected()
{
	for (int i = 1; i < INSTRUCTIONS_NUMBER - 1; i++)
		instructionTexts[i].setFillColor(Color::White);
}