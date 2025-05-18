#pragma once

#include <string>
#include <glad/glad.h>

class Texture {
public:
    unsigned int ID = 0;
    int width  = 0;
    int height = 0;
    int channels = 0;

    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    bool loadFromFile(const std::string& path, bool flipVertically = true);
    void generateCheckerboard(int size = 256, int checkSize = 32);
    void bind(unsigned int unit = 0) const;

private:
    void createFromData(const unsigned char* data, int w, int h, int ch);
};
