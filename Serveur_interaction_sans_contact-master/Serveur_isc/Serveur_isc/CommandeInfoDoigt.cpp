#include "CommandeInfoDoigt.h"

#include "Server_motiv.h"
// #include "RealToScreen.h"
#include "reel_vers_ecran.h"

CommandeInfoDoigt::CommandeInfoDoigt(CommandesServeurLst* next, ServerTCP& serveur) 
	: CommandesServeurLst(next), m_serveur(serveur) {}

/*virtual*/int CommandeInfoDoigt::resoud_expert(const std::string& commande, const std::vector<std::string>& args) {
	if (commande == "infoDoigt" || commande == "i") {

		ReelVersEcran rts;
		Server_motiv& motiv(Server_motiv::getInstance());
		bool find(false) ;

		while (!find) {
			// requete motive
			motiv.requete = true;
			while (motiv.requete);
			// recup de la reponse
			std::vector<Vecteur3<double>> lunettes(motiv.Points_Lunettes);
			std::vector<Vecteur3<double>> mains(motiv.Points_main);

			// TODO remplacer 3 et 1 par des constantes
			if (lunettes.size() >= 3 && mains.size() >= 1) find = true;

			if (find) {
				// on recupere la position de la main
				Vecteur3<double> main(mains[0]);

				std::pair<double, double> position = rts.positionDoigtEcran(main);

				// TODO * 2 bizzar

				std::string aEnvoyer = "{\"X\":" + std::to_string(position.first) + ",\"Y\":" + std::to_string(position.second) + "}";
				//std::cout << aEnvoyer << std::endl;
				m_serveur.envoi_message(aEnvoyer);
			}
			else {
				std::cerr << "nbpt mains : " << mains.size() << std::endl;
				std::cerr << "nbpt lunettes : " << lunettes.size() << std::endl;
			}
		}



		return 0;
	}

	return -1;
}
