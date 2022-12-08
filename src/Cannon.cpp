#include <armadillo>
#include "../include/Transform.hpp"
#include "../include/Cannon.hpp"
#include "../include/Curve.hpp"


//1.0, 1.0, 0.0, 0.0
//0.0, 1.0, 0.0
//0.0, 0.0, 1.0

Cannon::Cannon(double grad)
{
    this->wheel.load("models/ball.obj",".obj", 1.0, 1.0, 0.0);
    this->body.load("models/cube.obj",".obj", 0.0, 1.0, 0.0);
    this->bullet.load("models/ball.obj",".obj", 0.0, 0.0, 1.0);
    this->inclinacion = grad; 
    this->shooted = false;
}

void Cannon::setterInclinacion(double grad)
{
    this->inclinacion = grad;
}

double Cannon::getterInclinacion(){
     return this->inclinacion;
     }

void Cannon::shoot(double fuerza){
    
    Transform tr;
    this->shooted = true;
    Vertex P1 (-0.9,0.2,0.0);
    Vertex P2 (-0.4,0.2+(this->inclinacion/10),0.0);
    Vertex P3 ((-P2.get_x())*fuerza,P2.get_y(),0.0);
    Vertex P4 ((-P2.get_x())+P3.get_x(),0.0,0.0);    
    Curve trayect(P1,P2,P3,P4,0.01);
    this->curve = trayect.get();
}


void Cannon::plot()
{
        Transform tr;

    //Rueda del cañon
    arma::Mat<double> S = tr.S(0.1,0.1,0.1);
    arma::Mat<double> T = tr.T(-0.9,0,0);
    arma:: Mat<double> MC = T*S;
    this->wheel.draw(MC);
    //Rueda del cañon
    arma::Mat<double> SC = tr.S(0.4,0.2,0.2);
    arma::Mat<double> RC = tr.Rz(this->inclinacion);
    arma::Mat<double> TC = tr.T(-0.85,0.1,0);
    arma:: Mat<double> MC2 = TC*RC*SC;
    this->body.draw(MC2);

    if(!this->shooted){
    //Bala del cañon
    arma::Mat<double> SB = tr.S(0.07,0.07,0.07);
    arma::Mat<double> TB = tr.T(-0.9,0.2,0);
    arma:: Mat<double> MC3 = TB*SB;
    this->bullet.draw(MC3);
    }
    else{
        Vertex vc = this->curve[this->posCurva];
        arma::Mat<double> BBS = tr.S(0.07,0.07,0.07);
        arma::Mat<double> BBT = tr.T(vc.get_x(),vc.get_y(),vc.get_z());
        this->bullet.draw(BBT*BBS);
        if(this->posCurva < this->curve.size()-1)
            this->posCurva++;
    }
}


bool Cannon::fueDisparado(){
    return this->shooted;
}

void Cannon::resetear(){
    this->shooted = false;
    this->posCurva = 0;
    this->curve.clear();
}