#include "Logger.hpp"
#include <boost/filesystem.hpp>

Logger::Logger(boost::asio::io_context &ioContext)
    : _radar_raw_subscriber(ioContext),
      _flying_object_subscriber(ioContext)
{   
    boost::filesystem::path log_dir("logs");
    if (boost::filesystem::exists(log_dir)) {
        boost::filesystem::remove_all(log_dir);
    }
    boost::filesystem::create_directory(log_dir);

    _radar_raw_log.open("logs/radar_raw.log", std::ios::out | std::ios::app);
    _flying_object_log.open("logs/flying_object.log", std::ios::out | std::ios::app);

    _radar_raw_log << "id, timestamp, range, azimuth, radial_velocity" << std::endl;
    _flying_object_log << "id, timestamp, position_x, position_y, velocity_x, velocity_y" << std::endl;

    _radar_raw_subscriber.set_on_receive(std::bind(&Logger::on_radar_raw_receive, this, std::placeholders::_1));
    _flying_object_subscriber.set_on_receive(std::bind(&Logger::on_flying_object_receive, this, std::placeholders::_1));
}

Logger::~Logger()
{
    _radar_raw_log.close();
    _flying_object_log.close();
}

void Logger::start()
{
    _radar_raw_subscriber.start();
    _flying_object_subscriber.start();
}

void Logger::stop()
{
    _radar_raw_subscriber.stop();
    _flying_object_subscriber.stop();
}

void Logger::on_radar_raw_receive(const std::vector<RadarRaw> &data)
{
    for (const auto &radar_raw : data)
    {
        _radar_raw_log << radar_raw.id << ", "
                       << radar_raw.timestamp.get_seconds() << ", "
                       << radar_raw.range.get_meters() << ", "
                       << radar_raw.azimuth.get_degrees() << ", "
                       << radar_raw.radial_velocity.get_meters_per_second() << std::endl;
        _radar_raw_log.flush();
    }
}

void Logger::on_flying_object_receive(const std::vector<FlyingObject> &data)
{
    for (const auto &flying_object : data)
    {
        _flying_object_log << flying_object.id << ", "
                           << flying_object.timestamp.get_seconds() << ", "
                           << flying_object.position.x.get_meters() << ", "
                           << flying_object.position.y.get_meters() << ", "
                           << flying_object.velocity.x.get_meters_per_second() << ", "
                           << flying_object.velocity.y.get_meters_per_second() << std::endl;
        _flying_object_log.flush();
    }
}
