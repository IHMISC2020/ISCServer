#pragma once

// lib c++ perso
#include "CommandeHelp.h"
#include "CommandeQuitter.h"
#include "CommandeRequeteServerMotive.h"
#include "CommandAddDataCalibrage.h"
#include "CommandeInfoDoigt.h"
#include "CommandeCSV.h"
#include "ServerTCP.h"

#include <vector>

class ManagerCommandes {
private:
	ServerTCP& m_serveur;
	CommandesServeurLst* m_commandes;
public:


	std::vector<std::string> split(const std::string& chaine) const;

	ManagerCommandes(ServerTCP& serveur);
	virtual ~ManagerCommandes();

	int resoud(const std::string& message);
};

