#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"
#include <string>
#include <iostream>
#include <armadillo>
using namespace std;

class Object     
{
protected:     
    vector <Vertex> vertices;
    vector <Face> faces;
    string tipoArchivo;
    float r,g,b;
public:
    Object(string file, string tipoArchivo,float r,float g,float b);
    Object();
    vector <string> split(string str, string delim); 
    void draw(arma::Mat<double> MC);
    void load(string file, string tipoArchivo ,float r,float g,float b);
    vector<Face> get_Faces();
    vector<Vertex> get_vertices();
    void calculoNormal();
};

#endif