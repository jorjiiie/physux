// particle.cpp

#include "particle.h"
// void Particle::get_
Particle::Particle(double charge, double mass, double radius) {
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
}
void Particle::log_data(std::ofstream& stream) {

	std::cerr << "hi\n";
}
void Particle::log_dbg() {
	std::cerr << "INFOS: ";
	physics->log_info();
}

void Particle::set_position(const v3d& pos) {
	physics->set_position(pos);
}
