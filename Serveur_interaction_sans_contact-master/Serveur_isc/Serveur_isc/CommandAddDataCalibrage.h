#pragma once

#include "CommandesServeur.h"

#include "ServerTCP.h"

class CommandAddDataCalibrage : public CommandesServeurLst {
private:
	ServerTCP& m_serveur;
public:
	CommandAddDataCalibrage(CommandesServeurLst* next, ServerTCP& serveur);
	virtual ~CommandAddDataCalibrage();

	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args);
};


