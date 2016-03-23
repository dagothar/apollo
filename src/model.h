#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glut.h>

//#include "log.h"

struct Material {
    std::string name;
    
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    
    GLfloat shininess;
};

struct Vertex;

struct Vertex {
    GLfloat x[3];
    
    Vertex();
    Vertex(GLfloat _x, GLfloat _y, GLfloat _z);
};

typedef struct {
    int normal;
    int vertex[3];
    
    int material;
} Face;

class Model {
    public:
        Model();

        void load(const char *filename);
        void display();
        void _display();
    
    private:
        std::string matfile;
    
        std::vector<Material> materials;
        std::vector<Vertex> vertex;
        std::vector<Vertex> normals;
        std::vector<Face> faces;
    
        GLuint display_list;
    
        void load_materials();
        void make_list();
};

#endif
