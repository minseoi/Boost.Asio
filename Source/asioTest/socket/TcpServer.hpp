#include <string>
using namespace std;

class TcpServer
{
private:
    std::string make_daytime_string();

public:
    void Run();   
};