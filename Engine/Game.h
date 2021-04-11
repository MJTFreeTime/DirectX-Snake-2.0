/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <stdlib.h>
#include <time.h>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void drawHead();
	void drawParts();
	void updateParts();
	void spawnCoin();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */

	// Wall variables
	static constexpr int margin = 50;
	
	// Grid variables
	int gridLen = 20;
	bool showGrid = false;
	bool shiftDebounce = false;

	// Snake head variables
	int snakeSize = gridLen - 2;
	int headX = (800 / 2) - (gridLen / 2) + 1;
	int headY = (600 / 2) - (gridLen / 2) + 1;
	int r = 255;
	int g = 0;
	int b = 0;
	int rainbow = false;
	int ctrlDebounce = false;

	// Snake movement variables
	int snakeSpeed = 30; // Speed of snake (0 - 1000)
	int moveX = 0;
	int moveY = 0;
	int headDirection = 1; // 0 = frozen, 1 = up, 2 = down, 3 = left, 4 = right (default)
	bool moveClicked = false; // Only let player click a movement button when this is set to false

	// SnakePart class
	class SnakePart
	{
	public:
		// SnakePart(); // SnakePart constructor definition
		int getX();
		int getY();
		int getDirection();
		void setX(int x);
		void setY(int y);
		void setDirection(int direction);

	private:
		int x;
		int y;
		int direction; // 0 stopped, 1 up, 2 down, 3 left, 4 right
	};

	// Point class (being worked on)

	/*
	class Point
	{
	public:
		int getX();
		int getY();
		void setX(int n);
		void setY(int n);
		void drawPoint(Graphics& gfx, int r, int g, int b);
		static constexpr int pointLen = 10; // Width/length of point
	private:
		int x;
		int y;
	};

	// Point variables
	Point point0;
	int spawnedPoints = 0;
	*/

	// Vector to store Snakeparts that are created
	std::vector <SnakePart> snakeParts = std::vector <SnakePart>(1);

	/********************************/
};