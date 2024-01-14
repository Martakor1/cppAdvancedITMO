// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <memory>

using namespace boost::asio;
char data[1024];
inline void on_read(const boost::system::error_code&, size_t s) {
	std::cout << "on_read: " << s << std::endl;
	std::cout << std::string(data) << std::endl;
}

inline size_t customCompletion(const boost::system::error_code&, size_t bytes) {
	std::cout << "completion function work " << bytes << std::endl;
	return 100;
}


int main1()
{
	io_context context;
	ip::tcp::endpoint endpoint(ip::address::from_string("192.168.0.1"), 80);
	ip::tcp::socket socket(context);
	socket.connect(endpoint);
	socket.write_some(buffer("GET /\n"));
	//async_read(socket, buffer(data, 1023), on_read);
	//читает из буфера (сокета) последовательно, записывает в буффер (всегда в начало)
	//on_read - сколько считали или 0 если буфер закончился на чтение
	async_read(socket, buffer(data, 1023), transfer_exactly(21), on_read);
	async_read(socket, buffer(data, 1023), transfer_exactly(10), on_read);
	async_read(socket, buffer(data, 1023), on_read);
	memset(data, 0, 1024);
	async_read(socket, buffer(data, 1023), on_read);
	context.run();
	/*context.poll_one();
	context.poll_one();*/
	return 0;
}

int main() {
	int a = 5;
	std::shared_ptr<int> ap(new int(8));
	std::cout << *ap;
	return 0;
}
