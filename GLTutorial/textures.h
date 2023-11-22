#pragma once
#include "common.h"

struct Texture {
	unsigned int id;
	std::string type; //"diffuse" or "specular"
	const char* path;
};

class TextureLoader {
public:
	static Texture loadTexture(const char* path, const std::string& directory, std::string typeName);
	static int getTexturesSize();
	static Texture getTexture(const char* path);
private:
	static std::map<const char*, Texture> loadedTextures;
	static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
};