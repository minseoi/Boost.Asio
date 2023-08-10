#include "Printer.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>

Printer::Printer(boost::asio::io_context& io)
    : strand_(boost::asio::make_strand(io))
    , timer1_(io, boost::asio::chrono::seconds(1))
    , timer2_(io, boost::asio::chrono::seconds(1))
    , count_(0)
{
    timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print1, this)));
    timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print2, this)));
}

void Printer::print1()
{
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

      timer1_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&Printer::print1, this)));
    }
}

void Printer::print2()
{
if (count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

      timer2_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&Printer::print2, this)));
    }
}