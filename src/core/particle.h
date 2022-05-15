#ifndef PARTICLE_H
#define PARTICLE_H


#include "renderable.h"
#include "tangible.h"
#include "ShapeFactory.h"

class Particle {
	public:
		// might be able to slightly improve performance by changing to pointers but irrelevant
		// i should use inheritence or something but whatever
		std::shared_ptr<Renderable> mesh;
		std::shared_ptr<Tangible> physics;
		static constexpr int SLICES = 63;
		// charge, mass, radius
		Particle(double, double, double);
		void log_data(std::ofstream&);
		void tick();
		void set_position(const v3d&);
		void log_dbg();

};


#endif