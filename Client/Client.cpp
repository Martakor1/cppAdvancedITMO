// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
int main()
{
    std::cout << "Client start!" << std::endl;
    io_context context;
    ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 1000);
    std::cout << "Try to connect" << std::endl;
    boost::system::error_code ec;
    ip::tcp::socket socket(context);
    socket.connect(endpoint, ec);
    while (true) {
       
       if (ec) {
          std::cout << ec.message() << std::endl;
          return 0;
       }
       socket.write_some(buffer("Hello, server!"), ec);
       if (ec) std::cout << ec.message() << " " << std::endl;
       char buf[100];
       socket.read_some(buffer(buf, 99), ec);
       if (ec) std::cout << ec.message();
       std::cout << socket.is_open();
       //socket.close();
       std::cout << "Ответ: " << std::string(buf) << std::endl;
       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}