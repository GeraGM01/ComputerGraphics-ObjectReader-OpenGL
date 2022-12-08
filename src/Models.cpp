#include "../include/Models.hpp"
#include <GLFW/glfw3.h>

Models::Models(string objfile)
{
    this->name = objfile;
}

vector<Face> Models::get_Faces(){
    return this->faces;
}

vector<string> Models::split(string str, string delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos=str.find(delim,prev);
        if(pos==string:: npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while(pos< str.length() && prev < str.length());
    return tokens;
}

void Models::draw(){
    glBegin(GL_TRIANGLES);
            for(Face f: this->faces){
                for(unsigned int index: f.getIndices_Vertices()){
                    double x = this->vertices[index].get_x();
                    double y = this->vertices[index].get_y();
                    double z = this->vertices[index].get_z();
                    glVertex3f(x,y,z);
                }
            }
        glEnd();
}

vector<Vertex> Models::get_vertices(){
    return this->vertices;
}