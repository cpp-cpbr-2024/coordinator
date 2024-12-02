#include "src/Logger/Logger.hpp"

int main(int argc, char const *argv[])
{
    boost::asio::io_context io_context;
    io_context.run();

    Logger logger(io_context);
    logger.start();

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    logger.stop();
    return 0;
}
