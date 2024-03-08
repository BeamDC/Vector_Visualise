#ifndef VECTOR_VISUALIZE_H
#define VECTOR_VISUALIZE_H
#include <cmath>
#include <iostream>

//Vector Types
struct vector2D{
    double x;
    double y;
};
struct vector3D{
    double x;
    double y;
    double z;
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

//3D functions
void print(vector3D v){
    printf("[%f, %f, %f]\n",v.x,v.y,v.z);
}

double magnitude(vector3D v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
double dot(vector3D v, vector3D w){
    return (v.x*w.x) + (v.y*w.y) + (v.z*w.z);
}

//3d rotation is evil
//use pitch and yaw for rotaions in 3D
//Vector3D pitch()
//Vector3D yaw()

vector3D add(vector3D v, vector3D w){
    vector3D r{};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    r.y = v.z + w.z;
    return r;
}
vector3D normalize(vector3D v){
    vector3D r{};
    double m = magnitude(v);
    r.x=v.x/m;
    r.y=v.y/m;
    r.z=v.z/m;
    return r;
}
vector3D scale(vector3D v, double val){
    vector3D r{};
    r.x= v.x * val;
    r.y= v.y * val;
    r.z= v.z * val;
    return r;
}

#endif //VECTOR_VISUALIZE_H
