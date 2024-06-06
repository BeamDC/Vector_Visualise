use std::default::Default;

#[derive(Debug, Clone, Copy)]
pub struct Point3D{
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

#[derive(Debug, Clone, Copy)]
pub struct Vec3D{
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

#[derive(Debug, Clone, Copy)]
pub struct Plane3D{
    pub a: Point3D,
    pub b: Point3D,
    pub c: Point3D,

    pub normal: Vec3D
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
pub fn magnitude(v: Vec3D) -> f64{
    (v.x * v.x + v.y * v.y + v.z * v.z).sqrt()
}

pub fn dot(v: Vec3D, w: Vec3D) -> f64{
    v.x * w.x + v.y * w.y + v.z * w.z
}

pub fn construct_vec(a: Point3D, b: Point3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = b.x - a.x;
    r.y = b.y - a.y;
    r.z = b.z - a.z;
    r
}

pub fn add(v: Vec3D, w: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = v.x + w.x;
    r.y = v.y + w.y;
    r.z = v.z + w.z;
    r
}

pub fn opposite(v: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = -v.x;
    r.y = -v.y;
    r.z = -v.z;
    r
}

pub fn normalize(v: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    let m:f64 = magnitude(v.clone());
    r.x = v.x / m;
    r.y = v.y / m;
    r.z = v.z / m;
    r
}

pub fn scale(v: Vec3D, scalar: f64) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = v.x * scalar;
    r.y = v.y * scalar;
    r.z = v.z * scalar;
    r
}

pub fn cross(v: Vec3D, w: Vec3D) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    r.x = (v.y * w.z) - (v.z * w.y);
    r.y = (v.z * w.x) - (v.x * w.z);
    r.z = (v.x * w.y) - (v.y * w.x);
    r
}

pub fn rotate(v: Vec3D, yaw: f64, pitch: f64, roll: f64) -> Vec3D{
    let mut r = Vec3D{..Default::default()};
    let yaw_cos: f64 = yaw.cos();
    let yaw_sin: f64 = yaw.sin();
    let pitch_cos: f64 = pitch.cos();
    let pitch_sin: f64 = pitch.sin();
    let roll_cos: f64 = roll.cos();
    let roll_sin: f64 = roll.sin();

    let xx = yaw_cos * pitch_cos;
    let xy = yaw_cos * pitch_sin * roll_sin - yaw_sin * roll_cos;
    let xz = yaw_cos * pitch_sin * roll_cos + yaw_sin * roll_sin;

    let yx = yaw_sin * pitch_cos;
    let yy = yaw_sin * pitch_sin * roll_sin + yaw_cos * roll_cos;
    let yz = yaw_sin * pitch_sin * roll_cos - yaw_cos * roll_sin;

    let zx = -pitch_sin;
    let zy = pitch_cos * roll_sin;
    let zz = pitch_cos * roll_cos;

    r.x = xx * v.x + xy * v.y + xz * v.z;
    r.y = yx * v.x + yy * v.y + yz * v.z;
    r.z = zx * v.x + zy * v.y + zz * v.z;

    r
}

/* Plane Functions */
pub fn construct_plane(a: Point3D, b: Point3D, c: Point3D) -> Plane3D{
    let mut r = Plane3D{..Default::default()};
    r.a = a.clone();
    r.b = b.clone();
    r.c = c.clone();
    let ab:Vec3D = construct_vec(a.clone(), b);
    let ac:Vec3D = construct_vec(a, c);
    r.normal = normalize(cross(ab, ac));
    r
}

pub fn get_equation(p: Plane3D) -> [f64; 4]{
    let mut eqn: [f64; 4] = [0.0; 4];

    eqn[0] = p.normal.x;
    eqn[1] = p.normal.y;
    eqn[2] = p.normal.z;
    eqn[3] = -p.normal.x * p.a.x + p.normal.y * p.a.y + p.normal.z * p.a.z;

    eqn
}

pub fn get_intercepts(p: Plane3D) -> [Point3D; 3]{
    let mut xyz_ints: [Point3D; 3] = [Point3D{..Default::default()}; 3];

    let e = get_equation(p);
    xyz_ints[0].x = -(e[3]/e[0]);
    xyz_ints[1].x = -(e[3]/e[1]);
    xyz_ints[2].x = -(e[3]/e[2]);

    xyz_ints
}
