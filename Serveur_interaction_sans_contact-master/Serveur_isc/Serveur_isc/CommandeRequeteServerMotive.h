#pragma once
#include "CommandesServeur.h"

#include "ServerTCP.h"

class CommandeRequeteServerMotive : public CommandesServeurLst {
private:
	ServerTCP& m_serveur;
public:
	CommandeRequeteServerMotive(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandeRequeteServerMotive();

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};

