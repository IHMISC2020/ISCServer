#pragma once

#include <vector>
#include "vecteur3.h"

class Axes {
private:
    Vecteur3<double> mU, mV, mW;
public:
    Axes(const Vecteur3<double>& doigt, const std::vector<Vecteur3<double>>& tete);
    virtual ~Axes() {}

    const Vecteur3<double>& getU() const { return mU; }
    const Vecteur3<double>& getV() const { return mV; }
    const Vecteur3<double>& getW() const { return mW; }
};