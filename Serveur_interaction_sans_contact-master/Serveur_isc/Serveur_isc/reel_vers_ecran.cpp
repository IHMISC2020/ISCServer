#include "reel_vers_ecran.h"

#include "DataCalibrageHandler.h"

ReelVersEcran::ReelVersEcran() {
    // on recupere le gestionnaire de calibrage
    DataCalibrageHandler& calibrageHandler(DataCalibrageHandler::getInstance());
    // on recupere les valeures de calibrage
    const std::vector<DataCalibrage>& pointsCalibrage(calibrageHandler.getDataCalibrage());

    // on recupere les capteurs de la tete
    std::vector<Vecteur3<double>> tete;
    tete.push_back(pointsCalibrage[0].getCapteurA());
    tete.push_back(pointsCalibrage[0].getCapteurB());
    tete.push_back(pointsCalibrage[0].getCapteurC());

    Vecteur3<double> p1 = pointsCalibrage[0].getDoigt();
    Vecteur3<double> p2 = pointsCalibrage[1].getDoigt();

    
    mAxes = new Axes(p1, tete);
    mPlan = new Plan(mAxes->getW(), p1);

    // init data calibrage
    mDataCalibrage.p1 = p1;
    mDataCalibrage.p2 = p2;
    mDataCalibrage.tete = tete;

    const Vecteur3<double>& u(mAxes->getU());
    const Vecteur3<double>& v(mAxes->getV());

    // todo remettre p2 dans le plan
    Vecteur3<double> newp2 = mPlan->projection(p2, mAxes->getW());

    // todo factoriser avec une methode prenant u/v en parametre
    mEcran.l = u.getX() * (newp2.getX() - p1.getX()) + u.getY() * (newp2.getY() - p1.getY()) + u.getZ() * (newp2.getZ() - p1.getZ());
    mEcran.h = v.getX() * (newp2.getX() - p1.getX()) + v.getY() * (newp2.getY() - p1.getY()) + v.getZ() * (newp2.getZ() - p1.getZ());
    //std::cout << "rts L : " << mEcran.l << std::endl;
    //std::cout << "rts H : " << mEcran.h << std::endl;

}

std::pair<double, double> ReelVersEcran::positionDoigtEcran(const Vecteur3<double>& positionDoigtReel) {
    // projettons le doigt dans le plan
    Vecteur3<double> H = mPlan->projection(positionDoigtReel, mAxes->getW());

    // calcul de uh et vh
    const Vecteur3<double>& u(mAxes->getU());
    const Vecteur3<double>& v(mAxes->getV());
    const Vecteur3<double>& p1(mDataCalibrage.p1);

    // todo factoriser le code
    double uh = u.getX() * (H.getX() - p1.getX()) + u.getY() * (H.getY() - p1.getY()) + u.getZ() * (H.getZ() - p1.getZ());
    double vh = v.getX() * (H.getX() - p1.getX()) + v.getY() * (H.getY() - p1.getY()) + v.getZ() * (H.getZ() - p1.getZ());

    return std::pair<double, double>(uh / mEcran.l, vh / mEcran.h);
}