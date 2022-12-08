#ifndef VERTEX_H
#define VERTEX_H

#pragma once
#include <armadillo>

class Vertex
{
private:
    double x;
    double y;
    double z;
public:
    Vertex(double x, double y, double z);
    Vertex();
    Vertex operator+(const Vertex &obj);
    Vertex operator-(const Vertex &obj);
    Vertex operator*(const Vertex &obj);
    Vertex operator*(const double obj);
    double get_x();
    double get_y();
    double get_z();
    arma::Col<double> h();
};

#endif