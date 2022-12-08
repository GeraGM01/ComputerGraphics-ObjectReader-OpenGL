#ifndef CURVE_H
#define CURVE_H

#pragma once

using namespace std;

#include <vector>
#include "Vertex.hpp"


class Curve
{
public:
    Curve(Vertex P1, Vertex P2,Vertex P3,Vertex P4,double dt);
    vector<Vertex> get();
private:
    vector<Vertex> curve;
};

#endif