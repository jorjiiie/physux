// particle.cpp

#include "particle.h"

Particle::Particle(double charge, double mass, double radius) : Loggable() {
	// radius = r
	//shader = default;
	v3d rgb;
	if (charge > 0) {
		// make it red
		rgb = v3d(1.0,.5, .5);
	} else {
		rgb = v3d(0.5, 0.5, 1.0);
	}
	std::vector<Triangle> sphere_mesh = ShapeFactory::generate_sphere(radius, v3d(0,0,0), Particle::SLICES, Particle::SLICES, rgb);
	mesh = std::make_shared<Renderable>(sphere_mesh, Shader::shaders[Shader::SHADER_DEFAULT]);


	// init the particle
	physics = std::make_shared<Tangible>(mass, charge);
}


void Particle::tick() {

	physics->tick();

	mesh->update_position(physics->get_pos());

	particle_time += Global::TIME_STEP;
}
void Particle::log_data(std::ofstream& stream) {
	// log out the data types
	v3d velocity = physics->get_velocity();
	v3d force = physics->get_force();
	v3d pos = physics->get_pos();
	stream << particle_time << ","
		   << pos.x << "," << pos.y << "," << pos.z << ","
		   << velocity.x << "," << velocity.y << "," << velocity.z << ","
		   << force.x << "," << force.y << "," << force.z << ","
		   << physics->get_charge() << "," << physics->get_mass() 
		   << std::endl;

	physics->reset_force();
}
void Particle::log_init(std::ofstream& stream) {
	std::vector<std::string> column_names = { 
												"time", 
												"x_coord", "y_coord", "z_coord", 
												"x_velocity", "y_velocity", "z_velocity",
												"x_force", "y_force", "z_force",
												"charge", "mass"
											 };


	int sz = column_names.size();
	for (int i=0; i<sz-1; i++) {
		stream << column_names[i] << ",";
	}
	stream << column_names[sz-1] << std::endl;

}
void Particle::log_dbg() {
	std::cerr << "INFOS: ";
	physics->log_info();
}

void Particle::set_position(const v3d& pos) {
	physics->set_position(pos);
}

Particle::~Particle() {
	std::cerr << "destroying particle\n";
}