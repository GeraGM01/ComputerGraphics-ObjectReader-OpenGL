#ifndef MODELS_H
#define MODELS_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Face.hpp"
using namespace std;

class Models
{
protected:
    vector<Vertex> vertices;
    vector<Face> faces;
    string name;
    Models(string objfile);
    vector<string> split(string str, string delim);
    virtual void load() = 0;
public:
    vector<Face> get_Faces();
    vector<Vertex> get_vertices();
    void draw();
};

#endif