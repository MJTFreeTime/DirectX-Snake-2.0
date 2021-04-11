/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}


void Game::UpdateModel()
{

	bool upClicked = wnd.kbd.KeyIsPressed(VK_UP);
	bool downClicked = wnd.kbd.KeyIsPressed(VK_DOWN);
	bool leftClicked = wnd.kbd.KeyIsPressed(VK_LEFT);
	bool rightClicked = wnd.kbd.KeyIsPressed(VK_RIGHT);

	bool wClicked = wnd.kbd.KeyIsPressed('W');
	bool aClicked = wnd.kbd.KeyIsPressed('A');
	bool sClicked = wnd.kbd.KeyIsPressed('S');
	bool dClicked = wnd.kbd.KeyIsPressed('D');

	bool shiftClicked = wnd.kbd.KeyIsPressed(VK_SHIFT);
	bool ctrlClicked = wnd.kbd.KeyIsPressed(VK_CONTROL);

	if (upClicked || wClicked)
	{
		if (headDirection != 2)
		{
			headDirection = 1;
			moveClicked = true;
		}
	}
	else if (downClicked || sClicked)
	{
		if (headDirection != 1)
		{
			headDirection = 2;
			moveClicked = true;
		}
	}
	else if (leftClicked || aClicked)
	{
		if (headDirection != 4)
		{
			headDirection = 3;
			moveClicked = true;
		}
	}
	else if (rightClicked || dClicked)
	{
		if (headDirection != 3)
		{
			headDirection = 4;
			moveClicked = true;
		}
	}

	if (shiftClicked)
	{
		if (shiftDebounce == false)
		{
			showGrid = !showGrid;
			shiftDebounce = true;
		}
	}
	else
		shiftDebounce = false;

	if (ctrlClicked)
	{
		if (ctrlDebounce == false)
		{
			rainbow = !rainbow;
			ctrlDebounce = true;
		}
	}
	else
		ctrlDebounce = false;

	// Change moveX or moveY based on direction
	if (headDirection == 0)
		moveX = 0, moveY = 0;
	else if (headDirection == 1)
		moveY -= snakeSpeed;
	else if (headDirection == 2)
		moveY += snakeSpeed;
	else if (headDirection == 3)
		moveX -= snakeSpeed;
	else if (headDirection == 4)
		moveX += snakeSpeed;


	// If moveX has reached max then move snake
	if (moveX >= 1000)
	{
		headX += gridLen;
		moveX = 0;
		updateParts();
	}
	else if (moveX <= -1000)
	{
		headX -= gridLen;
		moveX = 0;
		updateParts();
	}

	// If moveY has reached max then move snake
	if (moveY >= 1000)
	{
		headY += gridLen;
		moveY = 0;
		updateParts();
	}
	else if (moveY <= -1000)
	{
		headY -= gridLen;
		moveY = 0;
		updateParts();
	}

	if (moveClicked == true && (moveX + gridLen >= 1000 || moveY + gridLen >= 1000 || moveX - gridLen <= -1000 || moveY - gridLen <= -1000))
	{
		moveClicked = false;
	}
}

void Game::ComposeFrame()
{
	// Draw left wall
	for (int i = margin; i <= 599 - margin; i++)
		gfx.PutPixel(margin, i, r, g, b);

	// Draw right wall
	for (int i = margin; i <= 599 - margin; i++)
		gfx.PutPixel(799 - margin, i, r, g, b);

	// Draw top wall
	for (int i = margin; i <= 799 - margin; i++)
		gfx.PutPixel(i, margin, r, g, b);

	// Draw bottom wall
	for (int i = margin; i <= 799 - margin; i++)
		gfx.PutPixel(i, 599 - margin, r, g, b);

	if (showGrid)
	{
		// Draw grid rows
		for (int i = margin; i <= 600 - margin; i += gridLen)
		{
			for (int j = margin; j <= 800 - margin; j++)
			{
				gfx.PutPixel(j, i, r, g, b);
			}
		}

		// Draw grid columns
		for (int i = margin; i <= 800 - margin; i += gridLen)
		{
			for (int j = margin; j <= 600 - margin; j++)
			{
				gfx.PutPixel(i, j, r, g, b);
			}
		}
	}
	
	// Rainbow rgb values
	if (rainbow)
	{

		if (r < 255 && g == 0 && b == 0)
			r++;
		else if (r == 255 && g < 255 && b == 0)
			g++;
		else if (r > 0 && g == 255 && b == 0)
			r--;
		else if (r == 0 && g == 255 && b < 255)
			b++;
		else if (r == 0 && g > 0 && b == 255)
			g--;
		else if (r < 255 && g == 0 && b == 255)
			r++;
		else if (r == 255 && g == 0 && b > 0)
			b--;
		else
		{
			if (r < 255)
				r++;
			if (g > 0)
				g--;
			if (b > 0)
				b--;
		}
	}
	else
		r = 128, g = 128, b = 128;

	drawHead();
	drawParts();

	/*
	if (spawnedPoints <= 1)
	{
		srand(time(NULL));	
		int xRand = rand() % (Graphics::ScreenWidth - margin - (point0.pointLen / 2)) + (margin + (point0.pointLen / 2));
		int yRand = rand() % (Graphics::ScreenHeight - margin - (point0.pointLen / 2)) + (margin + (point0.pointLen / 2));
		point0.setX(xRand);
		point0.setY(yRand);
		spawnedPoints++;
	}

	point0.drawPoint(gfx, r, g, b);
	*/
}

void Game::drawHead()
{
	// Draw snake head
	for (int i = 0; i <= snakeSize; i++)
	{
		gfx.PutPixel(headX + i, headY, r, g, b);

		for (int j = 0; j <= snakeSize; j++)
		{
			gfx.PutPixel(headX + i, headY + j, r, g, b);
		}
	}
}

void Game::drawParts()
{
	// Draw snake parts
	for (int i = 0; i < snakeParts.size(); ++i)
	{
		for (int j = 0; j <= snakeSize; j++)
		{
			gfx.PutPixel(snakeParts[i].getX() + j, snakeParts[i].getY(), r, g, b);

			for (int k = 0; k <= snakeSize; k++)
			{
				gfx.PutPixel(snakeParts[i].getX() + j, snakeParts[i].getY() + k, r, g, b);
			}
		}
	}
}

void Game::updateParts()
{
	if (snakeParts.size() < 15)
	{
		for (int i = 0; i < 15; ++i)
			snakeParts.push_back(SnakePart());
	}

	// Updating snakeParts[0]
	snakeParts[0].setX(headX);
	snakeParts[0].setY(headY);

	// Updating rest of snakeParts[]
	for (int i = snakeParts.size() - 1; i > 0; --i)
	{
		snakeParts[i].setX(snakeParts[i - 1].getX());
		snakeParts[i].setY(snakeParts[i - 1].getY());
	}
}

void Game::spawnCoin()
{
	// Spawning coin

}

int Game::SnakePart::getX()
{
	return x;
}

int Game::SnakePart::getY()
{
	return y;
}

int Game::SnakePart::getDirection()
{
	return direction;
}

void Game::SnakePart::setX(int n)
{
	x = n;
}

void Game::SnakePart::setY(int n)
{
	y = n;
}

void Game::SnakePart::setDirection(int d)
{
	direction = d;
}

// Point member functions (to be worked on)
/*
int Game::Point::getX()
{
	return x;
}

int Game::Point::getY()
{
	return y;
}

void Game::Point::drawPoint(Graphics& gfx, int r, int g, int b)
{
	for (int i = 0; i < pointLen; ++i)
	{
		gfx.PutPixel(x + i, y, r, g, b);
		
		for (int j = 0; j < pointLen; ++j)
		{
			gfx.PutPixel(x + i, y + j, r, g, b);
		}
	}
}

void Game::Point::setX(int n)
{
	x = n;
}

void Game::Point::setY(int n)
{
	y = n;
}
*/