#ifndef _MARKET_DATA_HPP_
#define _MARKET_DATA_HPP_
#include <map>
#include <string>

struct MarketData {
    std::string ticker;
    int last;
    int bid;
    int ask;

    MarketData(std::string ticker) : ticker(ticker), last(0), bid(0), ask(0) {}
    MarketData(std::string ticker, int last, int bid, int ask)
        : ticker(ticker), last(last), bid(bid), ask(ask) {}

    std::pair<int, int> calc_diff(MarketData& md) {
        int last_diff = md.last - last;
        int mid_diff = (md.ask + md.bid - bid - ask) / 2;
        return std::make_pair(last_diff, mid_diff);
    }
};

struct BasketData {
    BasketData(std::string bskt_id) : basket(bskt_id), last(0), mid(0) {}

    std::string basket;
    int last;
    int mid;
};

#endif