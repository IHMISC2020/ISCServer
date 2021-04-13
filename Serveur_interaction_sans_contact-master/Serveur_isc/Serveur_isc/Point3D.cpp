#include "Point3D.h"

Point3D::Point3D() : mX(0), mY(0), mZ(0) {}
Point3D::Point3D(double x, double y, double z)
	: mX(x), mY(y), mZ(z) {}

/*virtual*/Point3D::operator std::string() const {
	return "Point : (" + std::to_string(getX()) + ", " + std::to_string(getY()) + ", " + std::to_string(getZ()) + ")";
}

double Point3D::getX() const { return mX; }
double Point3D::getY() const { return mY; }
double Point3D::getZ() const { return mZ; }
void Point3D::setX(double x) { mX = x; }
void Point3D::setY(double y) { mY = y; }
void Point3D::setZ(double z) { mZ = z; }

extern std::ostream& operator << (std::ostream& os, const Point3D& point) {
	return os << (std::string) point;
}
