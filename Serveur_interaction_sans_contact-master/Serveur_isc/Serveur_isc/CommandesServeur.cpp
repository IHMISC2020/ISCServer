#include "CommandesServeur.h"

#pragma region CommandesServer

/*virtual*/CommandesServeur::~CommandesServeur() {}

#pragma endregion CommandesServeur

CommandesServeurLst::CommandesServeurLst(CommandesServeurLst* next) 
	: m_next(next) {}

/*virtual*/CommandesServeurLst::~CommandesServeurLst() {}

int CommandesServeurLst::resoud(const std::string& commande, const std::vector<std::string>& args) {
	int res = resoud_expert(commande, args);
	if (res != -1) return res;
	else {
		if (m_next != nullptr) {
			return m_next->resoud(commande, args);
		} else {
			return res; // -1
		}
	}
}

void CommandesServeurLst::delete_chaine(CommandesServeurLst*& lst) {
	if (lst != nullptr) {
		if (lst->m_next != nullptr) {
			CommandesServeurLst::delete_chaine(lst->m_next);
			delete lst; lst = nullptr;
		}
	}
}