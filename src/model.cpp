#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "model.h"

#include <iostream>
#include <unordered_map>

/* Simple hash for deduplicating vertices by their index triple. */
struct IndexHash {
    size_t operator()(const std::tuple<int,int,int>& t) const {
        auto h1 = std::hash<int>{}(std::get<0>(t));
        auto h2 = std::hash<int>{}(std::get<1>(t));
        auto h3 = std::hash<int>{}(std::get<2>(t));
        return h1 ^ (h2 << 11) ^ (h3 << 22);
    }
};

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::draw() const {
    for (const auto& mesh : meshes)
        mesh.draw();
}

void Model::loadModel(const std::string& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!warn.empty()) std::cerr << "OBJ WARNING: " << warn << "\n";
    if (!err.empty())  std::cerr << "OBJ ERROR: "   << err  << "\n";
    if (!ok) {
        std::cerr << "Failed to load OBJ: " << path << "\n";
        return;
    }

    for (const auto& shape : shapes) {
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::unordered_map<std::tuple<int,int,int>, unsigned int, IndexHash> uniqueVerts;

        for (const auto& index : shape.mesh.indices) {
            auto key = std::make_tuple(index.vertex_index,
                                       index.normal_index,
                                       index.texcoord_index);

            if (uniqueVerts.count(key)) {
                indices.push_back(uniqueVerts[key]);
                continue;
            }

            Vertex vertex{};

            // Position (required)
            vertex.Position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            // Normal
            if (index.normal_index >= 0) {
                vertex.Normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }

            // Texture coordinates
            if (index.texcoord_index >= 0) {
                vertex.TexCoords = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
            }

            auto idx = static_cast<unsigned int>(vertices.size());
            uniqueVerts[key] = idx;
            vertices.push_back(vertex);
            indices.push_back(idx);
        }

        meshes.emplace_back(std::move(vertices), std::move(indices));
    }

    std::cout << "Loaded model: " << path
              << " (" << meshes.size() << " mesh(es))\n";
}
