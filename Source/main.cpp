#include <iostream>
#include "asioTest/socket/TcpServer.hpp"

int main(int argc, char** argv)
{
    TcpServer server;

    try{
        server.Run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}