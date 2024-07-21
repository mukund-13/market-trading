#include "MovingAverageCrossoverStrategy.h"
#include <iostream>

MovingAverageCrossoverStrategy::MovingAverageCrossoverStrategy(size_t shortWindow, size_t longWindow, OrderExecutionEngine& orderEngine, RiskManagementModule& riskModule)
    : shortWindow(shortWindow), longWindow(longWindow), orderExecutionEngine(orderEngine), riskManagementModule(riskModule) {}

MovingAverageCrossoverStrategy::~MovingAverageCrossoverStrategy() {}

void MovingAverageCrossoverStrategy::onMarketData(const std::string& symbol, double price) {
    priceHistory[symbol].push_back(price);
    if (priceHistory[symbol].size() > longWindow) {
        generateSignal(symbol);
    }
}

void MovingAverageCrossoverStrategy::onTradeSignal(const std::string& symbol, const std::string& signal) {
    std::cout << "Trade Signal for " << symbol << ": " << signal << std::endl;
    if (signal == "BUY") {
        positions[symbol] = true;
        orderExecutionEngine.placeOrder(symbol, "BUY", priceHistory[symbol].back(), 100); // Example quantity
        riskManagementModule.updatePosition(symbol, priceHistory[symbol].back(), 100);
    } else if (signal == "SELL") {
        positions[symbol] = false;
        orderExecutionEngine.placeOrder(symbol, "SELL", priceHistory[symbol].back(), 100); // Example quantity
        riskManagementModule.updatePosition(symbol, priceHistory[symbol].back(), -100);
    }
}

void MovingAverageCrossoverStrategy::generateSignal(const std::string& symbol) {
    const auto& prices = priceHistory[symbol];
    auto shortMA = dataProcessingEngine.calculateMovingAverage(prices, shortWindow);
    auto longMA = dataProcessingEngine.calculateMovingAverage(prices, longWindow);

    if (shortMA.back() > longMA.back() && !positions[symbol]) {
        onTradeSignal(symbol, "BUY");
    } else if (shortMA.back() < longMA.back() && positions[symbol]) {
        onTradeSignal(symbol, "SELL");
    }
}
