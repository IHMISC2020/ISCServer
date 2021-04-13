#include "ServerTCP.h"

// lib c++ perso
#include "ManagerCommandes.h"
#include "Server_motiv.h"

ServerTCP::ServerTCP(const std::string& s_ip, const std::string& s_port)
	: m_ip(s_ip)
	, m_port(s_port)
	, m_taille_buffer(2048)
	, m_buffer(nullptr)
	, m_result(nullptr)
	, m_socket_ecoute(INVALID_SOCKET)
	, m_socket_client(INVALID_SOCKET) 
	, m_run(true) {
	load_server();
}

/*virtual*/ServerTCP::~ServerTCP() {
	delete[] m_buffer; // suppression du beffer
	// free(m_result); ne marche pas lol
	// on supprime le result
	freeaddrinfo(m_result);
}

void ServerTCP::set_run(bool value) {
	m_run = value;
}

void ServerTCP::load_server() {
	// creation du buffer
	m_buffer = new char[m_taille_buffer];
	// on test si on a bien réussie à démarrer la version 2 de winsock api 
	if (WSAStartup(MAKEWORD(2, 2), &m_wsdata) != 0) {
		//si on a pas réussie à démarrer winsock
		throw std::string("Erreur lors du chargement de winsock");
	}
	//on test si on a bien chargé la version 2 de winsock
	if (LOBYTE(m_wsdata.wVersion) != 2 || HIBYTE(m_wsdata.wVersion) != 2) {
		throw std::string("Mauvaise version de l'api");
	}

	int iResult;
	ZeroMemory(&m_hints, sizeof(m_hints));
	m_hints.ai_family = AF_INET;
	m_hints.ai_socktype = SOCK_STREAM;
	m_hints.ai_protocol = IPPROTO_TCP;


	iResult = getaddrinfo(m_ip.c_str(), m_port.c_str(), &m_hints, &m_result);

	if (iResult != 0) {
		throw std::string("On a pas réussie a trouver l'adresse");
	}


	std::cout << "en attente du client" << std::endl;

	load_client();

	std::cout << "client trouvé" << std::endl;

}

void ServerTCP::load_client() {
	int iResult;
	m_socket_ecoute = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
	if (m_socket_ecoute == INVALID_SOCKET) {
		throw std::string("echec de la création de la socket");
	}

	//mise en place de l'écoute
	iResult = bind(m_socket_ecoute, m_result->ai_addr, (int)m_result->ai_addrlen);
	if (iResult != 0) {
		throw std::string("Erreur lors de l'ecoute de la socket");
	}

	//listen
	iResult = listen(m_socket_ecoute, SOMAXCONN); // SOMAXCONN nombre de connexion simultané autorisés (c'est un standard)
	if (iResult != 0) {
		throw std::string("Erreur de listen");
	}

	//création de la socket client 
	m_socket_client = accept(m_socket_ecoute, NULL, NULL);
	if (m_socket_client == INVALID_SOCKET) {
		throw std::string("Erreur Socket");
	}

	//on ferme la socket d'écoute car on a recu un client (si on veut un client)
	closesocket(m_socket_ecoute);
}

void ServerTCP::run2() {
	//ce que l'on fait tant que le client n'a pas fermé la connection
		ManagerCommandes manager(*this);
		std::string message_recu;
		int iResult(message_recu.length());
		do {
			message_recu = attend_message();
			iResult = (message_recu.length());
			if (iResult == 0) {
				// set_run(false);
				std::cout << "Fin de commnication";
			}
			else if (message_recu.length() > 0) {
				// envoi_message("message recu");
				manager.resoud(message_recu);
			}
			else {
				closesocket(m_socket_client);
				WSACleanup();
				throw std::string("Erreur lors de la réception d'un paquet");
			}

		} while (m_run);

		//Fermeture du reseau
		closesocket(m_socket_client);
		WSACleanup();
}

std::string ServerTCP::attend_message() {
	std::string message_recu;
	int taille_message_recu = recv(m_socket_client, m_buffer, m_taille_buffer, 0);

	if (taille_message_recu > 0) {
		// on a bien recu le message
		//on renvoie a l'envoyeur ce que l'on a recu
		//dans ce cas la iResult correspond a la taille du message que l'on a recu
		//on affiche le message recu
		char* msg = new char[taille_message_recu + (int)1]; //////////////////////////////////////////////////////////////// ajouter '/0'
		for (int i = 0; i < taille_message_recu; i++) {
			msg[i] = m_buffer[i];
		}
		msg[taille_message_recu] = '\0';

		std::cout << "nb de Bytes recu : " << taille_message_recu << std::endl;
		std::cout << "message recu : " << msg << std::endl;

		message_recu = msg;
		delete[] msg; // on supprime le message (on en a plus besoin)
	}

	return message_recu;
}

void ServerTCP::envoi_message(const std::string& message) {
	if (send(m_socket_client, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
		closesocket(m_socket_client);
		throw std::string("Erreur lors de l'envoie d'une réponse");
	}
}
