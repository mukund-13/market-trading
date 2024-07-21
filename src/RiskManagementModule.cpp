#include "RiskManagementModule.h"
#include <iostream>

RiskManagementModule::RiskManagementModule() : maxDrawdownLimit(0.2), currentDrawdown(0.0) {
    // Initialize position limits (example values)
    positionLimits["AAPL"] = 1000.0;
    positionLimits["GOOGL"] = 1000.0;
}

RiskManagementModule::~RiskManagementModule() {}

void RiskManagementModule::updatePosition(const std::string& symbol, double price, int quantity) {
    positions[symbol] += price * quantity;
    calculateDrawdown();
    checkRiskLimits();
}

void RiskManagementModule::checkRiskLimits() {
    for (const auto& position : positions) {
        if (position.second > positionLimits[position.first]) {
            std::cerr << "Risk limit exceeded for " << position.first << "!" << std::endl;
            // Implement logic to handle risk limit breach
        }
    }

    if (currentDrawdown > maxDrawdownLimit) {
        std::cerr << "Max drawdown limit exceeded!" << std::endl;
        // Implement logic to handle drawdown limit breach
    }
}

void RiskManagementModule::calculateDrawdown() {
    // Implement drawdown calculation logic
    // Example: simple drawdown calculation based on current positions
    double totalValue = 0.0;
    for (const auto& position : positions) {
        totalValue += position.second;
    }
    currentDrawdown = (totalValue < 0) ? -totalValue / totalValue : 0;
}
