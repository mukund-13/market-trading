#ifndef RISK_MANAGEMENT_MODULE_H
#define RISK_MANAGEMENT_MODULE_H

#include <string>
#include <unordered_map>

class RiskManagementModule {
public:
    RiskManagementModule();
    ~RiskManagementModule();

    void updatePosition(const std::string& symbol, double price, int quantity);
    void checkRiskLimits();

private:
    std::unordered_map<std::string, double> positions;
    std::unordered_map<std::string, double> positionLimits;
    double maxDrawdownLimit;
    double currentDrawdown;

    void calculateDrawdown();
};

#endif // RISK_MANAGEMENT_MODULE_H
