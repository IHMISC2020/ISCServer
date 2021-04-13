#pragma once

#include <iostream>
#include <string>
#include <vector>

class CommandesServeur {
public:
	virtual ~CommandesServeur();

	virtual int resoud(const std::string& commande, const std::vector<std::string>& args) = 0;
};

class CommandesServeurLst : public CommandesServeur {
private:
	CommandesServeurLst* m_next;
public:
	CommandesServeurLst(CommandesServeurLst* next);
	virtual ~CommandesServeurLst();

	virtual int resoud(const std::string& commande, const std::vector<std::string>& args);
	virtual int resoud_expert(const std::string& commande, const std::vector<std::string>& args) = 0;

	static void delete_chaine(CommandesServeurLst*& lst);
};

