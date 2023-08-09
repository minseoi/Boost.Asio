#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "asioTest/Printer.hpp"

int main(int argc, char** argv)
{
    boost::asio::io_context io;
    Printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    //io.run();
    t.join();

    return 0;
}