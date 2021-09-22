#include <iostream>
#include "Board.h"

bool ClickedOn(sf::RenderWindow& window, sf::Sprite& sprite) {
    return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

int main()
{
    ifstream config("boards/config.cfg");
    string columns, rows, mines;
    getline(config, columns);
    getline(config, rows);
    getline(config, mines);
    sf::RenderWindow window(sf::VideoMode(stoi(columns) * 32, stoi(rows) * 32 + 88), "Minesweeper");
    Board board(stoi(rows), stoi(columns), stoi(mines));
    bool gameOver = false;
    bool gameWon = false;
    bool debugMode = false;
    sf::Sprite resetButton(Textures::Get("face_happy"));
    sf::Sprite debugButton(Textures::Get("debug"));
    sf::Sprite test1Button(Textures::Get("test_1"));
    sf::Sprite test2Button(Textures::Get("test_2"));
    sf::Sprite test3Button(Textures::Get("test_3"));
    resetButton.setPosition((((stof(columns) - 2.0f) / 2.0f)) * 32.0f, stof(rows) * 32.0f);
    debugButton.setPosition((((stof(columns) - 2.0f) / 2.0f)) * 32.0f + 128.0f, stof(rows) * 32.0f);
    test1Button.setPosition((((stof(columns) - 2.0f) / 2.0f)) * 32.0f + 192.0f, stof(rows) * 32.0f);
    test2Button.setPosition((((stof(columns) - 2.0f) / 2.0f)) * 32.0f + 256.0f, stof(rows) * 32.0f);
    test3Button.setPosition((((stof(columns) - 2.0f) / 2.0f)) * 32.0f + 320.0f, stof(rows) * 32.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (ClickedOn(window, resetButton)) {
                        board.Clear();
                        board.GenerateTiles("");
                        gameOver = false;
                        gameWon = false;
                        resetButton.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, debugButton) && !gameWon) {
                        if (debugMode)
                            debugMode = false;
                        else
                            debugMode = true;
                    }
                    if (ClickedOn(window, test1Button)) {
                        board.Clear();
                        board.GenerateTiles("testboard1");
                        gameOver = false;
                        gameWon = false;
                        resetButton.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, test2Button)) {
                        board.Clear();
                        board.GenerateTiles("testboard2");
                        gameOver = false;
                        gameWon = false;
                        resetButton.setTexture(Textures::Get("face_happy"));
                    }
                    if (ClickedOn(window, test3Button)) {
                        board.Clear();
                        board.GenerateTiles("testboard3");
                        gameOver = false;
                        gameWon = false;
                        resetButton.setTexture(Textures::Get("face_happy"));
                    }
                    if (sf::Mouse::getPosition(window).y < stoi(rows) * 32 && sf::Mouse::getPosition(window).x < stoi(columns) * 32 && !gameWon && !gameOver) {
                        if (board.Reveal(sf::Mouse::getPosition(window).y / 32, sf::Mouse::getPosition(window).x / 32)) {
                            gameOver = true;
                            board.RevealMines();
                            resetButton.setTexture(Textures::Get("face_lose"));
                        }
                        if (board.Won()) {
                            gameWon = true;
                            debugMode = false;
                            resetButton.setTexture(Textures::Get("face_win"));
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                    if (sf::Mouse::getPosition(window).y < stoi(rows) * 32 && sf::Mouse::getPosition(window).x < stoi(columns) * 32 && !gameWon && !gameOver)
                        board.Flag(sf::Mouse::getPosition(window).y / 32, sf::Mouse::getPosition(window).x / 32);
            }
        }

        window.clear();
        board.Draw(window, (gameOver || debugMode));
        window.draw(resetButton);
        window.draw(debugButton);
        window.draw(test1Button);
        window.draw(test2Button);
        window.draw(test3Button);
        window.display();
    }

    Textures::Clear();
    return 0;
}