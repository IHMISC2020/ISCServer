#pragma once

#include <iostream>
#include <string>

class Point3D {
private:
	double mX, mY, mZ;
public:
	Point3D(double x, double y, double z);
	Point3D();
	virtual ~Point3D() {}

	virtual operator std::string() const;

	double getX() const;
	double getY() const;
	double getZ() const;
	void setX(double x);
	void setY(double y);
	void setZ(double z);
};

extern std::ostream& operator << (std::ostream& os, const Point3D& point);
