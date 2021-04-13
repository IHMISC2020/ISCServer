#pragma once
#include <iostream>
#include <vector>

#include <NatNetTypes.h>
#include <NatNetCAPI.h>
#include <NatNetClient.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <conio.h>
#include "Constantes.h"
#include "vecteur3.h"


class Server_motiv {
	private :
		Server_motiv();
		static Server_motiv* instance;
		NatNetClient* g_pClient;
		std::vector< sNatNetDiscoveredServer > liste_server;
		sNatNetClientConnectParams parametre_connexion;
		char g_discoveredMulticastGroupAddr[kNatNetIpv4AddrStrLenMax] = NATNET_DEFAULT_MULTICAST_ADDRESS;
		static const ConnectionType kDefaultConnectionType = ConnectionType_Multicast;
		sServerDescription g_serverDescription;
		int g_analogSamplesPerMocapFrame;
		static void gestion_data(sFrameOfMocapData* data, void* pUserData);
		static void gestion_decouverte_server(const sNatNetDiscoveredServer* pDiscoveredServer, void* pUserContext);
		void recherche_server();
		void connexion_server();
	public:
		const static int NB_POINTS_MAINS = 2;
		const static int NB_POINTS_LUNETTE = 3;
		void run();
		bool requete;
		std::vector<Vecteur3<double>> Points_Lunettes;
		std::vector<Vecteur3<double>> Points_main;
		std::string reponse;
		static Server_motiv& getInstance();
		static void delete_instance();
		~Server_motiv();
};
