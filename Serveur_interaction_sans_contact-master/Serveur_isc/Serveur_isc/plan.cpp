#include "plan.h"

Plan::Plan(const Vecteur3<double>& vecteurNormal, const Vecteur3<double>& pointPlan) {

    // l'equation du plan etant ax + by + cy + d = 0 on peux choisir a b c les composantes
    // d'un vecteur normal au plan

    // dans notre cas vectorNormal est normal au plan
    mA = vecteurNormal.getX();
    mB = vecteurNormal.getY();
    mC = vecteurNormal.getZ();

    // definissons d
    mD = -(vecteurNormal.getX() * pointPlan.getX() + vecteurNormal.getY() * pointPlan.getY() + vecteurNormal.getZ() * pointPlan.getZ());
}

Plan::operator std::string() const {
    std::string s_a(std::to_string(mA));
    std::string s_b(std::to_string(mB));
    std::string s_c(std::to_string(mC));
    std::string s_d(std::to_string(mD));
    return "Plan [ equation : " + s_a + "x + " + s_b + "y + " + s_c + "z + " + s_d + " ]";
}

Vecteur3<double> Plan::projection(const Vecteur3<double>& point, const Vecteur3<double>& direction) const {
    double numerateur = point.getX() * mA + point.getY() * mB + point.getZ() * mC + mD;
    double denominateur = direction.getX() * mA + direction.getY() * mB + direction.getZ() * mC;
    double t = (numerateur / denominateur);

    double Hx = point.getX() - direction.getX() * t;
    double Hy = point.getY() - direction.getY() * t;
    double Hz = point.getZ() - direction.getZ() * t;

    return Vecteur3<double>(Hx, Hy, Hz);
}

extern std::ostream& operator << (std::ostream& os, const Plan& plan) {
    return os << (std::string)plan;
}