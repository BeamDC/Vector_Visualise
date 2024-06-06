mod math;

use std::fmt;
use math::*;
use egui::{ComboBox, DragValue};

#[derive(PartialEq)]
enum Types {
    Point,
    Vector,
    Plane,
}

impl fmt::Display for Types {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Types::Point => write!(f, "Point"),
            Types::Vector => write!(f, "Vector"),
            Types::Plane => write!(f, "Plane"),
        }
    }
}

struct MainWindow {
    add_type: Types,
    standard_point: Point3D,
    standard_vector: Vec3D,
    standard_plane: Plane3D,
    points: Vec<Point3D>,
    vectors: Vec<Vec3D>,
    planes: Vec<Plane3D>,
}

impl Default for MainWindow {
    fn default() -> Self {
        Self {
            add_type: Types::Point,
            standard_point: Point3D { ..Default::default() },
            standard_vector: Vec3D { ..Default::default() },
            standard_plane: Plane3D { ..Default::default() },
            points: Vec::new(),
            vectors: Vec::new(),
            planes: Vec::new(),
        }
    }
}

impl eframe::App for MainWindow {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                //dropdown menu for types
                ui.label("Add New Item: ");
                ComboBox::from_label("")
                    .selected_text(format!("{}", self.add_type))
                    .show_ui(ui, |ui| {
                        ui.style_mut().wrap = Some(false);
                        ui.set_min_width(45.0);
                        ui.selectable_value(&mut self.add_type, Types::Point, Types::Point.to_string());
                        ui.selectable_value(&mut self.add_type, Types::Vector, Types::Vector.to_string());
                        ui.selectable_value(&mut self.add_type, Types::Plane, Types::Plane.to_string());
                    });
            });

            // inputs for each type
            match self.add_type {
                Types::Point => ui.horizontal(|ui| {
                    ui.label("X: ");
                    ui.add(DragValue::new(&mut self.standard_point.x).speed(0.5));
                    ui.label("Y: ");
                    ui.add(DragValue::new(&mut self.standard_point.y).speed(0.5));
                    ui.label("Z: ");
                    ui.add(DragValue::new(&mut self.standard_point.z).speed(0.5));
                }),
                Types::Vector => ui.horizontal(|ui| {
                    ui.label("X: ");
                    ui.add(DragValue::new(&mut self.standard_vector.x).speed(0.5));
                    ui.label("Y: ");
                    ui.add(DragValue::new(&mut self.standard_vector.y).speed(0.5));
                    ui.label("Z: ");
                    ui.add(DragValue::new(&mut self.standard_vector.z).speed(0.5));
                }),
                Types::Plane => ui.vertical(|ui| {
                    ui.horizontal(|ui|{
                        ui.label("X1: ");
                        ui.add(DragValue::new(&mut self.standard_plane.a.x).speed(0.5));
                        ui.label("Y1: ");
                        ui.add(DragValue::new(&mut self.standard_plane.a.y).speed(0.5));
                        ui.label("Z1: ");
                        ui.add(DragValue::new(&mut self.standard_plane.a.z).speed(0.5));
                    });
                    ui.horizontal(|ui|{
                        ui.label("X2: ");
                        ui.add(DragValue::new(&mut self.standard_plane.b.x).speed(0.5));
                        ui.label("Y2: ");
                        ui.add(DragValue::new(&mut self.standard_plane.b.y).speed(0.5));
                        ui.label("Z2: ");
                        ui.add(DragValue::new(&mut self.standard_plane.b.z).speed(0.5));
                    });
                    ui.horizontal(|ui|{
                        ui.label("X3: ");
                        ui.add(DragValue::new(&mut self.standard_plane.c.x).speed(0.5));
                        ui.label("Y3: ");
                        ui.add(DragValue::new(&mut self.standard_plane.c.y).speed(0.5));
                        ui.label("Z3: ");
                        ui.add(DragValue::new(&mut self.standard_plane.c.z).speed(0.5));
                    });
                }),
            };

            //button to construct the type
            if ui.button("CONSTRUCT").clicked(){
                match self.add_type {
                    Types::Point => self.points.push(self.standard_point),
                    Types::Vector => self.vectors.push(self.standard_vector),
                    Types::Plane => self.planes.push(self.standard_plane),
                }
                println!("Points: {:#?}",self.points);
                println!("Vectors: {:#?}",self.vectors);
                println!("Planes: {:#?}",self.planes);
            }
        });
    }
}


fn main() -> Result<(), eframe::Error> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([640.0, 480.0]),
        ..Default::default()
    };
    eframe::run_native("Vector Visualiser", options,
                       Box::new(|cc| {
                           Box::<MainWindow>::default()
                       }),
    )
}
