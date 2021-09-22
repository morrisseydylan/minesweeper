#pragma once
#include "MineCounter.h"
class Tile
{
	bool revealed;
	bool flagged;
	short adjacentMines;
	Tile* neighbors[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	sf::Sprite sprite;
	sf::Sprite flag;
	sf::Sprite number;
	sf::Sprite mine;
public:
	bool HasMine;
	Tile();
	bool IsRevealed();
	void SetNeighbors(Tile**& tiles, int i, int j, int iMax, int jMax);
	void SetPosition(float x, float y);
	void Draw(sf::RenderWindow& window, bool showMines);
	void Flag(MineCounter& mineCounter);
	bool Reveal();
	void MineReveal();
};

