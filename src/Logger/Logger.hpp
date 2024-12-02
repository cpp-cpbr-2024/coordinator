#pragma once
#include <Comm.hpp>
#include <fstream>

class Logger
{
public:
    Logger(boost::asio::io_context& ioContext);
    ~Logger();

    void start();
    void stop();

private:
    RadarRawSubscriber _radar_raw_subscriber;
    FlyingObjectSubscriber _flying_object_subscriber;

    std::ofstream _radar_raw_log;
    std::ofstream _flying_object_log;

    void on_radar_raw_receive(const std::vector<RadarRaw>& data);
    void on_flying_object_receive(const std::vector<FlyingObject>& data);
};