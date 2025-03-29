// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include <iostream>
#include <thread>

const int offset = 25;
Surface ball("assets/ball.png");
int px = 0, py = 0;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	std::cout << "Node GRID: X / Y" << endl;
	for (int y = 0; y < GHEIGHT; y++)
	{
		for (int x = 0; x < GWIDTH; x++)
		{
			nodesGrid[y][x] = Node(x, y);
			cout << nodesGrid[y][x].x << " / " << nodesGrid[y][x].y << " ||| ";
		}
		cout << endl;
	}
	
	
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick( float /* deltaTime */ )
{
	screen->Clear(0);
	
	if (showAlgorithm)
	{
		Algorithm();
		showAlgorithm = false;
	}
	AlghoritmTiles();

}

void Tmpl8::Game::Algorithm(int StartX, int StartY)
{
	//INIT
	Node* start = &nodesGrid[StartX][StartY];
	
	start->visited = true;
	std::queue<Node*> Q;
	//Push first node to queue
	Q.push(start);
	
	while (!Q.empty())
	{
		//Check neighbours(clockwise order ,starting in top one)
		Node* current = Q.front();
		//remove current first node from queue
		Q.pop();
		//Print in command line results
		PrintGrid();
		//Checkes and updates neighbours
		CheckNeighbours(current, Q);
	}
}

void Tmpl8::Game::CheckNeighbours(Node* current, std::queue<Node*>& Q)
{
	Node* neighbour = nullptr;
	int currentX = current->x;
	int currentY = current->y;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			if (currentY - 1 < 0) continue;
			neighbour = &nodesGrid[currentY - 1][currentX];
			
		}
		else if (i == 1)
		{
			if (currentX + 1 > GWIDTH - 1) continue;
			neighbour = &nodesGrid[currentY][currentX + 1];
			
		}
		else if (i == 2)
		{
			if (currentY + 1 > GHEIGHT - 1) continue;
			neighbour = &nodesGrid[currentY + 1][currentX];
			
		}
		else if (i == 3)
		{
			if (currentX - 1 < 0) continue;
			neighbour = &nodesGrid[currentY][currentX - 1];
			
		}
		
		if (!neighbour->visited)
		{
			neighbour->visited = true;
			Q.push(neighbour);
		}
	}
}

void Tmpl8::Game::PrintGrid()
{
	for (int y = 0; y < GHEIGHT; y++)
	{
		for (int x = 0; x < GWIDTH; x++)
		{
			if (nodesGrid[y][x].visited)
				std::cout << "X ";  // Mark visited nodes
			else
				std::cout << ". ";  // Unvisited nodes
		}
		std::cout << std::endl;
	}
	std::cout << "----------------\n";
}



void Tmpl8::Game::AlghoritmTiles()
{
	for (int y = 0; y < GHEIGHT; y++)
	{
		for (int x = 0; x < GWIDTH; x++)
		{
			if (nodesGrid[y][x].visited)
			{
				screen->Bar(x * 100, y * 100, x * 100 + (offset * 3), y * 100 + (offset * 3), 0x0000FF);
			}
			else
			{
				screen->Bar(x * 100, y * 100, x * 100 + (offset * 3), y * 100 + (offset * 3), 0xFF0000);
			}
		}
	}
}
