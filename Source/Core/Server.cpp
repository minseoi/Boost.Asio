#include "Server.hpp"
#include <ctime>

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
: m_socket(io_context)
{
}

tcp::socket& TcpConnection::socket()
{
    return m_socket;
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
    return pointer(new TcpConnection(io_context));
}

void TcpConnection::start()
{
    // time_t now = time(0);
    // readyForWrite(ctime(&now));
    readyForRead();
}

void TcpConnection::readyForWrite(std::string message)
{
    writeBuffer = message;
    boost::asio::async_write(m_socket, boost::asio::buffer(writeBuffer), boost::bind(&TcpConnection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
    if(!error)
    {
        std::cout << "Send: " << writeBuffer << std::endl;
    }
}

void TcpConnection::readyForRead()
{
    readBuffer.clear();
    boost::asio::async_read(m_socket, boost::asio::buffer(readBuffer), boost::bind(&TcpConnection::handle_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if(!error)
    {
        std::cout << "Receive: " << readBuffer << std::endl;
        readyForRead();
    }
}

Server::Server(boost::asio::io_context& io_context, short port)
: m_io_context(io_context)
, m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void Server::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(m_io_context);
    m_acceptor.async_accept(new_connection->socket(), boost::bind(&Server::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void Server::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error)
{
    if(!error)
    {
        new_connection->start();
    }
    start_accept(); 
}