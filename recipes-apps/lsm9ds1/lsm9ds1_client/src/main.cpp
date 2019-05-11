#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum {
	max_length = 1
};

int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket s(io_service);
		s.connect(*iterator);

		uint8_t read_buffer = 0;
		size_t reply_length = boost::asio::read(s,
				boost::asio::buffer(&read_buffer, sizeof(read_buffer)));
		std::cout << (uint32_t) read_buffer << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
