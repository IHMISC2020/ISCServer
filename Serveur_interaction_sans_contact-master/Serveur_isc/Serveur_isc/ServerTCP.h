#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

// lib c++
#include <iostream>
#include <string>

// lib c
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// lib c perso
// extern "C" {}

#pragma comment (lib, "Ws2_32.lib")

class ServerTCP {
private:
	std::string m_ip, m_port;

	int m_taille_buffer;
	char* m_buffer;

	WSADATA m_wsdata;

	struct addrinfo m_hints;
	struct addrinfo* m_result;

	SOCKET m_socket_ecoute;
	SOCKET m_socket_client;

	bool m_run;
public:
	ServerTCP(const std::string& s_ip, const std::string& s_port);
	virtual ~ServerTCP();

public:

	void set_run(bool value);

	void load_server();
	void load_client();
	void run2();

	std::string attend_message();
	void envoi_message(const std::string& message);
};

