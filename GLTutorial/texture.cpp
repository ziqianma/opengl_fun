#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  

Texture::Texture(int textureUnit, std::string path) {
	_textureUnit = textureUnit;
	_path = path;
	glGenTextures(1, &_textureID);
}

void TextureLoader::addTexture(int textureUnit, Texture tex) {
	textures.insert(std::pair<int, Texture>(textureUnit, tex));
}

void TextureLoader::loadTexture(int textureUnit) {
    auto iterator = textures.find(textureUnit);
    unsigned int textureID;

    if (iterator == textures.end()) {
        std::cerr << "Error, did not add texture to loader." << std::endl;
        return;
    }
    else {
        textureID = iterator->second.getTextureId();
    }

	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load in texture data
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    std::string path = iterator->second.getPath();
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        std::string extension = path.substr(path.find("."), path.length());
        GLint internalFormat = extension == ".png" ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	
}

void TextureLoader::bindTextures() {
    for (auto entry : textures) {
        int textureUnit = entry.first;
        Texture tex = entry.second;

        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, tex.getTextureId());
    }
}   

void TextureLoader::deleteTexture(int textureUnit) {
	textures.erase(textureUnit);
}
