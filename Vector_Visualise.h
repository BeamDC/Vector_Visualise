#ifndef VECTOR_VISUALISE_H
#define VECTOR_VISUALISE_H
#include <cmath>
#include <iostream>

//Types
struct point3D{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
struct vector3D{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
struct plane{
    point3D pointA;
    point3D pointB;
    point3D pointC;

    vector3D normal{};
};

/** point functions **/
void print(point3D p){
    printf("(%f, %f, %f)\n",p.x,p.y,p.z);
}
point3D rotate(point3D p, double yaw, double pitch, double roll){
    point3D r{};

    double DegToRad = M_PI / 180;
    yaw *= DegToRad;
    pitch *= DegToRad;
    roll *= DegToRad;

    double yawCos = cos(yaw);
    double pitchCos = cos(pitch);
    double rollCos = cos(roll);
    double yawSin = sin(yaw);
    double pitchSin = sin(pitch);
    double rollSin = sin(roll);

    double xx = yawCos * pitchCos;
    double xy = yawCos * pitchSin * rollSin - yawSin * rollCos;
    double xz = yawCos * pitchSin * rollCos + yawSin * rollSin;

    double yx = yawSin * pitchCos;
    double yy = yawSin * pitchSin * rollSin + yawCos * rollCos;
    double yz = yawSin * pitchSin * rollCos - yawCos * rollSin;

    double zx = -pitchSin;
    double zy = pitchCos * rollSin;
    double zz = pitchCos * rollCos;

    r.x = xx * p.x + xy * p.y + xz * p.z;
    r.y = yx * p.x + yy * p.y + yz * p.z;
    r.z = zx * p.x + zy * p.y + zz * p.z;
    
    return r;
}

/** vector functions **/
void print(vector3D v){
    printf("[%f, %f, %f]\n",v.x,v.y,v.z);
}

double magnitude(vector3D v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
double dot(vector3D v, vector3D w){
    return (v.x*w.x) + (v.y*w.y) + (v.z*w.z);
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
vector3D rotate(vector3D v, double yaw, double pitch, double roll){
    vector3D r{};

    double DegToRad = M_PI / 180;
    yaw *= DegToRad;
    pitch *= DegToRad;
    roll *= DegToRad;

    double yawCos = cos(yaw);
    double pitchCos = cos(pitch);
    double rollCos = cos(roll);
    double yawSin = sin(yaw);
    double pitchSin = sin(pitch);
    double rollSin = sin(roll);

    double xx = yawCos * pitchCos;
    double xy = yawCos * pitchSin * rollSin - yawSin * rollCos;
    double xz = yawCos * pitchSin * rollCos + yawSin * rollSin;

    double yx = yawSin * pitchCos;
    double yy = yawSin * pitchSin * rollSin + yawCos * rollCos;
    double yz = yawSin * pitchSin * rollCos - yawCos * rollSin;

    double zx = -pitchSin;
    double zy = pitchCos * rollSin;
    double zz = pitchCos * rollCos;

    r.x = xx * v.x + xy * v.y + xz * v.z;
    r.y = yx * v.x + yy * v.y + yz * v.z;
    r.z = zx * v.x + zy * v.y + zz * v.z;

    return r;
}

/** PLANES **/
void print(plane P){
    printf("Normal:  (%f, %f, %f)\n\n",P.normal.x,P.normal.y,P.normal.z);
    printf("Point A: (%f, %f, %f)\n",P.pointA.x,P.pointA.y,P.pointA.z);
    printf("Point B: (%f, %f, %f)\n",P.pointB.x,P.pointB.y,P.pointB.z);
    printf("Point C: (%f, %f, %f)\n",P.pointC.x,P.pointC.y,P.pointC.z);
}

plane construct(point3D A, point3D B, point3D C){
    plane r{};

    r.pointA = A;
    r.pointB = B;
    r.pointC = C;
    
    vector3D AB = construct(A,B);
    vector3D AC = construct(A,C);
    r.normal = normalize(cross(AB,AC));
    
    return r;
}
plane rotate(plane P, double yaw, double pitch, double roll){
    plane r{};

    r.normal = rotate(P.normal,yaw,pitch,roll);
    r.pointA = rotate(P.pointA,yaw,pitch,roll);
    r.pointB = rotate(P.pointB,yaw,pitch,roll);
    r.pointC = rotate(P.pointC,yaw,pitch,roll);

    return r;
}
double* getEquation(plane P){
    static double eqn[4];
    
    eqn[0] = P.normal.x;
    eqn[1] = P.normal.y;
    eqn[2] = P.normal.z;
    eqn[3] = -P.normal.x * P.pointA.x + P.normal.y * P.pointA.y + P.normal.z * P.pointA.z;

    return eqn;
}
point3D* getIntercepts(plane P){
    static point3D xyz_ints[3];
    double* e = getEquation(P);

    xyz_ints[0].x = -(e[3]/e[0]);
    xyz_ints[1].y = -(e[3]/e[1]);
    xyz_ints[2].z = -(e[3]/e[2]);
    
    return xyz_ints;
}

#endif //VECTOR_VISUALISE_H
