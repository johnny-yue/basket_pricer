#ifndef _PRICER_HPP_
#define _PRICER_HPP_

#include <cstdlib>
#include <ctime>
#include <functional>
#include <map>
#include <set>
#include <vector>

#include "data_source.hpp"
#include "market_data.hpp"

struct TickerRefData {
    MarketData md;
    std::map<std::string, double> weight_map;

    TickerRefData(std::string ticker) : md(ticker) {}

    void set_weight(std::string basket, double weight) { weight_map[basket] = weight; }
};

class Pricer {
   public:
    Pricer(std::map<std::string, std::vector<std::string>> config) {
        for (auto& [bskt_id, bskt_tickers] : config) {
            int count = bskt_tickers.size();
            for (auto& ticker : bskt_tickers) {
                tickers.insert(ticker);
                ticker_ref_map.insert(std::make_pair(ticker, TickerRefData{ticker}));
                // equal weight
                ticker_ref_map.find(ticker)->second.set_weight(bskt_id, 1.0 / count);
            }

            basket_data.insert(std::make_pair(bskt_id, BasketData{bskt_id}));
        }
    }

    void Subscribe(IDataSource& data_source) {
        auto f = [&](MarketData& md) { this->OnEvent(md); };
        data_source.Subscribe(f, tickers);
    }

    void OnEvent(MarketData& md) {
        auto& ref_data = ticker_ref_map.find(md.ticker)->second;

        auto [last_diff, mid_diff] = ref_data.md.calc_diff(md);

        // update all associated basket according to the weight
        for (auto& [bskt_id, weight] : ref_data.weight_map) {
            if (basket_data.find(bskt_id) == basket_data.end()) {
                // this is a problem
                continue;
            }
            BasketData& bdata = basket_data.find(bskt_id)->second;

            int basket_last_diff = last_diff * weight;
            int basket_mid_diff = mid_diff * weight;
            if (((double)basket_last_diff / bdata.last) > warning_threshold) {
                std::cout << "basket last jumped. basket_last_diff:" << basket_last_diff
                          << ", basket_last" << bdata.last << "\n";
            }
            if (((double)basket_mid_diff / bdata.mid) > warning_threshold) {
                std::cout << "basket mid jumped. basket_mid_diff:" << basket_mid_diff
                          << ", basket_mid" << bdata.mid << "\n";
            }

            // update basket Data
            bdata.last += basket_last_diff;
            bdata.mid += basket_mid_diff;
        }
    }

   private:
    std::set<std::string> tickers;

    // basket : BasketData
    std::map<std::string, BasketData> basket_data;

    // {ticker : TickerRefData}
    std::map<std::string, TickerRefData> ticker_ref_map;

    double warning_threshold = 0.0001;
};

#endif