#include <cstdlib>
#include <iostream>
#include "Board.h"

int Board::GetMines() {
	int mines = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (tiles[i][j].HasMine)
				mines++;
	return mines;
}
Board::Board(int rows, int columns, int mines) : mineCounter(rows, mines) {
	this->columns = columns;
	this->rows = rows;
	this->mines = mines;
	GenerateTiles("");
}
void Board::GenerateTiles(string board) {
	tiles = new Tile * [rows];
	for (int i = 0; i < rows; i++)
		tiles[i] = new Tile[columns];
	if (board == "") {
		srand((int)time(0));
		while (mines > GetMines()) {
			int randomI = rand() % rows;
			int randomJ = rand() % columns;
			tiles[randomI][randomJ].HasMine = true;
		}
	}
	else {
		ifstream boardFile("boards/" + board + ".brd");
		string row;
		for (int i = 0; getline(boardFile, row); i++)
			for (unsigned int j = 0; j < row.length(); j++)
				if (row[j] == '1')
					tiles[i][j].HasMine = true;
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			tiles[i][j].SetNeighbors(tiles, i, j, rows - 1, columns - 1);
			tiles[i][j].SetPosition(j * 32.0f, i * 32.0f);
		}
	mineCounter.AssignCountValue(to_string(GetMines()));
	mineCounter.Negative = false;
	mineCounter.UpdateTextures();
}
void Board::Clear() {
	for (int i = 0; i < rows; i++)
		delete[] tiles[i];
	delete[] tiles;
}
void Board::Draw(sf::RenderWindow& window, bool showMines) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			tiles[i][j].Draw(window, showMines);
	mineCounter.Draw(window);
}
bool Board::Reveal(int i, int j) {
	return tiles[i][j].Reveal();
}
void Board::RevealMines() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (tiles[i][j].HasMine)
				tiles[i][j].MineReveal();
}
void Board::Flag(int i, int j) {
	tiles[i][j].Flag(mineCounter);
}
bool Board::Won() {
	bool won = true;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (!tiles[i][j].HasMine && !tiles[i][j].IsRevealed())
				return false;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (tiles[i][j].HasMine)
				tiles[i][j].Flag(mineCounter);
	return true;
}
Board::~Board() {
	Clear();
}