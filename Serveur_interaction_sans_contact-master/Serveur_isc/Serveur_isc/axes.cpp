#include "axes.h"

Axes::Axes(const Vecteur3<double>& doigt, const std::vector<Vecteur3<double>>& tete) {
    //////////////////////////
    // CALCUL DU VECTEUR MV //
    //////////////////////////

    // on recupere les points des capteurs des lunettes
    const Vecteur3<double>& A = tete[0];
    const Vecteur3<double>& B = tete[1];
    const Vecteur3<double>& C = tete[2];
    // on cree 2 vecteurs
    Vecteur3<double> AB(A, B);
    Vecteur3<double> BC(B, C);
    // mV est le produit vectoriel de AB ^ BC
    Vecteur3<double> pdtVectorielV = Vecteur3<double>::vectoriel(AB, BC);
    // mV est le vecteur unitaire de ce produit vectoriel
    mV = Vecteur3<double>::unitaire(pdtVectorielV);

    //////////////////////////
    // CALCUL DU VECTEUR MW //
    //////////////////////////

    // on cree le vecteur CB
    Vecteur3<double> CB(C, B);
    // le vecteur W est la somme de AB et CB
    Vecteur3<double> wNonUnitaire = AB + CB;
    // on en deduit W etant le vecteur unitaire de ce dernier
    mW = Vecteur3<double>::unitaire(wNonUnitaire);

    //////////////////////////
    // CALCUL DU VECTEUR MU //
    //////////////////////////

    // le vecteur mU est tout simplement le produit vectoriel des v et w

    // remarque comme v et w sont unitaire et que l'angle sin(v, w) = 90 u est
    // bien unitaire
    mU = Vecteur3<double>::vectoriel(mV, mW);
    mU = Vecteur3<double>::unitaire(mU); // on le met unitaire
}