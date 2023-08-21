#include "TcpAsyncServer.hpp"

tcp_connection::tcp_connection(boost::asio::io_context& io_context)
: socket_(io_context)
{
}

TcpAsyncServer::TcpAsyncServer(boost::asio::io_context& io_context, short port)
    : io_context_(io_context)
    , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void TcpAsyncServer::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(io_context_);
    acceptor_.async_accept(new_connection->socket(),
        bind(&TcpAsyncServer::handle_accept, this, new_connection,
        boost::asio::placeholders::error)
    );
}

void TcpAsyncServer::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    if(!error)
    {
        new_connection->start();
    }
    start_accept();
}