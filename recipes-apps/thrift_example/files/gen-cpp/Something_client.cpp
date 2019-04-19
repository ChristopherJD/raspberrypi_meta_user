#include "Something.h"  // As an example

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Test;

int main(int argc, char **argv) {
	std::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	SomethingClient client(protocol);
	transport->open();
	client.ping();
	transport->close();

	return 0;
}
