#include "CommandeCSV.h"

#include <fstream>

CommandeCSV::CommandeCSV(CommandesServeurLst* next, ServerTCP& serveur)
	: CommandesServeurLst(next), m_serveur(serveur) {}

/*virtual*/int CommandeCSV::resoud_expert(const std::string& commande, const std::vector<std::string>& args) {

	if (commande == "csv" || commande == "c") {

		const std::string nom_fichier("out/export.csv");
		std::ofstream of(nom_fichier.c_str());
		if (of) {
			std::cout << "============================================================================= ecriture ok" << std::endl;

			for (const std::string& s : args) {
				of << s << std::endl;
			}
		}
		else {
			std::cerr << "erreur d'ecriture du fichier" << std::endl;
		}

		return 0;
	}
	return -1;

}
