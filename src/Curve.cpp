#include "../include/Curve.hpp"
#include <armadillo>

Curve::Curve(Vertex P1, Vertex P2,Vertex P3,Vertex P4,double dt)
{
    arma:: Mat<double> MB = {{-1, 3, -3, 1},
                            {3, -6, 3, 0},
                            {-3, 3, 1, 0},
                            {1, 0, 0, 0}};
    arma:: Mat<double> Gb = {{P1.get_x(),P1.get_y(),P1.get_z()},
                            {P2.get_x(),P2.get_y(),P2.get_z()},
                            {P3.get_x(),P3.get_y(),P3.get_z()},
                            {P4.get_x(),P4.get_y(),P4.get_z()}};
    for(double t=0; t<= 1.0 + dt; t+=dt){
        arma:: Row<double> T = {pow(t,3),pow(t,2),t,1};

        arma:: Mat<double> Qt = T * MB * Gb;

        Vertex nv(Qt[0,0],Qt[0,1],Qt[0,2]);
        this->curve.push_back(nv);
    }
}

vector <Vertex> Curve::get(){
    return this->curve;
}

