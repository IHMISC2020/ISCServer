#include "CommandeRequeteServerMotive.h"

#include "Server_motiv.h"


CommandeRequeteServerMotive::CommandeRequeteServerMotive(CommandesServeurLst* next, ServerTCP& serveur)
	: CommandesServeurLst(next), m_serveur(serveur) {}

/*virtual*/CommandeRequeteServerMotive::~CommandeRequeteServerMotive() {}

int CommandeRequeteServerMotive::resoud_expert(const std::string& commande, const std::vector<std::string>& args)
{
	if (commande == "motive" || commande == "m") {
		Server_motiv::getInstance().requete = true;
		//On attends que la requete soit traitée par le serveur motiv lancé dans un autre thread
		while (Server_motiv::getInstance().requete);
		m_serveur.envoi_message(Server_motiv::getInstance().reponse);
		//m_serveur.envoi_message("MAIN : " + (std::string) Server_motiv::getInstance().Points_Lunettes[0] + " " + (std::string) Server_motiv::getInstance().Points_Lunettes[1] + " " + (std::string) Server_motiv::getInstance().Points_Lunettes[2]);

		return 0;
	}

	return -1;
}