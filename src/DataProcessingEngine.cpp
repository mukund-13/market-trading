#include "DataProcessingEngine.h"
#include <iostream>
#include <numeric>

DataProcessingEngine::DataProcessingEngine() {
    // Initialize data structures
}

DataProcessingEngine::~DataProcessingEngine() {
    // Clean up resources
}

void DataProcessingEngine::processMarketData(const std::string& data) {
    // Parse and process market data
    std::cout << "Processing market data: " << data << std::endl;
}

std::vector<double> DataProcessingEngine::calculateMovingAverage(const std::vector<double>& data, size_t windowSize) {
    std::vector<double> movingAverage;
    if (data.size() < windowSize) {
        return movingAverage;
    }

    double sum = std::accumulate(data.begin(), data.begin() + windowSize, 0.0);
    movingAverage.push_back(sum / windowSize);

    for (size_t i = windowSize; i < data.size(); ++i) {
        sum += data[i] - data[i - windowSize];
        movingAverage.push_back(sum / windowSize);
    }

    return movingAverage;
}
