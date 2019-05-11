/*
 * Copyright (C) Your copyright.
 *
 * Author: Christopher Jordan-Denny
 *
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <lsm9ds1.h>

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(socket_ptr sock) {
	try {
#ifdef DEBUG
		std::cout << "Handling read request..." << std::endl;
#endif
		uint8_t read_buffer = 0;
		lsm9ds1_read(0xF, &read_buffer);
#ifdef DEBUG
		std::cout << (uint32_t) read_buffer << std::endl;
#endif

		boost::asio::write(*sock,
				boost::asio::buffer(&read_buffer, sizeof(read_buffer)));
	} catch (std::exception& e) {
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server(boost::asio::io_service& io_service, short port) {
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;) {
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock));
	}
}

int main(int argc, char* argv[]) {
	try {
		int8_t ret = -1;
		if (argc != 2) {
			std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
			return 1;
		}

#ifdef DEBUG
		std::cout << "Starting lsm9ds1_server..." << std::endl;
		std::cout << "lsm9ds1 init..." << std::endl;
#endif

		ret = lsm9ds1_init(LSM9DS1_SPI_BUS);
		if (ret < 0) {
			return ret;
		}
#ifdef DEBUG
		std::cout << "lsm9ds1 init: SUCCESS" << std::endl;
#endif

		boost::asio::io_service io_service;

#ifdef DEBUG
		std::cout << "Waiting on clients..." << std::endl;
#endif
		server(io_service, atoi(argv[1]));
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
