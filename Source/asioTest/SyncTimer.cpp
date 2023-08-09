#include "SyncTimer.hpp"
#include <iostream>
#include <boost/asio.hpp>

void SyncTimer::Run() {
    std::cout << "TimerStart!" << std::endl;
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.wait();
    
    std::cout << "TimerEnd" << std::endl;
}