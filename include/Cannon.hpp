#ifndef CANNON_H
#define CANNON_H
#include "Object.hpp"
#pragma once

class Cannon
{
public:
    vector<Vertex> curve;
    Cannon(double grados);
    void plot();
    void shoot(double fuerza);
    bool fueDisparado();
    double getterInclinacion();
    void resetear();
    void setterInclinacion(double grados);
private:
    string tipoArchivo;
    unsigned int posCurva;
    bool shooted;
    double inclinacion;
    Object body;
    Object wheel;
    Object bullet;
};

#endif