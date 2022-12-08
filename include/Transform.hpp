#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once
#include <armadillo>
#include "Vertex.hpp"

class Transform
{
public:
    Transform();
    arma::Mat<double> T (double dx,double dy,double dz);
    arma::Mat<double> S (double sx, double sy, double sz);
    arma::Mat<double> Rx(double theta);
    arma::Mat<double> Ry(double theta);
    arma::Mat<double> Rz(double theta);
    arma::Mat<double> Rv1v2(Vertex v1, Vertex v2, double theta);
private:

};

#endif