#include <iostream>
#include <boost/asio.hpp>
#include "Core/Server.hpp"

int main(int argc, char** argv)
{
    boost::asio::io_context io_context;
    short port = 8123;
    Server server(io_context, port);
    std::cout<<"Server is running on port "<<port<<std::endl;
    io_context.run();

    return 0;
}