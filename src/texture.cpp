#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"

#include <iostream>
#include <vector>

Texture::Texture() {
    glGenTextures(1, &ID);
}

Texture::~Texture() {
    if (ID) glDeleteTextures(1, &ID);
}

bool Texture::loadFromFile(const std::string& path, bool flipVertically) {
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << "\n";
        return false;
    }

    createFromData(data, width, height, channels);
    stbi_image_free(data);

    std::cout << "Loaded texture: " << path
              << " (" << width << "x" << height << ", " << channels << "ch)\n";
    return true;
}

void Texture::generateCheckerboard(int size, int checkSize) {
    width    = size;
    height   = size;
    channels = 3;

    std::vector<unsigned char> data(size * size * 3);

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            bool white = ((x / checkSize) + (y / checkSize)) % 2 == 0;
            unsigned char c = white ? 220 : 60;
            int idx = (y * size + x) * 3;
            data[idx + 0] = c;
            data[idx + 1] = c;
            data[idx + 2] = c;
        }
    }

    createFromData(data.data(), size, size, 3);
    std::cout << "Generated checkerboard texture (" << size << "x" << size << ")\n";
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::createFromData(const unsigned char* data, int w, int h, int ch) {
    GLenum format = GL_RGB;
    if (ch == 1) format = GL_RED;
    else if (ch == 4) format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format),
                 w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}
