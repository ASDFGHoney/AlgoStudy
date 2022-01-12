#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void init();
int buy(int mNumber, int mStock, int mQuantity, int mPrice);
int sell(int mNumber, int mStock, int mQuantity, int mPrice);
void cancel(int mNumber);
int bestProfit(int mStock);
int apply();

class order{
public:
    bool isBuy;
    int mNumber;
    int mStock;
    int mQuantity;
    int mPrice;

    order(bool isBuy, int mNumber, int mStock, int mQuantity, int mPrice){
        this->mNumber = mNumber;
        this->mStock = mStock;
        this->mQuantity = mQuantity;
        this->mPrice = mPrice;
        this->isBuy = isBuy;
    }
};

class marcket{
public:
    int curNum;
    vector<vector<order*>> waitForBuy;
    int waitForBuyCnt[6];
    vector<vector<order*>> waitForSell;
    int waitForSellCnt[6];
    vector<pair<int, order*>> forSearch;

    void init(){
        curNum = 0;
        forSearch.push_back(make_pair(NULL,nullptr));
        for(int i = 0 ; i < 6 ; i++) {
            waitForBuyCnt[i] = 0;
            waitForSellCnt[i] = 0;
            vector<order *> newVec1;
            vector<order *> newVec2;
            waitForBuy.push_back(newVec1);
            waitForSell.push_back(newVec2);
        }
    }
} mart;

int apply(){

}

void init()
{
    mart.init();
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    mart.curNum++;
    auto *newOrder = new order(true, mNumber, mStock, mQuantity, mPrice);
    mart.forSearch.push_back(make_pair(mart.waitForBuy[mStock].size(),newOrder));
    mart.waitForBuyCnt[mStock]++;
    mart.waitForBuy[mStock].push_back(newOrder);
    return apply();
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    mart.curNum++;
    auto *newOrder = new order(false, mNumber, mStock, mQuantity, mPrice);
    mart.forSearch.push_back(make_pair(mart.waitForBuy[mStock].size(),newOrder));
    mart.waitForSellCnt[mStock]++;
    mart.waitForSell[mStock].push_back(newOrder);
    return apply();
}

void cancel(int mNumber)
{
    pair<int, order*> wantCancelOrder = mart.forSearch[mNumber];
    if(wantCancelOrder.second->isBuy){
        mart.waitForBuy[wantCancelOrder.second->mStock][wantCancelOrder.first] = nullptr;
        mart.waitForBuyCnt[wantCancelOrder.second->mStock]--;
    }else{
        mart.waitForBuy[wantCancelOrder.second->mStock][wantCancelOrder.first] = nullptr;
        mart.waitForSellCnt[wantCancelOrder.second->mStock]--;
    }
}

int bestProfit(int mStock)
{
    return 0;
}