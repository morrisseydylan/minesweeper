#include <iostream>
#include "Tile.h"
Tile::Tile() {
	HasMine = false;
	revealed = false;
	flagged = false;
	adjacentMines = 0;
	sprite.setTexture(Textures::Get("tile_hidden"));
	flag.setTexture(Textures::Get("flag"));
	mine.setTexture(Textures::Get("mine"));
}
bool Tile::IsRevealed() {
	return revealed;
}
void Tile::SetNeighbors(Tile**& tiles, int i, int j, int iMax, int jMax) {
	if (i > 0) {
		neighbors[1] = &tiles[i - 1][j];
		if (j > 0)
			neighbors[0] = &tiles[i - 1][j - 1];
		if (j < jMax)
			neighbors[2] = &tiles[i - 1][j + 1];
	}
	if (j > 0)
		neighbors[3] = &tiles[i][j - 1];
	if (j < jMax)
		neighbors[4] = &tiles[i][j + 1];
	if (i < iMax) {
		neighbors[6] = &tiles[i + 1][j];
		if (j > 0)
			neighbors[5] = &tiles[i + 1][j - 1];
		if (j < jMax)
			neighbors[7] = &tiles[i + 1][j + 1];
	}
	for (Tile* tile : neighbors)
		if (tile != nullptr)
			if (tile->HasMine)
				adjacentMines++;
	switch (adjacentMines) {
	case 1: {
		number.setTexture(Textures::Get("number_1"));
		break;
	}
	case 2: {
		number.setTexture(Textures::Get("number_2"));
		break;
	}
	case 3: {
		number.setTexture(Textures::Get("number_3"));
		break;
	}
	case 4: {
		number.setTexture(Textures::Get("number_4"));
		break;
	}
	case 5: {
		number.setTexture(Textures::Get("number_5"));
		break;
	}
	case 6: {
		number.setTexture(Textures::Get("number_6"));
		break;
	}
	case 7: {
		number.setTexture(Textures::Get("number_7"));
		break;
	}
	case 8: {
		number.setTexture(Textures::Get("number_8"));
		break;
	}
	}
}
void Tile::SetPosition(float x, float y) {
	sprite.setPosition(x, y);
	flag.setPosition(x, y);
	number.setPosition(x, y);
	mine.setPosition(x, y);
}
void Tile::Draw(sf::RenderWindow& window, bool showMines) {
	window.draw(sprite);
	if (flagged)
		window.draw(flag);
	if (HasMine && showMines)
		window.draw(mine);
	else
		if (revealed && adjacentMines > 0)
			window.draw(number);
}
void Tile::Flag(MineCounter& mineCounter) {
	if (!revealed) {
		if (flagged) {
			flagged = false;
			mineCounter.Add();
		}
		else {
			flagged = true;
			mineCounter.Subtract();
		}
	}
}
bool Tile::Reveal() {

	if (flagged)
		return false;
	revealed = true;
	sprite.setTexture(Textures::Get("tile_revealed"));
	if (HasMine)
		return true;
	if (adjacentMines == 0)
		for (int i = 0; i < 8; i++)
			if (neighbors[i] != nullptr)
				if (!neighbors[i]->revealed && !neighbors[i]->HasMine && !neighbors[i]->flagged)
					neighbors[i]->Reveal();

	return false;
}
void Tile::MineReveal() {
	sprite.setTexture(Textures::Get("tile_revealed"));
}