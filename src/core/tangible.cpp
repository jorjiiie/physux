//tangible.cpp

#include "tangible.h"

Tangible::Tangible(const Tangible& other) {
	pos = other.pos;
	velocity = other.velocity;

	mass = other.mass;
	charge = other.charge;

	fixed_in_place = other.fixed_in_place;
}

v3d Tangible::get_electric_field(const Tangible& other) {
	// kq/r^2
	// std::cerr << other.pos << " " << pos << "\n";
	v3d d = other.pos - pos;
	double r_squared = d.dot(d);
	r_squared = std::max(r_squared, Global::EPSILON);

	// std::cerr << r_squared << " " << d << " " << charge << "\n";
	d.normalize();
	return d * (Global::CONSTANT_ELECTRIC * charge * 1.0 / r_squared);
}

void Tangible::make_static() {
	fixed_in_place = true;
}

void Tangible::apply_field(const v3d& field) {
	v3d force = field*charge;


	force_tick += force;

	velocity += (force * (Global::TIME_STEP / mass));
}

void Tangible::apply_magnetic(const v3d& field) {
	// f = qv x b;
	v3d force = (velocity.cross(field)) * charge * Global::CONSTANT_MAGNETIC * 2;

	force_tick += force;

	velocity += (force * Global::TIME_STEP);
}

void Tangible::tick() {

	if (!fixed_in_place)
		pos += (velocity * Global::TIME_STEP);

	//reset so each tick it will accumulate
}
void Tangible::reset_force() {
	force_tick = v3d(0,0,0);
}

void Tangible::set_position(const v3d& position) {
	pos = position;
}
void Tangible::set_velocity(const v3d& v) {
	velocity = v;
}

void Tangible::log_info() {
	std::cerr << pos << " " << velocity << " " << force_tick << "\n";
}