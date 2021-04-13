#pragma once
#include "CommandesServeur.h"

#include "ServerTCP.h"

class CommandeQuitter : public CommandesServeurLst {
private:
	ServerTCP& m_serveur;
public:
	CommandeQuitter(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandeQuitter();

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};

