#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

#include <vector>
#include <string>

class TradingStrategy {
public:
    virtual ~TradingStrategy() = default;
    virtual void onMarketData(const std::string& symbol, double price) = 0;
    virtual void onTradeSignal(const std::string& symbol, const std::string& signal) = 0;
};

#endif // TRADING_STRATEGY_H
