#include <Comm.hpp>

int main(int argc, char const *argv[])
{
    boost::asio::io_service io_service;
    RadarRawPublisher radar_raw_pub(io_service);

    return 0;
}
