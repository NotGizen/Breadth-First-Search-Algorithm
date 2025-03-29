// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
#include "Node.h"
#include <queue>
#include <vector>
#define GWIDTH 4
#define GHEIGHT 4
namespace Tmpl8
{
class DummyData
{
public:
	DummyData(){}
	Surface sprite;
	
};

class Game : public TheApp
{
public:
	// game flow methods
	void Init();
	void Tick( float deltaTime );
	void Shutdown() { /* implement if you want to do something on exit */ }
	// input handling
	void MouseUp( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button) { if (button == 1) showAlgorithm = true;/* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp( int ) { /* implement if you want to handle keys */ }
	void KeyDown( int ) { /* implement if you want to handle keys */ }
	void SimpleBFS(int StartX, int StartY);
	void PathfindingBFS(int StartX, int StartY, int endX, int endY);
	void CheckNeighbours(Node* currentNode, std::queue<Node*>& Q);
	void PrintGrid();
	void PrintPathGrid();
	void ReconstructPath(Node* end, Node* current);
	void AlghoritmTiles();
	//DummyData dummy;
	/*int grid[GHEIGHT][GWIDTH] = 
	{
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}
	};*/
	Node nodesGrid[GHEIGHT][GWIDTH];
	// data members
	int2 mousePos;
	//Algorithm
	bool showAlgorithm = false;
	
	
};

} // namespace Tmpl8