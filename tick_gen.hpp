#ifndef _TICK_GEN_HPP_
#define _TICK_GEN_HPP_

#include <cstdlib>
#include <ctime>
#include <functional>
#include <map>
#include <set>
#include <vector>

#include "data_source.hpp"

class MarketData;

class TickGen : public IDataSource {
   public:
    TickGen() { std::srand(0); }

    void Subscribe(std::function<void(MarketData&)> func, std::set<std::string> tickers) {
        for (auto& ticker : tickers) {
            auto iter = callback_map.find(ticker);
            if (iter == callback_map.end()) {
                callback_map[ticker] = {};
            }

            callback_map[ticker].push_back(func);
        }
    }

    void TestRun() {
        std::vector<MarketData> mdvector;
        mdvector.emplace_back("AAPL", 2000000, 2050000, 2020000);
        mdvector.emplace_back("IBM", 1000000, 1050000, 1020000);
        mdvector.emplace_back("IBM", 1000000, 1050000, 1020000);
        mdvector.emplace_back("IBM", 1010000, 1050000, 1020000);
        mdvector.emplace_back("IBM", 990000, 1050000, 1020000);
        mdvector.emplace_back("IBM", 1000000, 1100000, 900000);

        for (auto& md : mdvector) {
            if (callback_map.find(md.ticker) != callback_map.end()) {
                for (auto& callback : callback_map[md.ticker]) {
                    callback(md);
                }
            }
        }
    }

    void Start() {
        while (true) {
            // find a random ticker to generate market data update

            // Rand x% to move last price vs the previous

            // Rand y% from last price lower to get the bid

            // Rand z% from last price higher to get the ask

            // if the ticker is in the tickers list. call the call back, send market data

            // wait for a random period of time.
        }
    }

   private:
    std::vector<std::string> tickers;
    std::map<std::string, std::vector<std::function<void(MarketData&)>>> callback_map;
};

#endif