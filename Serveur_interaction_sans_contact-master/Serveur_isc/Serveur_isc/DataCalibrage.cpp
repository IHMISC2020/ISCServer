#include "DataCalibrage.h"

DataCalibrage::DataCalibrage(const Vecteur3<double>& doigt, const Vecteur3<double>& cA, const Vecteur3<double>& cB, const Vecteur3<double>& cC)
	: mDoigt(doigt), mCapteurA(cA), mCapteurB(cB), mCapteurC(cC) {}
