#include "MarketDataFeedHandler.h"
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

MarketDataFeedHandler::MarketDataFeedHandler() {
    // Initialize network components
}

MarketDataFeedHandler::~MarketDataFeedHandler() {
    // Clean up resources
}

void MarketDataFeedHandler::connect(const std::string& server, int port) {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(server, std::to_string(port));
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Connected to " << server << ":" << port << std::endl;

        // Example of receiving data
        for (;;) {
            char buf[1024];
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::string data(buf, len);
            if (dataCallback) {
                dataCallback(data);
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void MarketDataFeedHandler::setMarketDataCallback(MarketDataCallback callback) {
    dataCallback = callback;
}
