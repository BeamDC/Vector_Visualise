#include <bits/stdc++.h>
using namespace std;

//Vector Types
struct vector2D{
    double x=0;
    double y=0;

    void print();
    void scale(double val);
    void rotate(double angle);
    void normalize();
    void add(vector2D v);
    void subtract(vector2D v);
    double dot(vector2D v);
};

//2D member functions
void vector2D::print(){
    printf("[%lf, %lf]\n",x,y);
}
void vector2D::scale(double val){
    x*=val;
    y*=val;
}
void vector2D::rotate(double angle){
    angle = angle * M_PI / 180; // convert to degrees
    double cx = x;
    double cy = y;
    x=(cx*cos(angle)) - (cy*sin(angle));
    y=(cx*sin(angle)) + (cy*cos(angle));
}
void vector2D::normalize(){
    double m = sqrt(x*x + y*y);
    x/=m;
    y/=m;
}
void vector2D::add(vector2D v){
    x+=v.x;
    y+=v.y;
}
void vector2D::subtract(vector2D v){
    x+=v.x*(-1);
    y+=v.y*(-1);
}
double vector2D::dot(vector2D v){
    return (x*v.x) + (y*v.y);
}

int main(){
    vector2D test;
    test.x=4;
    test.y=-2;
    test.print();
    test.rotate(45);
    test.print();
}
