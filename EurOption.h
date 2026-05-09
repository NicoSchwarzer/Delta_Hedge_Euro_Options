#ifndef EurOption_h
#define EurOption_h
#include "BinModel.h"
#include "BinLattice.h"

class EurOption
{
private:
    int N; //steps to expiry
    double (*Payoff)(double S, double K);
    BinLattice PriceTree;
    BinLattice StockPositionsTree;
    BinLattice BondPositionsTree;
    bool PriceTreeComputed = false;
    bool StockPositionsTreeComputed = false;
    bool BondPositionsTreeComputed = false;



public:

    // Constructor
    EurOption(int N_);


    void SetPayoff(double (*Payoff_)(double S, double K))
    {
        Payoff=Payoff_;
    }


//pricing European option by CRR formula
    double PriceByCRR(BinModel Model, double K);


    // new function (ex 1.2) to find entire tree of option prices
    void OptionPriceTree(BinModel Model, double K);

    // replicating for time 0
    double ReplicatingStrategyTimeZero(BinModel Model, double K);

    //new function to compute stock positions in replicating strategy
    void ReplicatingStrategyStockPositions(BinModel Model, double K);

    //new function to compute stock positions in replicating strategy
    void ReplicatingStrategyBondPositions(BinModel Model, double K);

    int getN();

    // getter functions for prices and replicating strategies for n,i
    double GetPrice(int n, int i);
    double GetReplicatingX(int n, int i);
    double GetReplicatingY(int n, int i);

    // Functions to display Full Trees;
    void DisplayPriceTree();
    void DisplayStockPositionsTree();
    void DisplayBondPositionsTree();


};
//computing the number of n-element subsets in an N-element set
double NewtonSymb(int N, int n);
//coumputing call payoff

double CallPayoff(double S, double K);
class EurCall: public EurOption
{
private:
    double K; //strike price
public:
    EurCall(int N_) : EurOption(N_)
    {
        SetPayoff(CallPayoff);
    }
    int GetInputData();


    double PriceByCRR(BinModel Model)
    {
        return EurOption::PriceByCRR(Model, K);
    }
    void OptionPriceTree(BinModel Model)
    {
        EurOption::OptionPriceTree(Model, K);
    }

    double ReplicatingStrategyTimeZero(BinModel Model)
    {
        return EurOption::ReplicatingStrategyTimeZero(Model, K);
    }
    void ReplicatingStrategyStockPositions(BinModel Model)
    {
        EurOption::ReplicatingStrategyStockPositions(Model, K);
    }
    void ReplicatingStrategyBondPositions(BinModel Model)
    {
        EurOption::ReplicatingStrategyBondPositions(Model, K);
    }

};
//coumputing put payoff
double PutPayoff(double S, double K);
class EurPut: public EurOption
{
private:
    double K; //strike price
public:
    EurPut(int N_) : EurOption(N_)
    {
        SetPayoff(PutPayoff);
    }
    int GetInputData();
    double PriceByCRR(BinModel Model)
    {
        return EurOption::PriceByCRR(Model, K);
    }

    void OptionPriceTree(BinModel Model)
    {
        EurOption::OptionPriceTree(Model, K);
    }

    double ReplicatingStrategyTimeZero(BinModel Model)
    {
        return EurOption::ReplicatingStrategyTimeZero(Model, K);
    }
    void ReplicatingStrategyStockPositions(BinModel Model)
    {
        EurOption::ReplicatingStrategyStockPositions(Model, K);
    }
    void ReplicatingStrategyBondPositions(BinModel Model)
    {
        EurOption::ReplicatingStrategyBondPositions(Model, K);
    }


};
#endif
