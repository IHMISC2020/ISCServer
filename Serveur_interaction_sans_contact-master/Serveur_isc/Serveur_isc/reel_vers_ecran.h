#pragma once

// ReelVersEcran
#include "vecteur3.h"

#include "plan.h"
#include "axes.h"

class ReelVersEcran {
private:
    struct DataCalibrageStruct { Vecteur3<double> p1, p2; std::vector<Vecteur3<double>> tete; } mDataCalibrage;
    Axes* mAxes;
    Plan* mPlan;
    struct Ecran { double h, l; } mEcran;
public:
    ReelVersEcran();
    virtual ~ReelVersEcran() {
        delete mAxes;
        delete mPlan;
    }

    std::pair<double, double> positionDoigtEcran(const Vecteur3<double>& positionDoigtReel);

};