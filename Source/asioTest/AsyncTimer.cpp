#include "AsyncTimer.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>

void AsyncTimer::print(const boost::system::error_code& e, boost::asio::steady_timer* t, int* count)
{
    if(*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(&AsyncTimer::print, this, boost::asio::placeholders::error, t, count));
    }
}

void AsyncTimer::Run() {
    std::cout << "[Run Start]" << std::endl;
    
    int count = 0;
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.async_wait(boost::bind(&AsyncTimer::print, this, boost::asio::placeholders::error, &t, &count));
    io.run();
    std::cout << "Last Pang is " << count << std::endl;

    std::cout << "[Run End]" << std::endl;
}