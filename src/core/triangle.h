#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Triangle {
	struct Point {
		v3d vertex, rgb;
		Point(const v3d& p_vertex, const v3d& p_rgb) : vertex(p_vertex), rgb(p_rgb) {}
	};
	Point a,b,c;
	Triangle(const v3d& p_a, const v3d& p_b, const v3d& p_c, const v3d& p_rgb) : a(p_a,p_rgb), b(p_b,p_rgb), c(p_c,p_rgb) {}
	Triangle(const Point& p_a, const Point& p_b, const Point& p_c) : a(p_a), b(p_b), c(p_c) {}
};


#endif