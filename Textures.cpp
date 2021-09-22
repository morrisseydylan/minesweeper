#include "Textures.h"

unordered_map<string, sf::Texture> Textures::textures;

void Textures::LoadTexture(string name) {
	string path = "images/" + name + ".png";
	textures[name].loadFromFile(path);
}

sf::Texture& Textures::Get(string name) {
	if (textures.find(name) == textures.end())
		LoadTexture(name);
	return textures[name];
}

void Textures::Clear() {
	textures.clear();
}