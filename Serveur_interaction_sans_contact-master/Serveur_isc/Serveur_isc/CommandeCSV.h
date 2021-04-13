#pragma once

#include "CommandesServeur.h"
#include "ServerTCP.h"


class CommandeCSV : public CommandesServeurLst {
private:
	ServerTCP& m_serveur;
public:
	CommandeCSV(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandeCSV() {}

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};

