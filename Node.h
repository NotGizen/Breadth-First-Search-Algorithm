#pragma once
class Node
{
public:
	Node(){}
	Node(int posx, int posy) { x = posx; y = posy; }

	//Node* parent = nullptr;
	bool visited = false;
	int x, y;
	
};

