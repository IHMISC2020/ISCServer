#include"Server_motiv.h"

#include <sstream>

Server_motiv* Server_motiv::instance = nullptr;

Server_motiv& Server_motiv::getInstance() {
	if (instance == nullptr) {
		instance = new Server_motiv();
	}
	return *instance;
}

Server_motiv::Server_motiv() {
	g_pClient = NULL;
	g_analogSamplesPerMocapFrame = 0;
	requete = false;
}

void Server_motiv::gestion_data(sFrameOfMocapData* data, void* pUserData) {

	if (Server_motiv::getInstance().requete) {
		NatNetClient* pClient = (NatNetClient*)pUserData;

		// timecode - for systems with an eSync and SMPTE timecode generator - decode to values
		int hour, minute, second, frame, subframe;
		NatNet_DecodeTimecode(data->Timecode, data->TimecodeSubframe, &hour, &minute, &second, &frame, &subframe);
		// decode to friendly string
		char szTimecode[128] = "";
		NatNet_TimecodeStringify(data->Timecode, data->TimecodeSubframe, szTimecode, 128);
		printf("Timecode : %s\n", szTimecode);


		// labeled markers - this includes all markers (Active, Passive, and 'unlabeled' (markers with no asset but a PointCloud ID)
		bool bOccluded;     // marker was not visible (occluded) in this frame
		bool bPCSolved;     // reported position provided by point cloud solve
		bool bModelSolved;  // reported position provided by model solve
		bool bHasModel;     // marker has an associated asset in the data stream
		bool bUnlabeled;    // marker is 'unlabeled', but has a point cloud ID that matches Motive PointCloud ID (In Motive 3D View)
		bool bActiveMarker; // marker is an actively labeled LED marker

		printf("Markers [Count=%d]\n", data->nLabeledMarkers);
		std::string res;
		std::vector<Vecteur3<double>> Lunettes;
		std::vector<Vecteur3<double>> Mains;
		for (int i = 0; i < data->nLabeledMarkers; i++)
		{
			bOccluded = ((data->LabeledMarkers[i].params & 0x01) != 0);
			bPCSolved = ((data->LabeledMarkers[i].params & 0x02) != 0);
			bModelSolved = ((data->LabeledMarkers[i].params & 0x04) != 0);
			bHasModel = ((data->LabeledMarkers[i].params & 0x08) != 0);
			bUnlabeled = ((data->LabeledMarkers[i].params & 0x10) != 0);
			bActiveMarker = ((data->LabeledMarkers[i].params & 0x20) != 0);

			sMarker marker = data->LabeledMarkers[i];

			// Marker ID Scheme:
			// Active Markers:
			//   ID = ActiveID, correlates to RB ActiveLabels list
			// Passive Markers: 
			//   If Asset with Legacy Labels
			//      AssetID 	(Hi Word)
			//      MemberID	(Lo Word)
			//   Else
			//      PointCloud ID
			int modelID, markerID;
			NatNet_DecodeID(marker.ID, &modelID, &markerID);
			
			//on a les 3 points des lunettes
			if (modelID == Contantes::ID_LUNETTES) {
				Lunettes.push_back(Vecteur3<double>(marker.x,marker.y,marker.z));
			}

			if (modelID == Contantes::ID_STYLO) {
				Mains.push_back(Vecteur3<double>(marker.x, marker.y, marker.z));
			}

			char szMarkerType[512];
			if (bActiveMarker)
				strcpy_s(szMarkerType, "Active");
			else if (bUnlabeled)
				strcpy_s(szMarkerType, "Unlabeled");
			else
				strcpy_s(szMarkerType, "Labeled");

			std::string temp;
			std::ostringstream oss;
			if (szMarkerType != "Unlabeled") {
				oss.precision(3);
				oss << szMarkerType << " Marker [ModelID=" << modelID << ",MarkerID=" << markerID << ", Occluded=" << bOccluded << ", PCSolved=" << bPCSolved
					<< ", ModelSolved=" << bModelSolved << "[size= " << marker.size << "]" << "[pos=" << marker.x << ", " << marker.y << ", " << marker.z << "]" << std::endl;

				/*sprintf_s(temp, "%s Marker [ModelID=%d, MarkerID=%d, Occluded=%d, PCSolved=%d, ModelSolved=%d] [size=%3.2f] [pos=%3.2f,%3.2f,%3.2f]\n",
					szMarkerType, modelID, markerID, bOccluded, bPCSolved, bModelSolved, marker.size, marker.x, marker.y, marker.z);*/
				res += oss.str();
				res += "\n";
			}
		}
		Server_motiv::getInstance().reponse = res;
		Server_motiv::getInstance().Points_Lunettes = Lunettes;
		Server_motiv::getInstance().Points_main = Mains;
		Server_motiv::getInstance().requete = false;
	}
}

void Server_motiv::gestion_decouverte_server(const sNatNetDiscoveredServer* pDiscoveredServer, void* pUserContext)
{
	char serverHotkey = '.';
	if (Server_motiv::getInstance().liste_server.size() < 9)
	{
		serverHotkey = static_cast<char>('1' + Server_motiv::getInstance().liste_server.size());
	}

	const char* warning = "";

	if (pDiscoveredServer->serverDescription.bConnectionInfoValid == false)
	{
		warning = " (WARNING: Legacy server, could not autodetect settings. Auto-connect may not work reliably.)";
	}

	printf("[%c] %s %d.%d at %s%s\n",
		serverHotkey,
		pDiscoveredServer->serverDescription.szHostApp,
		pDiscoveredServer->serverDescription.HostAppVersion[0],
		pDiscoveredServer->serverDescription.HostAppVersion[1],
		pDiscoveredServer->serverAddress,
		warning);

	Server_motiv::getInstance().liste_server.push_back(*pDiscoveredServer);
}

void Server_motiv::recherche_server() {
	NatNetDiscoveryHandle discovery;
	NatNet_CreateAsyncServerDiscovery(&discovery, gestion_decouverte_server);

	printf("Recherche du server local \n");
	printf("Selectionnez un server en saississant le numero qui lui est associe\n");


	while (const int c = _getch())
	{
		if (c >= '1' && c <= '9')
		{
			const size_t serverIndex = c - '1';
			if (serverIndex < liste_server.size())
			{
				const sNatNetDiscoveredServer& discoveredServer = liste_server[serverIndex];

				if (discoveredServer.serverDescription.bConnectionInfoValid)
				{
					// Build the connection parameters.
					_snprintf_s(
						g_discoveredMulticastGroupAddr, sizeof g_discoveredMulticastGroupAddr,
						"%" PRIu8 ".%" PRIu8".%" PRIu8".%" PRIu8"",
						discoveredServer.serverDescription.ConnectionMulticastAddress[0],
						discoveredServer.serverDescription.ConnectionMulticastAddress[1],
						discoveredServer.serverDescription.ConnectionMulticastAddress[2],
						discoveredServer.serverDescription.ConnectionMulticastAddress[3]
					);

					parametre_connexion.connectionType = discoveredServer.serverDescription.ConnectionMulticast ? ConnectionType_Multicast : ConnectionType_Unicast;
					parametre_connexion.serverCommandPort = discoveredServer.serverCommandPort;
					parametre_connexion.serverDataPort = discoveredServer.serverDescription.ConnectionDataPort;
					parametre_connexion.serverAddress = discoveredServer.serverAddress;
					parametre_connexion.localAddress = discoveredServer.localAddress;
					parametre_connexion.multicastAddress = g_discoveredMulticastGroupAddr;
				}
				else
				{
					// We're missing some info because it's a legacy server.
					// Guess the defaults and make a best effort attempt to connect.
					parametre_connexion.connectionType = kDefaultConnectionType;
					parametre_connexion.serverCommandPort = discoveredServer.serverCommandPort;
					parametre_connexion.serverDataPort = 0;
					parametre_connexion.serverAddress = discoveredServer.serverAddress;
					parametre_connexion.localAddress = discoveredServer.localAddress;
					parametre_connexion.multicastAddress = NULL;
				}

				break;
			}
		}
	}

	//on libere la recherche de serveur car on en a trouvé un
	NatNet_FreeAsyncServerDiscovery(discovery);
}

void Server_motiv::connexion_server() {
	// Release previous server
	g_pClient->Disconnect();

	// Init Client and connect to NatNet server
	int retCode = g_pClient->Connect(parametre_connexion);
	if (retCode != ErrorCode_OK)
	{
		std::cout << "erreur de connexion au serveur" << std::endl;
		exit(-1);
	}
	else
	{
		// connection succeeded

		void* pResult;
		int nBytes = 0;
		ErrorCode ret = ErrorCode_OK;

		// print server info
		memset(&g_serverDescription, 0, sizeof(g_serverDescription));
		ret = g_pClient->GetServerDescription(&g_serverDescription);
		if (ret != ErrorCode_OK || !g_serverDescription.HostPresent)
		{
			printf("Unable to connect to server. Host not present. Exiting.");
			exit(-1);
		}
		printf("\n[SampleClient] Server application info:\n");
		printf("Application: %s (ver. %d.%d.%d.%d)\n", g_serverDescription.szHostApp, g_serverDescription.HostAppVersion[0],
		g_serverDescription.HostAppVersion[1], g_serverDescription.HostAppVersion[2], g_serverDescription.HostAppVersion[3]);
		printf("NatNet Version: %d.%d.%d.%d\n", g_serverDescription.NatNetVersion[0], g_serverDescription.NatNetVersion[1],
		g_serverDescription.NatNetVersion[2], g_serverDescription.NatNetVersion[3]);
		printf("Client IP:%s\n", parametre_connexion.localAddress);
		printf("Server IP:%s\n", parametre_connexion.serverAddress);
		printf("Server Name:%s\n", g_serverDescription.szHostComputerName);

		// get mocap frame rate
		ret = g_pClient->SendMessageAndWait("FrameRate", &pResult, &nBytes);
		if (ret == ErrorCode_OK)
		{
			float fRate = *((float*)pResult);
			printf("Mocap Framerate : %3.2f\n", fRate);
		}
		else {
			printf("Error getting frame rate.\n");
		}
			// get # of analog samples per mocap frame of data
		ret = g_pClient->SendMessageAndWait("AnalogSamplesPerMocapFrame", &pResult, &nBytes);
		if (ret == ErrorCode_OK)
		{
			g_analogSamplesPerMocapFrame = *((int*)pResult);
			printf("Analog Samples Per Mocap Frame : %d\n", g_analogSamplesPerMocapFrame);
		}
		else {
			printf("Error getting Analog frame rate.\n");
		}
	}
	std::cout << "connecte au server" << std::endl;
}

void Server_motiv::run()
{
	//création du clien natnet : 
	g_pClient = new NatNetClient();
	//on link la fonction qui va gerer ce qu'il se passe lorsque l'on recoit un message du serveur
	g_pClient->SetFrameReceivedCallback(gestion_data, g_pClient);
	//on se mets a la recherche d'un serveur NatNet lancé par optitrack 
	//et on demande a l'utilisateur de selectionner celui qui lui semble le plus approprié dans la liste
	recherche_server();
	//on se conncte , et si il y a une erreur on arrete le programme
	connexion_server();

	// Ready to receive marker stream!
	printf("\nClient is connected to server and listening for data...\n");
	
	
}

Server_motiv::~Server_motiv() {
	if (g_pClient)
	{
		g_pClient->Disconnect();
		delete g_pClient;
		g_pClient = NULL;
	}
}

void Server_motiv::delete_instance() {
	delete instance;
}
