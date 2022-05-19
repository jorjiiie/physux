#ifndef TANGIBLE_H
#define TANGIBLE_H

#include "v3d.h"

// worst design choice ive ever made
#include "../gfx/Global.h"
#include <cmath>


class Tangible {
	protected:
		bool fixed_in_place = false;
		v3d pos, velocity;
		// force on this tick
		v3d force_tick;
		double mass, charge;
	public:
		Tangible();
		Tangible(double _mass, double _charge) : mass(_mass), charge(_charge) {}
		Tangible(const Tangible&);

		v3d get_electric_field(const Tangible&);
		// virtual v3d get_magnetic_field(const v3d&);
		v3d get_pos() { return pos; }
		v3d get_velocity() {return velocity;}
		v3d get_force() {return force_tick;}
		double get_mass() {return mass;}
		double get_charge() {return charge;}

		void apply_field(const v3d&);
		void apply_magnetic(const v3d&);

		void reset_force();
		void make_static();
		void tick();
		void set_position(const v3d&);
		void set_velocity(const v3d&);
		void log_info();
		// virtual void tick();

};

#endif
