#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/container/list.hpp>
#include <iostream>
#include <string>
using boost::asio::ip::tcp;

class TcpConnection: public boost::enable_shared_from_this<TcpConnection>
{
private:
    tcp::socket m_socket;
    std::string writeBuffer, readBuffer;

    TcpConnection(boost::asio::io_context& io_context);

public:
    typedef boost::shared_ptr<TcpConnection> pointer;
    tcp::socket& socket();

    //factory method
    static pointer create(boost::asio::io_context& io_context);

    void start();

    void readyForWrite(std::string message);
    void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

    void readyForRead();
    void handle_read(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);
};

class Server
{
private:
    boost::asio::io_context& m_io_context;
    tcp::acceptor m_acceptor;
    boost::container::list<TcpConnection> m_list;

public:
    Server(boost::asio::io_context& io_context, short port);

    void start_accept();

    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
};