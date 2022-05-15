// 3d vector class w basic operations
// opengl takes 4d vectors but the w-comp is just assumped to be 1 after normalization/clipping
//
#ifndef V3D_H
#define V3D_H

#include <cmath>
#include <iostream>
struct v3d {
	float x,y,z;
	v3d() : x(0), y(0), z(0) {}
	v3d(float x, float y, float z) : x(x), y(y), z(z) {}
	v3d(const v3d& o) : x(o.x), y(o.y), z(o.z) {}
	v3d& operator=(const v3d& o) {
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
		return *this;
	}

	v3d operator-() const {
		return v3d(-x,-y,-z);
	}
	v3d operator+(const v3d& o) const {
		v3d tmp = *this;
		return tmp += o;
	}
	v3d& operator+=(const v3d& o) {
		this->x += o.x;
		this->y += o.y;
		this->z += o.z;
		return *this;
	}
	v3d operator-(const v3d& o) const {
		v3d tmp = *this;
		return tmp -= o;
	}
	v3d& operator-=(const v3d& o) {
		this->x -= o.x;
		this->y -= o.y;
		this->z -= o.z;
		return *this;
	}	

	v3d operator*(double x) const {
		v3d tmp = *this;
		return tmp *= x;
	}
	v3d& operator*=(double x) {
		this->x *= x;
		this->y *= x;
		this->z *= x;
		return *this;
	}

	double dot(const v3d& o) const {
		return o.x * this->x + o.y * this->y + o.z * this->z;
	}
	v3d cross(const v3d& o) const {
		//cross product
		v3d tmp;
		tmp.x = this->y * o.z - this->z * o.y;
		tmp.y = this->z * o.x - this->x * o.z;
		tmp.z = this->x * o.y - this->y * o.x;

		return tmp;
	}

	v3d& normalize() {
		double magnitude = std::sqrt(x*x + y*y + z*z);

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		return *this;
	}
	v3d project(const v3d& o) const {
		v3d tmp = o;
		return tmp*(this->dot(o)/(o.dot(o)));
	}
	bool operator==(const v3d& o) const {
		// should have an epsilon here instead but whatever lmao
		if (abs(x-o.x) > .0001) return false;
		if (abs(y-o.y) > .0001) return false;
		if (abs(z-o.z) > .0001) return false;
		return true;
	}
	double operator[](const int i) const {
		switch(i) {
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
		}
		return 0;
	}

};

std::ostream& operator<<(std::ostream&, const v3d&);


#endif
