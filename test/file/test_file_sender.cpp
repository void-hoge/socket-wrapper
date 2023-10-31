#include "../../socket_wrapper.hpp"
#include <iostream>
#include <fstream>

int main() {
	auto client = get_sender_connection("127.0.0.1", 12345);
	std::ifstream ifs("src.png", std::ios::binary);
	if (!ifs) {
		throw std::runtime_error("Failed to open the file.");
	}
	send_istream<256>(client, ifs);
	close(client);
}
