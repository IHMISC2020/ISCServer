#pragma once

#include <iostream>
#include <string>
#include "Point3D.h"

class Vecteur3D
{
private:
	double mX, mY, mZ;

public:
	Vecteur3D();
	Vecteur3D(double x, double y, double z);
	Vecteur3D(const Point3D& p1, const Point3D& p2);
	virtual ~Vecteur3D() {}

	// operateur
	operator std::string() const;
	Vecteur3D operator / (double valeur) const;

	// getter
	double getX() const { return mX; }
	double getY() const { return mY; }
	double getZ() const { return mZ; }
	// setter
	void setX(double x) { mX = x; }
	void setY(double y) { mY = y; }
	void setZ(double z) { mZ = z; }

	// calculs static
	static double norme(const Vecteur3D& vecteur);
	static Vecteur3D vectoriel(const Vecteur3D& v1, const Vecteur3D& v2);
	static Vecteur3D unitaire(const Vecteur3D& vecteur);
	static Vecteur3D division(const Vecteur3D& vecteur, double valeur);
	static Vecteur3D addition(const Vecteur3D& vecteur1, const Vecteur3D& vecteur2);
};

extern std::ostream& operator << (std::ostream& os, const Vecteur3D& vecteur);