#include "ManagerCommandes.h"

ManagerCommandes::ManagerCommandes(ServerTCP& serveur) : m_serveur(serveur) {
	// m_commandes = new CommandeHelp(nullptr, m_serveur);
	m_commandes = new CommandeQuitter(m_commandes, m_serveur);
	m_commandes = new CommandAddDataCalibrage(m_commandes, serveur);
	m_commandes = new CommandeInfoDoigt(m_commandes, serveur);
	m_commandes = new CommandeCSV(m_commandes, serveur);
}

std::vector<std::string> ManagerCommandes::split(const std::string& chaine) const {
	std::vector<std::string> res;
	std::string mot = "";
	for (int i = 0; i < chaine.length(); i++) {
		char c = chaine[i];

		if (c != ' ') {
			mot += c;
		}
		else {
			if (mot.length() > 0) {
				res.push_back(mot);
				mot = "";
			}
		}
	}

	if (mot.length() > 0) res.push_back(mot);

	return res;
}

/*virtual*/ManagerCommandes::~ManagerCommandes() {
	CommandesServeurLst::delete_chaine(m_commandes);
}

int ManagerCommandes::resoud(const std::string& message) {
	// liste de vide pour le moment en ce qui concerne les arguments
	// TODO split la chaine message afin de determiner la commande et les args

	std::vector<std::string> lst = split(message);

	std::vector<std::string> args;

	for (int i = 1; i < lst.size(); i++) args.push_back(lst[i]);

	return m_commandes->resoud(lst[0], args);
}