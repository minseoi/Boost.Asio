#include <iostream>
#include "asioTest/socket/TcpClient.hpp"
#include "asioTest/socket/TcpAsyncServer.hpp"

int main(int argc, char** argv)
{
    bool bIsServerCode = false;
    if(bIsServerCode)
    {
        boost::asio::io_context io_context;
        TcpAsyncServer server(io_context, 13);
        io_context.run();
    }
    else
    {
        TcpClient client;
        client.Run();
    }

    return 0;
}