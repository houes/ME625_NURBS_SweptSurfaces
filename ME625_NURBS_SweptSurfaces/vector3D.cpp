#include "vector3D.h"

vector3D vector3D::crossp(const vector3D &v) const
{
	return vector3D(	y*v.z - z*v.y,
						z*v.x - x*v.z,
						x*v.y - y*v.x	);
}