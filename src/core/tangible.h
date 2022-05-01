#ifndef TANGIBLE_H
#define TANGIBLE_H

#include "v3d.h"
#include <cmath>


class Tangible {
	private:
		bool fixed_in_place = false;
		v3d position, velocity;
		double mass;
	public:
		Tangible();
		Tangible(const v3d& position, double mass) : position(position), mass(mass) {}
		Tangible(const v3d& position, double mass, const v3d& velocity) : position(position), velocity(velocity), mass(mass) {}

		virtual v3d get_electric_field(const v3d&);
		virtual v3d get_magnetic_field(const v3d&);
		v3d get_position() { return position; }

		virtual ~Tangible();

};

#endif
