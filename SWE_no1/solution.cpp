#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void init();
int buy(int mNumber, int mStock, int mQuantity, int mPrice);
int sell(int mNumber, int mStock, int mQuantity, int mPrice);
void cancel(int mNumber);
int bestProfit(int mStock);

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
struct cmpBuys{
    bool operator() (order* or0, order* or1){
        if(or0->mPrice == or1->mPrice)
            return or0->mNumber < or1->mNumber;
        else
            return or0->mPrice > or1->mPrice;
    }
};
struct cmpSells{
    bool operator() (order* or0, order* or1){
        if(or0->mPrice == or1->mPrice)
            return or0->mNumber < or1->mNumber;
        else
            return or0->mPrice < or1->mPrice;
    }
};

class marcket{
public:
    order* curOrder;
    int waitForBuyCnt[6];
    int waitForSellCnt[6];
    vector<priority_queue<order*,vector<order*>,cmpBuys>> waitForBuy;
    vector<priority_queue<order*,vector<order*>,cmpSells>> waitForSell;
    vector<order*> forSearch;

    vector<vector<int>> forTimeTraveler;

    void init(){
        curOrder = nullptr;
        forSearch.push_back(nullptr);
        for(int i = 0 ; i < 6 ; i++) {
            waitForBuyCnt[i] = 0;
            waitForSellCnt[i] = 0;
            priority_queue<order*,vector<order*>,cmpBuys> newVec1;
            priority_queue<order*,vector<order*>,cmpSells> newVec2;
            vector<int> newVec3;
            waitForBuy.push_back(newVec1);
            waitForSell.push_back(newVec2);
            forTimeTraveler.push_back(newVec3);
        }
    }
    int apply(){
        if(curOrder->isBuy){
            if(!waitForSell[curOrder->mStock].empty() && waitForSell[curOrder->mStock].top()->mPrice <= curOrder->mPrice){
                forTimeTraveler[curOrder->mStock].push_back(waitForSell[curOrder->mStock].top()->mPrice);
                if(waitForSell[curOrder->mStock].top()->mQuantity < curOrder->mQuantity){
                    curOrder->mQuantity -= waitForSell[curOrder->mStock].top()->mQuantity;
                    waitForSell[curOrder->mStock].pop();
                    return apply();
                }else if(waitForSell[curOrder->mStock].top()->mQuantity > curOrder->mQuantity){
                    waitForSell[curOrder->mStock].top()->mQuantity-= curOrder->mQuantity;
                    return 0;
                }else{
                    waitForSell[curOrder->mStock].pop();
                    return 0;
                }
            }
        }else{
            if(!waitForBuy[curOrder->mStock].empty() && waitForBuy[curOrder->mStock].top()->mPrice >= curOrder->mPrice){
                forTimeTraveler[curOrder->mStock].push_back(waitForBuy[curOrder->mStock].top()->mPrice);
                if(waitForBuy[curOrder->mStock].top()->mQuantity < curOrder->mQuantity){
                    curOrder->mQuantity -= waitForBuy[curOrder->mStock].top()->mQuantity;
                    waitForBuy[curOrder->mStock].pop();
                    return apply();
                }else if(waitForBuy[curOrder->mStock].top()->mQuantity > curOrder->mQuantity){
                    waitForBuy[curOrder->mStock].top()->mQuantity-= curOrder->mQuantity;
                    return 0;
                }else{
                    waitForBuy[curOrder->mStock].pop();
                    return 0;
                }
            }
        }
        return curOrder->mQuantity;
    }
} mart;

void init()
{
    mart.init();
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    order* newOrder = new order(true, mNumber, mStock, mQuantity, mPrice);
    mart.curOrder = newOrder;
    mart.forSearch.push_back(newOrder);
    int re = mart.apply();
    if(re == 0)
        return 0;

    mart.waitForBuyCnt[mStock]++;
    mart.waitForBuy[mStock].push(newOrder);
    return re;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    order* newOrder = new order(false, mNumber, mStock, mQuantity, mPrice);
    mart.curOrder = newOrder;
    mart.forSearch.push_back(newOrder);
    int re = mart.apply();
    if(re == 0)
        return 0;

    mart.waitForSellCnt[mStock]++;
    mart.waitForSell[mStock].push(newOrder);
    return re;
}

void cancel(int mNumber)
{
    mart.forSearch[mNumber]->mQuantity = 0;
}

int bestProfit(int mStock)
{
    int max = 0;

    vector<int> temp = mart.forTimeTraveler[mStock];
    int frontTmp = temp[0];
    for(int i = 1 ; i < temp.size(); i++){
        if(frontTmp > temp[i]){
            frontTmp = temp[i];
            continue;
        }
        for(int j = i-1; j >=0 ;j--){
            if((temp[i]-temp[j]) > max){
                max = temp[i]-temp[j];
            }
        }
    }
    return max;
}