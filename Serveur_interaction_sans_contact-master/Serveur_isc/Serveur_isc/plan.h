#pragma once

// c++
#include <vector>
// perso
#include "vecteur3.h"

/**
 * se construit a partir d'un vecteur directeur et
 * d'un point du plan
 */
class Plan {
private:
    double mA, mB, mC, mD;
public:
    Plan(const Vecteur3<double>& vecteurNormal, const Vecteur3<double>& pointPlan);
    virtual ~Plan() {}

    operator std::string() const;

    double getA() const { return mA; }
    double getB() const { return mB; }
    double getC() const { return mC; }
    double getD() const { return mD; }

    Vecteur3<double> projection(const Vecteur3<double>& point, const Vecteur3<double>& direction) const;
};

extern std::ostream& operator << (std::ostream& os, const Plan& plan);