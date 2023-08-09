#include <boost/asio.hpp>

class Printer
{
private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;

public:
    Printer(boost::asio::io_context& io);

    void print1();
    void print2();
};