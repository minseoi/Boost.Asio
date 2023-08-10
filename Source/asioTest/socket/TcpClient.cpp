#include "TcpClient.hpp"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void TcpClient::Run()
{
    std::cout<<"TcpClient::Run()"<<std::endl;
    boost::asio::io_context io;
    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve("localhost", "daytime");

    tcp::socket socket(io);
    boost::asio::connect(socket, endpoints);
    std::cout<<"Connected to server"<<std::endl;

    for(;;)
    {
        boost::array<char, 128> buf;
        boost::system::error_code error;
        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        if(error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if(error)
            throw boost::system::system_error(error);

        std::cout.write(buf.data(), len);
    }
}