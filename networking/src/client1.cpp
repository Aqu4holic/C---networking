// author: blackwhite
// file: client1.cpp
// project: networking
// created: 2:50:58 am - 16/12/2023
// -----
// last modified: 5:01:08 am - 16/12/2023
// -----

#include "defines.hpp"

#include <iostream>
#include <string>
#include <winsock2.h>

int main() {
	WSADATA wsa_data;

	// init
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) {
		std::cout << "startup failed: " << WSAGetLastError() << '\n';

		return 0;
	}

	// create socket
	int address_family = AF_INET;
	int type = SOCK_DGRAM;
	int protocol = IPPROTO_UDP;

	SOCKET sock = socket(address_family, type, protocol);

	if (sock == INVALID_SOCKET) {
		std::cout << "socket failed:" << WSAGetLastError() << '\n';

		return 0;
	}

	// send message
	SOCKADDR_IN server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int flags = 0;

	for (char message[SOCKET_BUFFER_SIZE]; ;) {
		std::cin.getline(message, SOCKET_BUFFER_SIZE);

		if (sendto(sock, message, strlen(message), flags,
				(SOCKADDR*) &server_address, sizeof(server_address)) == SOCKET_ERROR) {
			std::cout << "sendto failed " << WSAGetLastError() << '\n';

			return 0;
		}

		if ((std::string) message == "!quit" || ((std::string) message).empty()) {
				break;
			}
	}

	std::cout << "done\n";

	return 0;
}
