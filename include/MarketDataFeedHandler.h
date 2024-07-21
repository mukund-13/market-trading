#ifndef MARKET_DATA_FEED_HANDLER_H
#define MARKET_DATA_FEED_HANDLER_H

#include <string>
#include <functional>

class MarketDataFeedHandler {
public:
    using MarketDataCallback = std::function<void(const std::string&)>;

    MarketDataFeedHandler();
    ~MarketDataFeedHandler();

    void connect(const std::string& server, int port);
    void setMarketDataCallback(MarketDataCallback callback);

private:
    MarketDataCallback dataCallback;
    // Add private members for network handling
};

#endif // MARKET_DATA_FEED_HANDLER_H
