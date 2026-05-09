#include "EurOption.h"
#include "BinModel.h"
#include "BinLattice.h"
#include <iostream>
#include <cmath>
using namespace std;


// Constructor
EurOption::EurOption(int N_)
    : N(N_), PriceTree(N_), StockPositionsTree(N_ - 1), BondPositionsTree(N_ - 1)

{
}

double EurOption::PriceByCRR(BinModel Model, double K)
{
    double p=Model.RiskNeutProb();
    double Price=0;
    for (int n=0; n<=N; n++)
    {
        Price=Price+NewtonSymb(N,n)*pow(p,n)*pow(1-p,N-n)
              *Payoff(Model.S(N,n),K)/pow(Model.GetR(),N);
    }
    return Price;
}

//new function to compute entire tree of option prices
void EurOption::OptionPriceTree(BinModel Model, double K)
{
    double p=Model.RiskNeutProb();
    double R = Model.GetR();

    for (int i=0; i<=N; i++)


    // final values at last time step
    // reminder: SetNode(step n, node i), so here step = N

    {
        PriceTree.SetNode(N,i,Payoff(Model.S(N,i),K) );
    }

    // recursive backwards loop

    for (int n=N-1; n>=0; n--)
    {
        for (int i=0; i<=n; i++)
        {
            // prices at t+1 in up and down cases
            double OptionPriceUp   = PriceTree.GetNode(n + 1, i + 1);
            double OptionPriceDown = PriceTree.GetNode(n + 1, i);

            // finding price using risk neutral probability
             PriceTree.SetNode(n, i, (p * OptionPriceUp + (1-p) * OptionPriceDown) / R);
        }
    }

    // for use in function that rely on the presence of the correct price tree
    PriceTreeComputed = true;


    return;
}


//new function for 1.1 to compute replicating strategy x(0) given y(0)
double EurOption::ReplicatingStrategyTimeZero(BinModel Model, double K)
{
    cout << "Enter y(0) to find corresponding x(0).\n";
    double y0;
    cin >> y0;

    double OptionPrice = PriceByCRR(Model, K);
    double x0 = (OptionPrice - y0 ) / Model.GetS0() ;

    return x0;

}

//new function to compute stock positions in replicating strategy
void EurOption::ReplicatingStrategyStockPositions(BinModel Model, double K)
{

    // Pricing first if not done yet
    if (PriceTreeComputed == false) {
            OptionPriceTree(Model, K);
    }

    for (int n=0; n<N; n++) {
        for (int i=0; i<=n; i++)
        {


            // Option Prices at t+1 in up and down cases
            double OptionPriceUp   = PriceTree.GetNode(n + 1, i + 1);
            double OptionPriceDown = PriceTree.GetNode(n + 1, i);

            // deriving xt using delta hedging
            double xt = (OptionPriceUp - OptionPriceDown) / ( Model.S(n+1,i+1) - Model.S(n+1,i) );
            StockPositionsTree.SetNode(n, i, xt);

        }
    }
    // for use in function that rely on the presence of the correct stock positions tree
    StockPositionsTreeComputed = true;

    return;
}


//new function to compute stock positions in replicating strategy
void EurOption::ReplicatingStrategyBondPositions(BinModel Model, double K)
{
    double R = Model.GetR();


    // Deriving stock positions (and thereby price tree) first -  if not done yet
    if (StockPositionsTreeComputed == false) {
            ReplicatingStrategyStockPositions(Model, K);
    }

    //BinLattice BondPositionsTree(N-1); // only of size N-1 since no rebalancing at N

    for (int n=0; n<N; n++) {
        for (int i=0; i<=n; i++)
        {

            // deriving yt
            double yt = (PriceTree.GetNode(n,i) - StockPositionsTree.GetNode(n,i) * Model.S(n,i) ) / pow(R, n);
            BondPositionsTree.SetNode(n, i, yt);
        }
    }

    // for use in function that rely on the presence of the correct bond positions tree
    BondPositionsTreeComputed = true;

    return;
}


double EurOption::GetPrice(int n, int i){

    // Ensuring that correct price tree exists
    if (PriceTreeComputed == false) {
            cout << "First compute the price tree.\n";
            return 1.0;
    }
    return PriceTree.GetNode(n,i);
}



double EurOption::GetReplicatingX(int n, int i){

    // Ensuring that correct price tree exists
    if (StockPositionsTreeComputed == false) {
            cout << "First compute the stock positions tree.\n";
            return -999999.0;
    }
    if (n==0){ // At time t=0, the position of x(1) is initialized, so this is returned!"
        return StockPositionsTree.GetNode(0,0); //
    }
    else if (i > n) { // such a value does not exist in the tree of bond positions
        cout << "Please use a value for i less than m!\n";
            return -999999.0;
    }
    else if (i < 0 || n < 0) {
        cout << "Please use values for i,m above 0!\n";
            return -999999.0;
    }
    if (i==n){
        return StockPositionsTree.GetNode(n-1,i-1);
    }

    return StockPositionsTree.GetNode(n-1,i); // using n-1 since at position n-1, the value for x(n) is held, e.g. at position n=0, we have x(1)


}

double EurOption::GetReplicatingY(int n, int i){

    // Ensuring that correct price tree exists
    if (BondPositionsTreeComputed == false) {
            cout << "First compute the bond positions tree.\n";
            return -999999.0;
    }
    else if (n==0){ // At time t=0, the position of y(1) is initialized, so this is returned!"
        return BondPositionsTree.GetNode(0,0); //
    }

    else if (i > n) { // such a value does not exist in the tree of bond positions
        cout << "Please use a value for i less or equal than m!\n";
            return -999999.0;
    }
    else if (i < 0 || n < 0) {
        cout << "Please use values for i,m above 0!\n";
            return -999999.0;
    }
    if (i==n){
        return BondPositionsTree.GetNode(n-1,i-1);
    }
    return BondPositionsTree.GetNode(n-1,i); // using n-1 since at position n-1, the value for x(n) is held, e.g. at position n=0, we have x(1)
}



void EurOption::DisplayPriceTree(){
    PriceTree.Display();
}

void EurOption::DisplayStockPositionsTree(){
    StockPositionsTree.Display();
}

void EurOption::DisplayBondPositionsTree(){
    BondPositionsTree.Display();
}


double NewtonSymb(int N, int n)
{
    if (n<0 || n>N) return 0;
    double result=1;
    for (int i=1; i<=n; i++) result=result*(N-n+i)/i;
    return result;
}
double CallPayoff(double S, double K)
{
    if (S>K) return S-K;
    return 0.0;
}
int EurCall::GetInputData()
{
    cout << "Enter European call data:" << endl;
//    cout << "Enter steps to expiry N: ";
//   cin >> N;
    cout << "Enter strike price K: ";
    cin >> K;
    cout << endl;
    cout << "K = " << K << endl;
    cout << endl;
    return 0;
}
double PutPayoff(double S, double K)
{
    if (S<K) return K-S;
    return 0.0;
}
int EurPut::GetInputData()

{
    cout << "Enter European put data:" << endl;
//    cout << "Enter steps to expiry N: ";
//    cin >> N;
    cout << "Enter strike price K: ";
    cin >> K;
    cout << endl;
    cout << "K = " << K << endl;
    cout << endl;
    return 0;
}



int EurOption::getN()
{
    return N;
}

