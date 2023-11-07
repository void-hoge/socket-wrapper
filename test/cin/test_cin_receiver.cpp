#include "../../socket_wrapper.hpp"
#include <iostream>

int main() {
	auto [client, server] = get_receiver_connection(12345);
	constexpr size_t buffsize = 8;
	void *buffer[buffsize];
	size_t len;
	do {
		len = receive_data<buffsize - 1>(client, buffer);
		((char*)buffer)[len] = '\0';
		std::cout << (char*)buffer;
	}while ((long)len > 0);
	close(client);
	close(server);
}
