#ifndef MOVING_AVERAGE_CROSSOVER_STRATEGY_H
#define MOVING_AVERAGE_CROSSOVER_STRATEGY_H

#include "TradingStrategy.h"
#include "DataProcessingEngine.h"
#include "OrderExecutionEngine.h"
#include "RiskManagementModule.h"
#include <unordered_map>

class MovingAverageCrossoverStrategy : public TradingStrategy {
public:
    MovingAverageCrossoverStrategy(size_t shortWindow, size_t longWindow, OrderExecutionEngine& orderEngine, RiskManagementModule& riskModule);
    ~MovingAverageCrossoverStrategy();

    void onMarketData(const std::string& symbol, double price) override;
    void onTradeSignal(const std::string& symbol, const std::string& signal) override;

private:
    size_t shortWindow;
    size_t longWindow;
    DataProcessingEngine dataProcessingEngine;
    OrderExecutionEngine& orderExecutionEngine;
    RiskManagementModule& riskManagementModule;
    std::unordered_map<std::string, std::vector<double>> priceHistory;
    std::unordered_map<std::string, bool> positions; // True if we have a position, false otherwise

    void generateSignal(const std::string& symbol);
};

#endif // MOVING_AVERAGE_CROSSOVER_STRATEGY_H
