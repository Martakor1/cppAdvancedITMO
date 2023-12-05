#include <boost/asio.hpp>
#include "Server.cpp"
#include <thread>

using namespace boost::asio;
io_context context;
void handle_clients() {
	context.run();
}

int main()
{
	ip::tcp::endpoint SERVER_ENDPOINT(ip::address::from_string("127.0.0.1"), 1000);
	std::cout << std::thread::hardware_concurrency() << std::endl;
	// дописать со стак оверфлов for (;;) service run
	boost::shared_ptr<EchoServer> serverPtr(new EchoServer(context, SERVER_ENDPOINT));
	serverPtr->start_listen();
	//acceptor.async_accept(socket, on_accept);
	std::vector<std::thread> threads;
	for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
		threads.push_back(std::thread(handle_clients));
	}
	for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
		threads[i].join();
	}
	return 0;
}