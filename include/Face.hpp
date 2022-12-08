#ifndef FACE_H
#define FACE_H

#pragma once

#include <vector>
#include "Vertex.hpp"

using namespace std;

class Face
{
private:
    vector <unsigned int> indices;
    float A,B,C,D;
public:
    Face(vector<unsigned int>indices);
    vector <unsigned int> getIndices_Vertices();
    void vectorNormal(vector<Vertex> vertices);
};

#endif