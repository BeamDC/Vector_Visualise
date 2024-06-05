use std::default::Default;

#[derive(Debug, Clone)]
struct Point3D{
    x: f64,
    y: f64,
    z: f64,
}

#[derive(Debug, Clone)]
struct Vec3D{
    x: f64,
    y: f64,
    z: f64,
}

#[derive(Debug, Clone)]
struct Plane3D{
    a: Point3D,
    b: Point3D,
    c: Point3D,
    
    normal: Vec3D
}

/* Defaults */
impl Default for Point3D {
    fn default() -> Self {
        Self { x: 0.0, y: 0.0, z: 0.0 }
    }
}

impl Default for Vec3D {
    fn default() -> Self {
        Self { x: 0.0, y: 0.0, z: 0.0 }
    }
}

impl Default for Plane3D {
    fn default() -> Self {
        Self { 
            a: Point3D{..Default::default()}, 
            b: Point3D{..Default::default()}, 
            c: Point3D{..Default::default()},
            normal: Vec3D{..Default::default()}
        }
    }
}

/* Vector Functions */
fn magnitude(v: Vec3D) -> f64{
    (v.x * v.x + v.y * v.y + v.z * v.z).sqrt()
}

fn dot(v: Vec3D, w: Vec3D) -> f64{
    v.x * w.x + v.y * w.y + v.z * w.z
}

fn construct_vec(a: Point3D, b: Point3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = b.x - a.x;
    r.y = b.y - a.y;
    r.z = b.z - a.z;
    r
}

fn add(v: Vec3D, w: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    r.z = v.z + w.z;
    r
}

fn opposite(v: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = -v.x;
    r.y = -v.y;
    r.z = -v.z;
    r
}

fn normalize(v: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    let m:f64 = magnitude(v.clone());
    r.x = v.x / m;
    r.y = v.y / m;
    r.z = v.z / m;
    r
}

fn scale(v: Vec3D, scalar: f64) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = v.x * scalar;
    r.y = v.y * scalar;
    r.z = v.z * scalar;
    r
}

fn cross(v: Vec3D, w: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = (v.y * w.z) - (v.z * w.y);
    r.y = (v.z * w.x) - (v.x * w.z);
    r.z = (v.x * w.y) - (v.y * w.x);
    r
}

fn rotate(v: Vec3D, yaw: f64, pitch: f64, roll: f64) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    let yawCos: f64 = yaw.cos();
    let yawSin: f64 = yaw.sin();
    let pitchCos: f64 = pitch.cos();
    let pitchSin: f64 = pitch.sin();
    let rollCos: f64 = roll.cos();
    let rollSin: f64 = roll.sin();
    
    let xx = yawCos * pitchCos;
    let xy = yawCos * pitchSin * rollSin - yawSin * rollCos;
    let xz = yawCos * pitchSin * rollCos + yawSin * rollSin;
    
    let yx = yawSin * pitchCos;
    let yy = yawSin * pitchSin * rollSin + yawCos * rollCos;
    let yz = yawSin * pitchSin * rollCos - yawCos * rollSin;
    
    let zx = -pitchSin;
    let zy = pitchCos * rollSin;
    let zz = pitchCos * rollCos;
    
    r.x = xx * v.x + xy * v.y + xz * v.z;
    r.y = yx * v.x + yy * v.y + yz * v.z;
    r.z = zx * v.x + zy * v.y + zz * v.z;
    
    r
}

//rotate a vector

/* Plane Functions */
fn construct_plane(a: Point3D, b: Point3D, c: Point3D) -> Plane3D{
    let mut r = Plane3D{..Default::default()};
    r.a = a.clone();
    r.b = b.clone();
    r.c = c.clone();
    let AB:Vec3D = construct_vec(a.clone(),b);
    let AC:Vec3D = construct_vec(a,c);
    r.normal = normalize(cross(AB,AC));
    r
}

fn get_equation(p: Plane3D) -> [f64; 4]{
    let mut eqn: [f64; 4] = [0.0; 4];
    
    eqn[0] = p.normal.x;
    eqn[1] = p.normal.y;
    eqn[2] = p.normal.z;
    eqn[3] = -p.normal.x * p.a.x + p.normal.y * p.a.y + p.normal.z * p.a.z;
    
    eqn
}

fn main(){
    let a = Point3D{x: 0.3,y: 7.8,z: 5.6};
    let b = Point3D{x: 3.4,y: 4.1,z: 9.7};
    let v: Vec3D = construct_vec(a,b);
    println!("{:?}",v);
}
