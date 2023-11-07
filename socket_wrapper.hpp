#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
#include <fstream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

inline int get_sender_connection(std::string addr, int port, int domain=AF_INET, int type=SOCK_STREAM, int protocol=0) {
	int sock = socket(domain, type, protocol);
	if (sock == -1) {
		throw std::runtime_error("Failed to create a socket.");
	}
	struct sockaddr_in dst;
	dst.sin_family = domain;
	dst.sin_port = htons(port);
	dst.sin_addr.s_addr = inet_addr(addr.c_str());

	if (connect(sock, (struct sockaddr *)&dst, sizeof(dst)) == -1) {
		std::stringstream ss;
		ss << "Failed to connect to port " << port << " of " << addr << "." << std::endl;
		throw std::runtime_error(ss.str());
	}
	return sock;
}

inline std::pair<int, int> get_receiver_connection(int port, int domain=AF_INET, int type=SOCK_STREAM, int protocol=0) {
	int server = socket(domain, type, protocol);
	if (server == -1) {
		throw std::runtime_error("Failed to create a socket.");
	}
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = domain;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
		close(server);
		throw std::runtime_error("Failed to bind a socket.");
	}

	if (listen(server, 5) == -1) {
		close(server);
		throw std::runtime_error("Failed to connect to a client.");
	}

	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);
	int client = accept(server, (struct sockaddr *)&clientaddr, &clientlen);
	if (client == -1) {
		close(server);
		throw std::runtime_error("Failed to accept a client.");
	}

	return {client, server};
}

inline bool send_data(int sock, void *data, size_t len) {
	// returns true when finished normally
	return send(sock, data, len, 0) != -1;
}

template<size_t len>
inline void send_istream(int sock, std::istream& is) {
	char buffer[len];
	while (is) {
		is.read(buffer, len);
		std::streamsize readlen = is.gcount();
		if (!send_data(sock, buffer, readlen)) {
			throw std::runtime_error("Failed to send data");
		}
	}
}

template<size_t len>
inline size_t receive_data(int sock, void *buffer) {
	return recv(sock, buffer, len, 0);
}
