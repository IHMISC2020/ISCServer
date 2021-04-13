#include "CommandeQuitter.h"

CommandeQuitter::CommandeQuitter(CommandesServeurLst* next, ServerTCP& serveur)
	: CommandesServeurLst(next), m_serveur(serveur) {}

/*virtual*/CommandeQuitter::~CommandeQuitter() {}

int CommandeQuitter::resoud_expert(const std::string& commande, const std::vector<std::string>& args)
{
	if (commande == "quitter" || commande == "q") {
		std::cout << "quitter" << std::endl;
		m_serveur.envoi_message("au revoir");

		m_serveur.set_run(false);

		return 0;
	}

	return -1;
}
