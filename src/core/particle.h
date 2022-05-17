#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "renderable.h"
#include "tangible.h"
#include "ShapeFactory.h"
#include "loggable.h"

class Particle : public Loggable {
	private:
		double particle_time = 0;
	public:
		// might be able to slightly improve performance by changing to pointers but irrelevant
		// i should use inheritence or something but whatever
		std::shared_ptr<Renderable> mesh;
		std::shared_ptr<Tangible> physics;
		static constexpr int SLICES = 63;
		// charge, mass, radius
		Particle(double, double, double);
		
		void log_data(std::ofstream&);
		void log_init(std::ofstream&);
		void tick();
		void set_position(const v3d&);
		void log_dbg();
		
		~Particle();
};


#endif