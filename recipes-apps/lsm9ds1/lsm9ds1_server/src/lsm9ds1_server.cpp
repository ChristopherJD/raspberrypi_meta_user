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

#include <cstdio>
#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <lsm9ds1.h>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

class session: public boost::enable_shared_from_this<session> {
public:
	session(boost::asio::io_service& io_service) :
			socket_(io_service) {
	}

	stream_protocol::socket& socket() {
		return socket_;
	}

	void start() {
		socket_.async_read_some(boost::asio::buffer(data_),
				boost::bind(&session::handle_read, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred) {
		if (!error) {
			std::cout << "handle read" << std::endl;
			int8_t ret = -1;
			accelerometer_data_t accelerometer_buffer = {0};
			lsm9ds1_read_accel(&accelerometer_buffer);

			boost::asio::async_write(socket_,
					boost::asio::buffer(&accelerometer_buffer.x, 1),
					boost::bind(&session::handle_write, shared_from_this(),
							boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error) {
		if (!error) {
			std::cout << "handle write" << std::endl;
			std::string buffer = "0x0F";
			socket_.async_read_some(boost::asio::buffer(buffer),
					boost::bind(&session::handle_read, shared_from_this(),
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));
		}
	}

private:
	// The socket used to communicate with the client.
	stream_protocol::socket socket_;

	// Buffer used to store data received from the client.
	boost::array<char, 1024> data_;
};

typedef boost::shared_ptr<session> session_ptr;

class server {
public:
	server(boost::asio::io_service& io_service, const std::string& file) :
			io_service_(io_service), acceptor_(io_service,
					stream_protocol::endpoint(file)) {
		session_ptr new_session(new session(io_service_));
		acceptor_.async_accept(new_session->socket(),
				boost::bind(&server::handle_accept, this, new_session,
						boost::asio::placeholders::error));
	}

	void handle_accept(session_ptr new_session,
			const boost::system::error_code& error) {
		if (!error) {
			new_session->start();
			new_session.reset(new session(io_service_));
			acceptor_.async_accept(new_session->socket(),
					boost::bind(&server::handle_accept, this, new_session,
							boost::asio::placeholders::error));
		}
	}

private:
	boost::asio::io_service& io_service_;
	stream_protocol::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
	try {
		if (argc != 2) {
			std::cerr << "Usage: stream_server <file>\n";
			std::cerr << "*** WARNING: existing file is removed ***\n";
			return 1;
		}

		lsm9ds1_status_t ret = LSM9DS1_UNKNOWN_ERROR;
		ret = lsm9ds1_init(LSM9DS1_SPI_BUS, LSM9DS1_ACCELRANGE_8G,
				LSM9DS1_MAGGAIN_8GAUSS, LSM9DS1_GYROSCALE_500DPS);
		std::cout << "Init status:" << (int32_t) ret << std::endl;

		boost::asio::io_service io_service;

		std::remove(argv[1]);
		server s(io_service, argv[1]);

		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
# error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
