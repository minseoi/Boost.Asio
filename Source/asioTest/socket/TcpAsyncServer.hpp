#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>
#include "../../basis/Statics.hpp"

using boost::asio::ip::tcp;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
private:
    tcp::socket socket_;
    std::string message_;

    tcp_connection(boost::asio::io_context& io_context);

    void handle_write(const boost::system::error_code error, size_t bytes_transfered)
    {

    }

public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
       message_ = Statics::make_daytime_string();
        boost::asio::async_write(socket_, boost::asio::buffer(message_), boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
};

class TcpAsyncServer
{
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;

public:
    TcpAsyncServer(boost::asio::io_context& io_context, short port);

    void start_accept();

    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
};