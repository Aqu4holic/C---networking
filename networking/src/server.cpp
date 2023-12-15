#include "defines.hpp"

#include <iostream>
#include <format>
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

	// bind socket to address
	SOCKADDR_IN local_address;
	local_address.sin_family = AF_INET;
	local_address.sin_port = htons(PORT);
	local_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (SOCKADDR*) &local_address, sizeof(local_address)) == SOCKET_ERROR) {
		std::cout << "bind failed: " << WSAGetLastError() << '\n';

		return 0;
	}

	// receive message
	char buffer[SOCKET_BUFFER_SIZE];
	int flags = 0;
	SOCKADDR_IN from;
	int from_size = sizeof(from);

	for (int bytes_received; ;) {
		bytes_received = recvfrom(sock, buffer, SOCKET_BUFFER_SIZE, flags,
									(SOCKADDR*) &from, &from_size);

		if (bytes_received == SOCKET_ERROR) {
			std::cout << "recvfrom returned SOCKET_ERROR, "
						"WSAGetLastError(): " << WSAGetLastError() << '\n';

			return 0;
		} else {
			buffer[bytes_received] = 0;

			std::cout << std::format("{}.{}.{}.{}:{} - \"{}\"\n",
									from.sin_addr.S_un.S_un_b.s_b1,
									from.sin_addr.S_un.S_un_b.s_b2,
									from.sin_addr.S_un.S_un_b.s_b3,
									from.sin_addr.S_un.S_un_b.s_b4,
									from.sin_port,
									buffer);

			if ((std::string) buffer == "!quit" || ((std::string) buffer).empty()) {
				break;
			}
		}
	}

	std::cout << "done\n";

	return 0;
}
