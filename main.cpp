#include <bits/stdc++.h>
using namespace std;

//Vector Types
struct vector2D{
    double x=0;
    double y=0;

    void scale(double val);
    void add(vector2D v);
    void subtract(vector2D v);
    double dot(vector2D v);
    void normalize();
};

//Member functions
void vector2D::scale(double val){
    x*=val;
    y*=val;
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
}
