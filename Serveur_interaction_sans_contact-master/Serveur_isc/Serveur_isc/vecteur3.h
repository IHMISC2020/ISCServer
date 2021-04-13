#pragma once

#include <cmath>
#include <iostream>
#include <string>

template <class T>
class Vecteur3 {
private:
    T mX, mY, mZ;

public:
    Vecteur3<T>() : mX(T()), mY(T()), mZ(T()) {}
    Vecteur3<T>(const T& x, const T& y, const T& z) : mX(x), mY(y), mZ(z) {}
    Vecteur3<T>(const Vecteur3<T>& p1, const Vecteur3<T>& p2)
        : mX(p2.getX() - p1.getX())
        , mY(p2.getY() - p1.getY())
        , mZ(p2.getZ() - p1.getZ()) {}
    virtual ~Vecteur3<T>() {}

    // operateur
    operator std::string() const {
        std::string sX = std::to_string(getX()),
            sY = std::to_string(getY()),
            sZ = std::to_string(getZ());

        return "Vecteur3 (" + sX + "," + sY + "," + sZ + ")";
    }
    Vecteur3<T> operator / (double valeur) const {
        return Vecteur3<T>::division(*this, valeur);
    }
    Vecteur3<T> operator + (const Vecteur3<T>& o) const {
        return Vecteur3<T>::addition(*this, o);
    }

    // getter
    const T& getX() const { return mX; }
    const T& getY() const { return mY; }
    const T& getZ() const { return mZ; }
    double getNorme() const { return Vecteur3<T>::norme(*this); }
    // setter
    void setX(const T& x) { mX = x; }
    void setY(const T& y) { mY = y; }
    void setZ(const T& z) { mZ = z; }

    // calculs static
    static double norme(const Vecteur3<T>& vecteur) {
        T x = vecteur.getX(), y = vecteur.getY(), z = vecteur.getZ();
        return std::sqrt(x * x + y * y + z * z);
    }
    static Vecteur3<T> vectoriel(const Vecteur3<T>& v1, const Vecteur3<T>& v2) {
        T x1 = v1.getX(), y1 = v1.getY(), z1 = v1.getZ();
        T x2 = v2.getX(), y2 = v2.getY(), z2 = v2.getZ();

        double xv = y1 * z2 - z1 * y2;
        double yv = z1 * x2 - x1 * z2;
        double zv = x1 * y2 - y1 * x2;

        return Vecteur3<T>(xv, yv, zv);
    }
    static Vecteur3<T> unitaire(const Vecteur3<T>& vecteur) {
        double norme = Vecteur3<T>::norme(vecteur);
        if (norme != 0.0) return vecteur / norme;
        else return vecteur;
    }
    static Vecteur3<T> division(const Vecteur3<T>& vecteur, double valeur) {
        return Vecteur3<T>(vecteur.getX() / valeur, vecteur.getY() / valeur, vecteur.getZ() / valeur);
    }
    static Vecteur3<T> addition(const Vecteur3<T>& vecteur1, const Vecteur3<T>& vecteur2) {
        T	x = vecteur1.getX() + vecteur2.getX(),
            y = vecteur1.getY() + vecteur2.getY(),
            z = vecteur1.getZ() + vecteur2.getZ();
        return Vecteur3<T>(x, y, z);
    }
};

template<class T>
extern std::ostream& operator << (std::ostream& os, const Vecteur3<T>& vecteur) {
    return os << (std::string)vecteur;
}