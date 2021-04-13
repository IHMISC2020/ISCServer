#pragma once

#include "CommandesServeur.h"

#include "ServerTCP.h"

class CommandeHelp : public CommandesServeurLst {
private:
	ServerTCP& m_serveur;
public:
	CommandeHelp(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandeHelp();

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};

