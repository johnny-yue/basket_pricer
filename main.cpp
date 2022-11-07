#include <iostream>

#include "market_data.hpp"
#include "pricer.hpp"
#include "tick_gen.hpp"

std::map<std::string, std::vector<std::string>> LoadConfig() {
    // open the file
    // read data into a map<basket, vector<symbol>> structure
    return {};
}

std::map<std::string, std::vector<std::string>> LoadConfigMock() {
    // IBM belongs to two basket
    std::vector<std::string> a_list{"AAPL", "AMD", "AMZN", "IBM"};
    std::vector<std::string> b_list{"BAC", "BABA", "IBM"};

    std::map<std::string, std::vector<std::string>> config{{"A", a_list}, {"B", b_list}};
    return config;
}

// MarketData comes in
// calc price-delta
// for each basket that it belongs to.
// get the weight associated with the basket
// update the basket price
int main() {
    auto config = LoadConfigMock();
    Pricer pricer{config};
    TickGen tick_gen;

    pricer.Subscribe(tick_gen);

    // tick_gen.Start();
    tick_gen.TestRun();
}