#pragma once
#include <fstream>
#include "Tile.h"
class Board
{
	int rows;
	int columns;
	int mines;
	Tile** tiles;
	int GetMines();
	MineCounter mineCounter;
public:
	Board(int rows, int columns, int mines);
	void GenerateTiles(string board);
	void Clear();
	void Draw(sf::RenderWindow& window, bool showMines);
	bool Reveal(int i, int j);
	void RevealMines();
	void Flag(int i, int j);
	bool Won();
	~Board();
};

