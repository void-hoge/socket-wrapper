#include "../../socket_wrapper.hpp"
#include <iostream>

int main() {
	auto [client, server] = get_receiver_connection(12345);
	void *buffer[256];
	size_t len = receive_data(client, buffer, 255);
	do {
		((char*)buffer)[len] = '\0';
		std::cout << (char*)buffer;
		len = receive_data(client, buffer, 256);
	} while ((long)len > 0);
	close(client);
	close(server);
}
