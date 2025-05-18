#pragma once

#include <string>
#include <vector>
#include "mesh.h"

class Model {
public:
    explicit Model(const std::string& path);

    void draw() const;

private:
    std::vector<Mesh> meshes;
    void loadModel(const std::string& path);
};
