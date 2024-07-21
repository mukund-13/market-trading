#ifndef DATA_PROCESSING_ENGINE_H
#define DATA_PROCESSING_ENGINE_H

#include <string>
#include <vector>

class DataProcessingEngine {
public:
    DataProcessingEngine();
    ~DataProcessingEngine();

    void processMarketData(const std::string& data);
    std::vector<double> calculateMovingAverage(const std::vector<double>& data, size_t windowSize);

private:
    // Add private members for data processing
};

#endif // DATA_PROCESSING_ENGINE_H
