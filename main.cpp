#include <bits/stdc++.h>
using namespace std;

//Vector Types
struct vector2D{
    double x=0;
    double y=0;

    void scale(double val);
    void add(vector2D v);
    void subtract(vector2D v);
    int dot(vector2D v);
};
//member fucntions
void vector2D::scale(double val){
    x*=val;
    y*=val;
}
void vector2D::add(vector2D v){
    x+=v.x;
    y+=v.y;
}
void vector2D::subtract(vector2D v){
    x+=v.x*(-1);
    y+=v.y*(-1);
}
int vector2D::dot(vector2D v){
    return (x*v.x) + (y*v.y);
}
int main(){
}
