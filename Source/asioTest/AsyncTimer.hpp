#include <boost/asio.hpp>

class AsyncTimer {
public:
    void print(const boost::system::error_code& e, boost::asio::steady_timer* t, int* count);

public:
    void Run();
};