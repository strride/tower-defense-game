#pragma once
#include <SFML/Graphics.hpp>

struct Inputs
{
	Inputs()
	{
		reset();
	}

	void reset()
	{
		mousePosition = Vector2f(0.0f, 0.0f);
		mouseLeftButtonClicked = false;
		enableWaypoints = false;
		pause = false;
		enableOption = Options::none;
		next = false;
	}

	Vector2f mousePosition;
	bool mouseLeftButtonClicked;
	bool enableWaypoints;
	Options enableOption;
	bool pause;
	bool next;
};
