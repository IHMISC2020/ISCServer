#pragma once

#include "CommandesServeur.h"
#include "ServerTCP.h"


class CommandeInfoDoigt : public CommandesServeurLst {
private:
	ServerTCP& m_serveur ;
public:
	CommandeInfoDoigt(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandeInfoDoigt() {}

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};

