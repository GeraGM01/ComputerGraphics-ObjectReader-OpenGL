#include "../include/Transform.hpp"

Transform::Transform()
{
}

arma::Mat<double> Transform::T (double dx,double dy,double dz)
{
    arma::Mat<double> t= {{1, 0, 0, dx},
                        {0, 1, 0, dy},
                        {0, 0, 1, dz},
                        {0, 0, 0, 1 }};
    return t;
}
arma::Mat<double> Transform::S (double sx,double sy,double sz)
{
    arma::Mat<double> s= {{sx, 0, 0, 0},
                         {0, sy, 0, 0},
                         {0, 0, sz, 0},
                         {0, 0, 0, 1 }};
    return s;
}
arma::Mat<double> Transform::Rx(double theta)
{
    double pi = 3.1415926535;
    double grad = theta * ( pi / 180);
    arma::Mat<double> r = {{1, 0, 0, 0},
                          {0, cos(grad), -sin(grad), 0},
                          {0, sin(grad), cos(grad),0},
                          {0, 0, 0, 1}};
    return r;
}
arma::Mat<double> Transform::Ry(double theta)
{
    double pi = 3.1415926535;
    double grad = theta * (pi /180);
    arma::Mat<double> r = {{cos(grad), 0, sin(grad), 0},
                          {0, 1, 0, 0},
                          {-sin(grad),0, cos(grad), 0},
                          {0, 0, 0, 1}};
    return r;
}
arma::Mat<double> Transform::Rz(double theta)
{
    double pi = 3.1415926535;
    double grad = theta * (pi /180);
    arma::Mat<double> r = {{cos(grad), -sin(grad), 0, 0},
                          {sin(grad), cos(grad), 0, 0},
                          {0, 0, 1, 0},
                          {0, 0, 0, 1}};
    return r;
}

arma::Mat<double> Transform::Rv1v2(Vertex v1, Vertex v2, double theta){
  //Primer Paso
  arma::Mat<double> T1 = this->T(-v1.get_x(),-v1.get_y(),-v1.get_z());
  //Segundo Paso
  double D1 = sqrt (pow(v2.get_z()-v1.get_z(),2) + pow(v2.get_x() - v1.get_x(),2));
  arma::Mat<double> Ry2 = {{(v2.get_z()-v1.get_z())/D1, 0, -(v2.get_x() - v1.get_x())/D1, 0},
                           {0,1,0,0},
                           {(v2.get_x()-v1.get_x())/D1, 0, (v2.get_z()-v1.get_z())/D1, 0},
                           {0, 0, 0, 1}};
    
  //Segundo Paso
  double D2 = sqrt (pow(v2.get_z()-v1.get_z(),2) + pow(v2.get_x() - v1.get_x(),2) + pow(v2.get_y() - v1.get_y(),2));
  arma::Mat<double> Rx3 = {{1, 0, 0, 0},
                           {0, D1/D2, -(v2.get_y() - v1.get_y())/D2,0},
                           {0, (v2.get_y() - v1.get_y())/D2, D1/D2, 0},
                           {0,0,0,1}};
  //Cuarto paso
  arma::Mat<double> Rz4 = this->Rz(theta);
  //Inversa 3r paso
  arma::Mat<double> iRx3 = Rx3.i();
  //Inversa 2do paso
  arma::Mat<double> iRy2 = Ry2.i();
  //Inversa 1er paso
  arma::Mat<double> iT1 = T1.i();
  return(iT1 * iRy2 * iRx3 * Rz4 * Rx3 * Ry2 * T1);

}
