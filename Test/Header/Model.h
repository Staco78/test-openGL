#pragma once

#include <vector>
#include <string>

#include <Glm/vec2.hpp>
#include <Glm/vec3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "stb_image.h"

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;  // nous mémorisons le chemin d’accès pour comparaison avec d’autres textures
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    /*  Données du modèle  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /*  Fonctions  */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader shader);
private:
    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh();
};

class Model
{
    public:
        /*  Fonctions   */
        Model(char* path)
        {
            loadModel(path);
        }
        void Draw(Shader shader);
    private:
        /*  Données du modèle  */
        std::vector<Mesh> meshes;
        std::string directory;
        /*  Fonctions   */
        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        std::vector<Texture> textures_loaded;
};