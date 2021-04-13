#include "RealToScreen.h"
/*
#include "DataCalibrageHandler.h"

RealToScreen::RealToScreen() : mPlan({ 0.0, 0.0, 0.0, 0.0 }), mEcran({ 0.0, 0.0 }) {
	// on initialise les axes de l'ecran android
	initAxes();
	// on initialise le plan
	initPlan();

	// 
	initEcran();
}

//fonction qui retourne la position en x et en y du pointeur sur l'ecran android
std::pair<double, double> RealToScreen::positionDoigtEcran(const Point3D& positionDoigtReel) {
	std::pair<double, double> res(0.0, 0.0);

	// meme methode que pour la projection de p2
	// resolution du system a un inconnu t
	const Point3D& M = positionDoigtReel;

	// projeton M sur le plan

	double diviseur = M.getX() * mPlan.a + M.getY() * mPlan.b + M.getZ() * mPlan.c + mPlan.d;
	double dividande = mW.getX() * mPlan.a + mW.getY() * mPlan.b + mW.getZ() * mPlan.c;
	double t = (diviseur / dividande);

	double Hx = M.getX() - mW.getX() * t;
	double Hy = M.getY() - mW.getY() * t;
	double Hz = M.getZ() - mW.getZ() * t;

	Point3D H(Hx, Hy, Hz);

	double uh = mU. getX() * (Hx - mP1.getX()) + mU.getY() * (Hy - mP1.getY()) + mU.getZ() * (Hz - mP1.getZ());
	double vh = mV.getX() * (Hx - mP1.getX()) + mV.getY() * (Hy - mP1.getY()) + mV.getZ() * (Hz - mP1.getZ());


	// TODO diviser par la hauteur et largeur pour obtenir les bonnes proportions

	res.first = uh / mEcran.l;
	res.second = vh / mEcran.h;

	//On fait en sorte de ne pas pouvroi dépasser l'ecran
	if (res.first > 1) res.first = 1;
	if (res.first < 0) res.first = 0;
	if (res.second > 1) res.second = 1;
	if (res.second < 0) res.second = 0;

	std::cout << "uh : " << uh << std::endl;
	std::cout << "vh : " << vh << std::endl;

	//on retourne la position en X et en Y du pointeur sur l'ecran
	return res;
}

void RealToScreen::initAxes() {
	// on recupere le gestionnaire de calibrage
	DataCalibrageHandler& calibrageHandler(DataCalibrageHandler::getInstance());
	// on recupere les valeures de calibrage
	const std::vector<DataCalibrage>& pointsCalibrage(calibrageHandler.getDataCalibrage());
	// on verifi la taille du tableau de point
	unsigned int nbPoints(pointsCalibrage.size());
	if (nbPoints < 2) {
		throw std::string("Erreur de calibrage : nombre de points calibres : " + nbPoints);
	}
	
	//////////////////////////
	// CALCUL DU VECTEUR MV //
	//////////////////////////

	// on recupere le premier point de calibrage
	const DataCalibrage& premierCalibrage(pointsCalibrage[0]);
	// on recupere les points des capteurs des lunettes
	const Point3D& A = premierCalibrage.getCapteurA();
	const Point3D& B = premierCalibrage.getCapteurB();
	const Point3D& C = premierCalibrage.getCapteurC();
	// on cree 2 vecteurs
	Vecteur3D AB(A, B);
	Vecteur3D BC(B, C);
	// mV est le produit vectoriel de AB ^ BC
	Vecteur3D pdtVectorielV = Vecteur3D::vectoriel(AB, BC);
	// mV est le vecteur unitaire de ce produit vectoriel
	mV = Vecteur3D::unitaire(pdtVectorielV);

	//////////////////////////
	// CALCUL DU VECTEUR MW //
	//////////////////////////
	
	// on cree le vecteur CB
	Vecteur3D CB(C, B);
	// le vecteur W est la somme de AB et CB
	Vecteur3D wNonUnitaire = Vecteur3D::addition(AB, CB);
	// on en deduit W etant le vecteur unitaire de ce dernier
	mW = Vecteur3D::unitaire(wNonUnitaire);

	//////////////////////////
	// CALCUL DU VECTEUR MU //
	//////////////////////////
	
	// le vecteur mU est tout simplement le produit vectoriel des v et w

	// remarque comme v et w sont unitaire et que l'angle sin(v, w) = 90 u est
	// bien unitaire
	mU = Vecteur3D::vectoriel(mV, mW);
}

void RealToScreen::initPlan() {
	// les axes etant initialiser on va pourvoir definir le plan
	// l'equation du plan etant ax + by + cy + d = 0 on peux choisir a b c les composante
	// d'un vecteur normal au plan

	// dans notre cas w est normal au plan
	mPlan.a = mW.getX();
	mPlan.b = mW.getY();
	mPlan.c = mW.getZ();

	// il ne reste plus qu'a determiner d.
	// le point de calibrage 1 appartenant au plan, il doit satisfaire son equation
	// on recupere le gestionnaire de calibrage
	DataCalibrageHandler& calibrageHandler(DataCalibrageHandler::getInstance());
	// on recupere les valeures de calibrage
	const std::vector<DataCalibrage>& pointsCalibrage(calibrageHandler.getDataCalibrage());
	// on verifi la taille du tableau de point
	unsigned int nbPoints(pointsCalibrage.size());
	if (nbPoints < 2) {
		throw std::string("Erreur de calibrage : nombre de points calibres : " + nbPoints);
	}

	const Point3D& p1(pointsCalibrage[0].getDoigt());

	// definissons d
	mPlan.d = -(mW.getX() * p1.getX() + mW.getY() * p1.getY() + mW.getZ() * p1.getZ());

	// projetons p2 dans plan
	// on recupere p2
	Point3D p2(pointsCalibrage[1].getDoigt());

	// resolution du system a un inconnu t
	double diviseur  = p2.getX() * mPlan.a + p2.getY() * mPlan.b + p2.getZ() * mPlan.c + mPlan.d;
	double dividande = mW.getX() * mPlan.a + mW.getY() * mPlan.b + mW.getZ() * mPlan.c;
	double t = (diviseur / dividande); // -t

	Point3D newP2(p2.getX() - mW.getX() * t, p2.getY() - mW.getY() * t, p2.getZ() - mW.getZ() * t);
	// on init nos points
	mP1 = p1;
	mP2 = newP2;
}

void RealToScreen::initEcran() {
	// definissions la largeur et la hauteur de l'ecran
	mEcran.h = mV.getX() * (mP2.getX() - mP1.getX()) + mV.getY() * (mP2.getY() - mP1.getY()) + mV.getZ() * (mP2.getZ() - mP1.getZ());
	mEcran.l = mU.getX() * (mP2.getX() - mP1.getX()) + mU.getY() * (mP2.getY() - mP1.getY()) + mU.getZ() * (mP2.getZ() - mP1.getZ());
}
*/