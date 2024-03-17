#ifndef VECTORS_H
#define VECTORS_H
#include <cmath>
#include <iostream>

//Vector Types
struct vector2D{
    double x;
    double y;
    double z = 0.0;
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

    r.x = (v.x*cos(angle)) - (v.y*sin(angle));
    r.y = (v.x*sin(angle)) + (v.y*cos(angle));
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
    r.x = v.x/m;
    r.y = v.y/m;
    return r;
}
vector2D scale(vector2D v, double val){
    vector2D r{};
    r.x = v.x * val;
    r.y = v.y * val;
    return r;
}
vector2D opposite(vector2D v){
    vector2D r{};
    r.x = v.x * -1;
    r.y = v.y * -1;
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

vector3D yaw(vector3D v, double yaw){ //rotate about the z-axis
    vector3D r{};
    yaw = yaw * M_PI / -180;
    r.x = v.x * cos(yaw) - v.y * sin(yaw);
    r.y = v.x * sin(yaw) + v.y * sin(yaw);
    r.z = v.z;
    return r;
}
vector3D pitch(vector3D v, double pitch){ //rotate about the y-axis
    vector3D r{};
    pitch = pitch * M_PI / -180;
    r.x = v.x * cos(pitch) + v.z * sin(pitch);
    r.y = v.y;
    r.z = v.z * cos(pitch) - v.x * sin(pitch);
    return r;
}
vector3D roll(vector3D v, double roll){ //rotate about the x-axis
    vector3D r{};
    roll = roll * M_PI / -180;
    r.x = v.x;
    r.y = v.y * cos(roll) - v.z * sin(roll);
    r.z = v.y * sin(roll) + v.z * cos(roll);
    return r;
}

vector3D add(vector3D v, vector3D w){
    vector3D r{};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    r.y = v.z + w.z;
    return r;
}
vector3D opposite(vector3D v){
    vector3D r{};
    r.x = v.x * -1;
    r.y = v.y * -1;
    r.z = v.z * -1;
    return r;
}
vector3D normalize(vector3D v){
    vector3D r{};
    double m = magnitude(v);
    r.x = v.x/m;
    r.y = v.y/m;
    r.z = v.z/m;
    return r;
}
vector3D scale(vector3D v, double val){
    vector3D r{};
    r.x = v.x * val;
    r.y = v.y * val;
    r.z = v.z * val;
    return r;
}
vector3D cross(vector3D v, vector3D w){
    vector3D r;
    r.x = (v.y * w.z) - (w.y * v.z);
    r.y = (v.z * w.x) - (w.z * v.x);
    r.z = (v.x * w.y) - (w.x * v.y);
    return r;
}

#endif //VECTOR_VISUALIZE_H
