#include "CommandAddDataCalibrage.h"

#include "DataCalibrageHandler.h"
#include "Server_motiv.h"

CommandAddDataCalibrage::CommandAddDataCalibrage(CommandesServeurLst* next, ServerTCP& serveur)
	: CommandesServeurLst(next), m_serveur(serveur) {}
/*virtual*/CommandAddDataCalibrage::~CommandAddDataCalibrage() {}

/*virtual*/int CommandAddDataCalibrage::resoud_expert(const std::string& commande, const std::vector<std::string>& args) {
	if (commande == "addDataCalibrage" || commande == "a") {
		Server_motiv& motiv(Server_motiv::getInstance());
		bool find(false);

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
				// on sauvegarde les donnees
				DataCalibrageHandler::getInstance().addData(DataCalibrage(
					mains[0],
					lunettes[0],
					lunettes[1],
					lunettes[2]
				));

				// m_serveur.envoi_message("data ajoutee");
			} else {
				std::cerr << "nbpt mains : " << mains.size() << std::endl;
				std::cerr << "nbpt lunettes : " << lunettes.size() << std::endl;
			}
		}

		return 0;
	}
	return -1;
	
}
