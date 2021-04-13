#include "CommandeHelp.h"

#include <sstream>

CommandeHelp::CommandeHelp(CommandesServeurLst* next, ServerTCP& serveur)
	: CommandesServeurLst(next), m_serveur(serveur) {}

CommandeHelp::~CommandeHelp() {}

int CommandeHelp::resoud_expert(const std::string& commande, const std::vector<std::string>& args) {
	if (commande == "help" || commande == "h" || commande == "aide") {
		std::ostringstream oss;
		oss << "voici la liste des commandes disponibles : " << std::endl;
		oss << "commande -- explication" << std::endl;
		oss << "<help> ou <h> -- liste des commandes disponibles" << std::endl;
		oss << "<quit> ou <q> -- etein le serveur et vous deconnecte" << std::endl;
		oss << "<motive> ou <m> -- envoi la liste des points capter par motive" << std::endl;
		m_serveur.envoi_message(oss.str());

		return 0;
	}

	return -1;
}
