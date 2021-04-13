#pragma once

#include "Point3D.h"
#include "vecteur3.h"

/**
 * structure de donnée staocker pour un point de calibration
 */
class DataCalibrage {
private:
	Vecteur3<double> mDoigt, mCapteurA, mCapteurB, mCapteurC;
public:
	DataCalibrage(const Vecteur3<double>& doigt, const Vecteur3<double>& cA, const Vecteur3<double>& cB, const Vecteur3<double>& cC);
	virtual ~DataCalibrage() {}

	// getter
	const Vecteur3<double>& getDoigt() const { return mDoigt; }
	const Vecteur3<double>& getCapteurA() const { return mCapteurA; }
	const Vecteur3<double>& getCapteurB() const { return mCapteurB; }
	const Vecteur3<double>& getCapteurC() const { return mCapteurC; }
};
