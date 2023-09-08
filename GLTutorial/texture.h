#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>

class Texture {
private:
	unsigned int _textureID;
	int _textureUnit;
	std::string _path;
public:
	Texture() {};
	Texture(int textureUnit, std::string path);
	int getTextureUnit() { return _textureUnit; }
	unsigned int getTextureId() { return _textureID; }
	std::string getPath() { return _path; }
};

class TextureLoader {
private:
	std::map<int, Texture> textures;
public:
	void loadTexture(int textureUnit);
	void addTexture(int textureUnit, Texture tex);
	void deleteTexture(int textureUnit);
	void bindTextures();
};