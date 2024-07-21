#include "MarketDataFeedHandler.h"
#include "DataProcessingEngine.h"
#include "MovingAverageCrossoverStrategy.h"
#include "OrderExecutionEngine.h"
#include "RiskManagementModule.h"
#include <iostream>
#include <sstream>

void onMarketDataReceived(const std::string& data, DataProcessingEngine& engine, MovingAverageCrossoverStrategy& strategy) {
    // Example: Parse data assuming it is in the format "SYMBOL,PRICE"
    std::istringstream ss(data);
    std::string symbol;
    std::string priceStr;
    if (std::getline(ss, symbol, ',') && std::getline(ss, priceStr)) {
        double price = std::stod(priceStr);
        engine.processMarketData(data); // Update data processing engine
        strategy.onMarketData(symbol, price); // Update trading strategy
    }
}

int main() {
    MarketDataFeedHandler marketDataHandler;
    DataProcessingEngine dataProcessingEngine;
    OrderExecutionEngine orderExecutionEngine;
    RiskManagementModule riskManagementModule;
    MovingAverageCrossoverStrategy tradingStrategy(5, 20, orderExecutionEngine, riskManagementModule); // Example windows: 5 and 20

    marketDataHandler.setMarketDataCallback([&dataProcessingEngine, &tradingStrategy](const std::string& data) {
        onMarketDataReceived(data, dataProcessingEngine, tradingStrategy);
    });

    marketDataHandler.connect("example.com", 12345); // Replace with actual server and port

    return 0;
}
