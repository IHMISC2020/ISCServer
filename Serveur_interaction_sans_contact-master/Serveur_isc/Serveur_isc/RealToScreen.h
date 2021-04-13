#pragma once

#include <utility>

#include "vecteur3D.h"
#include "Point3D.h"

/**
 * cette class comporte toute les methodes permettant de passer de coordonnée 
 * de la salle vers l'application android
 */

/*
class RealToScreen {
private:
	// axes
	Vecteur3D mU, mV, mW; // axe U et V et W de l'ecran

	// plan application
	struct Plan { double a, b, c, d; } mPlan;
	struct Ecran { double h, l; } mEcran;

	Point3D mP1, mP2;
public:

	RealToScreen();
	virtual ~RealToScreen() {}
	
	std::pair<double, double> positionDoigtEcran(const Point3D& positionDoigtReel);

	// init
	void initAxes();
	void initPlan();
	void initEcran();
};

*/