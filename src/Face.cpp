#include "../include/Face.hpp"
#include <armadillo>

Face::Face(vector<unsigned int> indices)
{
    this->indices = indices;
    this->A=0; this->B=0; this->C=0; this->D=0;
}

void Face::vectorNormal(vector<Vertex> vertices){
    Vertex a = vertices[this->indices[0]];
    Vertex b = vertices[this->indices[1]];
    Vertex c = vertices[this->indices[2]];
    arma::vec v1 = {a.get_x(),a.get_y(),a.get_z()};
    arma::vec v2 = {b.get_x(),b.get_y(),b.get_z()};
    arma::vec v3 = {c.get_x(),c.get_y(),c.get_z()};
    arma::vec normal = arma::cross((v2-v1),(v3-v1));
    this->A = normal[0];
    this->B = normal[1];
    this->C = normal[2];
    this->D = -((this->A * v1[0]) + (this->B * v1[1]) + (this->C * v1[2]) );
}

vector<unsigned int> Face::getIndices_Vertices()
{
    return this->indices;
}