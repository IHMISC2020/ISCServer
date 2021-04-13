#include <iostream>
#include <string>
#include "Server_motiv.h"

#include "ServerTCP.h"

#include "vecteur3D.h"

std::string saisie(const std::string& message) {
	std::string resultat;
	std::cout << message;
	std::cin >> resultat;
	std::cout << std::endl;

	return resultat;
}
std::string saisie_ip() {
	return saisie("saisir adresse ip du server : ");
}
std::string saisie_port() {
	return saisie("saisir port du serveur : ");
}

int main(int argc, char* argv[]) {

	Server_motiv::getInstance().run();

	// demande de saisie utilisateur
	std::string s_ip("0.0.0.0"), s_port(saisie_port());

	// creation et initialisation du server
	ServerTCP serveur(s_ip, s_port);
	
	// lancement du serveur
	try {
		serveur.run2();
	}
	catch (std::string msg) {
		std::cerr << msg << std::endl;
	}

	// TODO dddd
	// suppression des instances singletons

	
	
	// fermeture du programme
	return 0;

}