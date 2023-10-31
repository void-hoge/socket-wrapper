#include "../../socket_wrapper.hpp"
#include <iostream>

int main() {
	auto client = get_sender_connection("127.0.0.1", 12345);
	send_istream<256>(client, std::cin);
	close(client);
}
