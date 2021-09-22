#include "MineCounter.h"
MineCounter::MineCounter(int rows, int mines) : size(21, 32), hyphen(Textures::Get("digits")) {
    count = "000";
    Negative = false;
    hyphen.setTextureRect(sf::IntRect(digits[10], size));
    hyphen.setPosition(0.0f, rows * 32.0f);
    sprites[0].setPosition(21.0f, rows * 32.0f);
    sprites[1].setPosition(42.0f, rows * 32.0f);
    sprites[2].setPosition(63.0f, rows * 32.0f);
    AssignCountValue(to_string(mines));
    UpdateTextures();
}
void MineCounter::AssignCountValue(string rhs) {
    if (rhs.length() == 1) {
        count[0] = '0';
        count[1] = '0';
        count[2] = rhs[0];
    }
    else if (rhs.length() == 2) {
        count[0] = '0';
        count[1] = rhs[0];
        count[2] = rhs[1];
    }
    else
        count = rhs;
}
void MineCounter::UpdateTextures() {
    SetRectangles(count[0], sprites[0]);
    SetRectangles(count[1], sprites[1]);
    SetRectangles(count[2], sprites[2]);
}
void MineCounter::SetRectangles(char& countDigit, sf::Sprite& sprite) {
    switch (countDigit) {
    case '0': {
        sprite.setTextureRect(sf::IntRect(digits[0], size));
        break;
    }
    case '1': {
        sprite.setTextureRect(sf::IntRect(digits[1], size));
        break;
    }
    case '2': {
        sprite.setTextureRect(sf::IntRect(digits[2], size));
        break;
    }
    case '3': {
        sprite.setTextureRect(sf::IntRect(digits[3], size));
        break;
    }
    case '4': {
        sprite.setTextureRect(sf::IntRect(digits[4], size));
        break;
    }
    case '5': {
        sprite.setTextureRect(sf::IntRect(digits[5], size));
        break;
    }
    case '6': {
        sprite.setTextureRect(sf::IntRect(digits[6], size));
        break;
    }
    case '7': {
        sprite.setTextureRect(sf::IntRect(digits[7], size));
        break;
    }
    case '8': {
        sprite.setTextureRect(sf::IntRect(digits[8], size));
        break;
    }
    case '9': {
        sprite.setTextureRect(sf::IntRect(digits[9], size));
        break;
    }
    }
}
void MineCounter::Draw(sf::RenderWindow& window) {
    if (Negative)
        window.draw(hyphen);
    for (sf::Sprite sprite : sprites)
        window.draw(sprite);
}
void MineCounter::Add() {
    int countInt = stoi(count);
    if (Negative) {
        if (countInt == 1) {
            Negative = false;
            count = "000";
            UpdateTextures();
            return;
        }
        else
            countInt--;
    }
    else
        countInt++;
    AssignCountValue(to_string(countInt));
    UpdateTextures();
}
void MineCounter::Subtract() {
    int countInt = stoi(count);
    if (countInt != 0) {
        if (Negative)
            countInt++;
        else
            countInt--;
    }
    else {
        Negative = true;
        count = "001";
        UpdateTextures();
        return;
    }
    AssignCountValue(to_string(countInt));
    UpdateTextures();
}