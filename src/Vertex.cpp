#include "../include/Vertex.hpp"
#include <iostream>

using namespace std;

Vertex::Vertex(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vertex::Vertex(){

}


double Vertex::get_x(){
    return this->x;
}
double Vertex::get_y(){
    return this->y;
}
double Vertex::get_z(){
    return this->z;
}

Vertex Vertex::operator+(const Vertex &obj){
    Vertex tmp;

    tmp.x = this->x + obj.x;
    tmp.y = this->y + obj.y;
    tmp.z = this->z + obj.z;

    return tmp;
}
Vertex Vertex::operator-(const Vertex &obj){
    Vertex tmp;

    tmp.x = this->x - obj.x;
    tmp.y = this->y - obj.y;
    tmp.z = this->z - obj.z;

    return tmp;
}
Vertex Vertex::operator*(const Vertex &obj){
    Vertex tmp;

    tmp.x = this->x * obj.x;
    tmp.y = this->y * obj.y;
    tmp.z = this->z * obj.z;

    return tmp;
}
Vertex Vertex::operator*(const double obj){
    Vertex tmp;

    tmp.x = this->x * obj;
    tmp.y = this->y * obj;
    tmp.z = this->z * obj;

    return tmp;
}

arma::Col<double> Vertex::h(){
    arma::Col<double> coordh = {this->x,this->y,this->z,1};
    
    return coordh;
}