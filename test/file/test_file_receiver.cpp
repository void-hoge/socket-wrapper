#include "../../socket_wrapper.hpp"
#include <iostream>
#include <fstream>

int main() {
	auto [client, server] = get_receiver_connection(12345);
	constexpr size_t buffsize = 256;
	void *buffer[buffsize];
	std::ofstream ofs("dst.png");
	if (!ofs) {
		throw std::runtime_error("Failed to open the file.");
	}
	while (true) {
		long len = receive_data<buffsize>(client, buffer);
		if (len <= 0) {
			break;
		}
		ofs.write((char*)buffer, len);
	}
	ofs.close();
	close(client);
	close(server);
}
