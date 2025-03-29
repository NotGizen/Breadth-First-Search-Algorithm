// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include <iostream>
#include <thread>

const int offset = 30;
Surface ball("assets/ball.png");
int2 ballPos = int2(0, 4);
float moveTimer = 0.f;
int2 endPos = int2(0,0);

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Loading node grids with the correct positions(just like elements)
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
void Game::Tick( float  deltaTime  )
{
	screen->Clear(0);
	int2 gMousePos = int2(mousePos.x / 100, mousePos.y / 100);
	if (setEnd)
	{
		ballPos.x = gMousePos.x;
		ballPos.y = gMousePos.y;
		setEnd = false;
	}
	int px = offset + 100 * ballPos.x, py = offset + 100 * ballPos.y;
	if (showAlgorithm)
	{
		showAlgorithm = false;
	}
		PathfindingBFS(ballPos.x, ballPos.y, gMousePos.x, gMousePos.y);
	AlghoritmTiles();
	if (moveTimer >= 0.3f)
	{
		Move();
		moveTimer = 0.f;
	}
	else
	{
		moveTimer += deltaTime/1000;
	}
	ball.CopyTo(screen, px, py);     
	cout <<"MousePos: "<< gMousePos.x << " / " << gMousePos.y <<endl;
}

void Tmpl8::Game::SimpleBFS(int StartX, int StartY)
{
	//INIT
	Node* start = &nodesGrid[StartY][StartX];
	
	start->visited = true;
	std::queue<Node*> Q;
	//Push first node to queue
	Q.push(start);
	
	while (!Q.empty())
	{
		//Current node now is the first from the queue
		
		Node* current = Q.front();
		//remove current first node from queue
		Q.pop();
		//Print in command line results
		PrintGrid();
		//Checkes and updates neighbours (clockwise order ,starting from the top one)
		CheckNeighbours(current, Q);
	}
}

void Tmpl8::Game::PathfindingBFS(int StartX, int StartY, int endX, int endY)
{
	//Reset
	for (int y = 0; y < GHEIGHT; y++)
	{
		for (int x = 0; x < GWIDTH; x++)
		{
			nodesGrid[y][x].parent = nullptr;
			nodesGrid[y][x].visited = false;
			nodesGrid[y][x].isPath = false;
			nodesGrid[y][x].isCollision = false;
			if (collision[y][x] == 1) nodesGrid[y][x].isCollision = true;
		}
	}
	//INIT
	Node* start = &nodesGrid[StartY][StartX];
	Node* end = &nodesGrid[endY][endX];
	start->visited = true;
	std::queue<Node*> Q;
	//Push first node to queue
	Q.push(start);
	Node* current = Q.front();
	while (!(&current == &end))
	{
		//Current node now is the first from the queue
		 if (Q.empty()) break;
		 current = Q.front();
		//remove current first node from queue
		Q.pop();
		//Print in command line results
		//PrintGrid();
		//Checkes and updates neighbours (clockwise order ,starting from the top one)
		CheckNeighbours(current, Q);
	}
	ReconstructPath(end, current);
	PrintPathGrid();
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
		
		if (!neighbour->visited && !neighbour->isCollision)
		{
			neighbour->parent = current;
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

void Tmpl8::Game::PrintPathGrid()
{
	
		for (int y = 0; y < GHEIGHT; y++)
		{
			for (int x = 0; x < GWIDTH; x++)
			{
			
				if (nodesGrid[y][x].isPath)
				{

					std::cout << "X ";  // Mark visited nodes

				}
				else
					std::cout << ". ";  // Unvisited nodes
			
			
			}
			std::cout << std::endl;
		}
		std::cout << "----------------\n";

	
}

void Tmpl8::Game::ReconstructPath(Node* end, Node* current)
{
	//std::vector<Node*> parents;
	current = end;
	while (current != nullptr)
	{
		//parents.push_back(current);
		current->isPath = true;
		//if (!current->parent) break;
		current = current->parent;
		
	}
	//std::reverse(parents.begin(), parents.end());
	
}



void Tmpl8::Game::AlghoritmTiles()
{
	for (int y = 0; y < GHEIGHT; y++)
	{
		for (int x = 0; x < GWIDTH; x++)
		{
			if (collision[y][x] == 1)
			{
				screen->Bar(x * 100 + offset, y * 100 + offset, x * 100 + (offset * 3), y * 100 + (offset * 3), 0x00FF00);
			}
			else if (nodesGrid[y][x].isPath)
			{
				screen->Bar(x * 100 + offset, y * 100 + offset, x * 100 + (offset * 3), y * 100 + (offset * 3), 0x0000FF);
			}
			else
			{
				screen->Bar(x * 100 + offset, y * 100 + offset, x * 100 + (offset * 3), y * 100 + (offset * 3), 0xFF0000);
			}

		}
	}
}

void Tmpl8::Game::Move()
{
	Node* current = &nodesGrid[ballPos.y][ballPos.x];
	Node* neighbour = nullptr;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			if (current->y - 1 < 0) continue;
			if (nodesGrid[current->y - 1][current->x].isPath) ballPos.y -= 1;
				
		}
		else if (i == 1)
		{
			if (current->x + 1 > GWIDTH - 1) continue;
			if(nodesGrid[current->y][current->x + 1].isPath) ballPos.x += 1;

		}
		else if (i == 2)
		{
			if (current->y + 1 > GHEIGHT - 1) continue;
			if(nodesGrid[current->y + 1][current->x].isPath) ballPos.y += 1;

		}
		else if (i == 3)
		{
			if (current->x - 1 < 0) continue;
			if(nodesGrid[current->y][current->x - 1].isPath) ballPos.x -= 1;

		}
	}
}
