#ifndef _DATA_SOURCE_HPP_
#define _DATA_SOURCE_HPP_
#include <functional>
#include <string>
#include <vector>

#include "market_data.hpp"

class IDataSource {
   public:
    virtual void Subscribe(std::function<void(MarketData&)> func,
                           std::set<std::string> tickers) = 0;
};

#endif