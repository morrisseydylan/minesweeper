#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;

class Textures
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string name);
public:
	static sf::Texture& Get(string name);
	static void Clear();
};

