#ifndef VECTOR_VISUALIZE_H
#define VECTOR_VISUALIZE_H

#include <cmath>
#include <iostream>

//Vector Types
struct vector2D{
    double x;
    double y;
};

//2D functions
void print(vector2D v){
    printf("[%f, %f]\n",v.x,v.y);
}

double magnitude(vector2D v){
    return sqrt(v.x*v.x + v.y*v.y);
}
double dot(vector2D v, vector2D w){
    return (v.x*w.x) + (v.y*w.y);
}

vector2D rotate(vector2D v, double angle){ //rotate clockwise
    vector2D r{};
    angle = angle * M_PI / -180; // convert to degrees
    double cx = v.x;
    double cy = v.y;
    r.x=(cx*cos(angle)) - (cy*sin(angle));
    r.y=(cx*sin(angle)) + (cy*cos(angle));
    return r;
}
vector2D add(vector2D v, vector2D w){
    vector2D r{};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    return r;
}
vector2D normalize(vector2D v){
    vector2D r{};
    double m = magnitude(v);
    r.x=v.x/m;
    r.y=v.y/m;
    return r;
}
vector2D scale(vector2D v, double val){
    vector2D r{};
    r.x= v.x * val;
    r.y= v.y * val;
    return r;
}

#endif
