#ifndef RENDER_H
#define RENDER_H
#include <cmath>
#include <iostream>

//Types
struct point2D{
    double x;
    double y;
    double z = 0.0;
};
struct point3D{
    double x;
    double y;
    double z;
};

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

struct plane{
    //intercepts 
    double x_int;
    double y_int;
    double z_int;

    //equation values
    double a;
    double b;
    double c;
    double d;

    //normal vector
    vector3D normal{};
};

/** 2D vector functions **/
void print(vector2D v){
    printf("[%f, %f]\n",v.x,v.y);
}

double magnitude(vector2D v){
    return sqrt(v.x*v.x + v.y*v.y);
}
double dot(vector2D v, vector2D w){
    return (v.x*w.x) + (v.y*w.y);
}

vector2D construct(point2D a, point2D b){
    vector2D r{};
    r.x = b.x - a.x;
    r.y = b.y - a.y;
    return r;
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

/** 3D vector functions **/
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

vector3D construct(point3D a, point3D b){
    vector3D r{};
    r.x = b.x - a.x;
    r.y = b.y - a.y;
    r.z = b.z - a.z;
    return r;
}
vector3D add(vector3D v, vector3D w){
    vector3D r{};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    r.z = v.z + w.z;
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

/** PLANES **/
plane contstruct(point3D A, point3D B, point3D C){
    plane r{};
    vector3D AB = construct(A,B);
    vector3D AC = construct(A,C);
    
    //normal vector
    r.normal = normalize(cross(AB,AC));

    //equation
    r.a = r.normal.x;
    r.b = r.normal.y;
    r.c = r.normal.z;
    r.d = r.a * A.x + r.b * A.y + r.c * A.z;
    
    //intercepts
    
    
    return r;
}

#endif //RENDER_H
