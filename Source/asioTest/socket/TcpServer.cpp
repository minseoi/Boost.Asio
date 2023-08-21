#include "TcpServer.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "../../basis/Statics.hpp"

using boost::asio::ip::tcp;

void TcpServer::Run()
{
    boost::asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13)); // listen on port 13

    for(;;)
    {
        tcp::socket socket(io);
        acceptor.accept(socket);
        std::string message = Statics::make_daytime_string();
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
}