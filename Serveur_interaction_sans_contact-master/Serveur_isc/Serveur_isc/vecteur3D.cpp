#include "vecteur3D.h"

Vecteur3D::Vecteur3D() : mX(0.0), mY(0.0), mZ(0.0) {}
Vecteur3D::Vecteur3D(double x, double y, double z)
	: mX(x), mY(y), mZ(z) {}
Vecteur3D::Vecteur3D(const Point3D& p1, const Point3D& p2) 
	: mX(p2.getX() - p1.getX())
	, mY(p2.getY() - p1.getY())
	, mZ(p2.getZ() - p1.getZ()) {}

// operateur
Vecteur3D::operator std::string() const {
	std::string sX = std::to_string(getX()),
				sY = std::to_string(getY()),
				sZ = std::to_string(getZ());

	return "Vecteur3D (" + sX + "," + sY + "," + sZ + ")";
}
Vecteur3D Vecteur3D::operator / (double valeur) const {
	return Vecteur3D(getX() / valeur, getY() / valeur, getZ() / valeur);
}

// calculs static
/*static*/double Vecteur3D::norme(const Vecteur3D& vecteur) {
	double x = vecteur.getX(), y = vecteur.getY(), z = vecteur.getZ();
	return std::sqrt(x * x + y * y + z * z);
}
/*static*/Vecteur3D Vecteur3D::vectoriel(const Vecteur3D& v1, const Vecteur3D& v2) {
	double x1 = v1.getX(), y1 = v1.getY(), z1 = v1.getZ();
	double x2 = v2.getX(), y2 = v2.getY(), z2 = v2.getZ();

	double xv = y1 * z2 - z1 * y2;
	double yv = z1 * x2 - x1 * z2;
	double zv = x1 * y2 - y1 * x2;

	return Vecteur3D(xv, yv, zv);
}
/*static*/Vecteur3D Vecteur3D::unitaire(const Vecteur3D& vecteur) {
	return Vecteur3D::division(vecteur, Vecteur3D::norme(vecteur));
}
/*static*/Vecteur3D Vecteur3D::division(const Vecteur3D& vecteur, double valeur) {
	return Vecteur3D(vecteur.getX() / valeur, vecteur.getY() / valeur, vecteur.getZ() / valeur);
}
/*static*/Vecteur3D Vecteur3D::addition(const Vecteur3D& vecteur1, const Vecteur3D& vecteur2) {
	double	x = vecteur1.getX() + vecteur2.getX(),
			y = vecteur1.getY() + vecteur2.getY(),
			z = vecteur1.getZ() + vecteur2.getZ();
	return Vecteur3D(x, y, z);
}

extern std::ostream& operator << (std::ostream& os, const Vecteur3D& vecteur) {
	return os << (std::string) vecteur;
}
