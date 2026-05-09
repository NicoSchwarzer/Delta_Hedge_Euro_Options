#include "BinModel.h"
#include "EurOption.h"
#include "BinLattice.h"
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    BinModel MyModel;
    if (MyModel.GetInputData()==1) return 1;


    cout << " --- Input & Output for Ex 1.1 --- \n";

    cout << "Enter the number of steps until expiry. \n";
    int N;
    cin >> N;
    EurCall MyOption1(N);

    MyOption1.GetInputData();


    cout << "Option price = "  << MyOption1.PriceByCRR(MyModel) << endl << endl;

    //  replicating strategy stock position using method based on any chosen y(0)
    cout << "Printing out Time 0 Replication strategy stock position based on entered value for y(0).\n";

    double x0 = MyOption1.ReplicatingStrategyTimeZero(MyModel);
    cout << "x(0) for replicating strategy for time 0 is: " << x0 << endl;

    //  pricing based on binomial tree and backward induction
    cout << "Printing out Time 0 option prices using binomial tree and backward induction.\n";
    MyOption1.OptionPriceTree(MyModel);
    cout << "Price at T=0 is " << MyOption1.GetPrice(0,0) <<  endl;


    // replicating strategy stock position using delta hedging
    cout << "Printing out Time 0 Replication strategy stock position using delta hedging.\n";
    MyOption1.ReplicatingStrategyStockPositions(MyModel);
    cout << "x(0) for replicating strategy is " << MyOption1.GetReplicatingX(0,0) <<  endl;

    //  replicating strategy bond position using delta hedging
    cout << "Printing out Time 0 Replication strategy bond position using delta hedging.\n";
    MyOption1.ReplicatingStrategyBondPositions(MyModel);
    cout << "y(0) for replicating strategy is " << MyOption1.GetReplicatingY(0,0) <<  endl;

    cout << " --- Output for Ex 1.2 --- \n";
    cout << "Choose any m,i for exemplary code output for Ex 1.2 -  first m, then i.\n";
    int m_ex12, i_ex12;
    cin >> m_ex12;
    cin >> i_ex12;

    // Price at m,i
    cout << "The price at m="<<m_ex12<<", i="<<i_ex12<<" is: "<< MyOption1.GetPrice(m_ex12, i_ex12) << ".\n";

    // Replicating strategy stock positions at m,i
    cout << "The stock position at m="<<m_ex12<<", i="<<i_ex12<<" is: "<< MyOption1.GetReplicatingX(m_ex12, i_ex12) << ".\n";

    //  Replicating strategy bond positions at m,i
    cout << "The bond position at m="<<m_ex12<<", i="<<i_ex12<<" is: "<< MyOption1.GetReplicatingY(m_ex12, i_ex12) << ".\n";


    //  entire price tree
    cout << "Find the full price tree below .\n";
    MyOption1.DisplayPriceTree();

    //  entire stock position tree
    cout << "Find the associated tree of stock positions using delta hedging below.\n";
    MyOption1.DisplayStockPositionsTree();


    //  - entire bond position tree
    cout << "Find the associated tree of bond positions (based on the stock positions found using delta) hedging below.\n";
    MyOption1.DisplayBondPositionsTree();




    cout << " --- Input & Output for Ex 1.3 and 1.4 --- \n";

    cout << "Enter the number of options to consider for your strategy :\n";
    int M;
    cin >> M;

    int m,i;
    cout << "Enter node at which to make computations - first m, then i.\n";
    cin >> m;
    cin >> i;

    // Counter variables to save joint stock and bond positions
    double joint_xt = 0;
    double joint_yt=0;

    for (int num_option = 0; num_option<M; num_option++)
    {

        cout << "Fill in input data for option No." << num_option << ".\n";

        //type of option
        string option_type;
        cout << "Enter option type - either 'call' or 'put\n";
        cin >> option_type;

        cout << "Enter steps to expiry N \n";
        cin >> N;

       // safety check on N
        if (N <= m) {
            cout << "m should be smaller than N!\n";
            return 1;
        }

        if (option_type == "call"){
            EurCall MyOption(N);
            MyOption.GetInputData();
            MyOption.OptionPriceTree(MyModel);
            MyOption.ReplicatingStrategyStockPositions(MyModel);
            MyOption.ReplicatingStrategyBondPositions(MyModel);

            //augmenting joint_xt, joint_yt
            //augmenting joint_xt, joint_yt
            joint_xt += MyOption.GetReplicatingX(m,i);
            joint_yt += MyOption.GetReplicatingY(m,i);



            cout << "At Node (m,i)="<<m<<","<<i<<"):\n";
            cout << "Option No " << num_option +1 << " price is "<< MyOption.GetPrice(m,i) << ", replicating strategy: x ="<< MyOption.GetReplicatingX(m,i) <<", y =" << MyOption.GetReplicatingY(m,i) << ".\n";

            }
        else if (option_type == "put"){
            EurPut MyOption(N);
            MyOption.GetInputData();
            MyOption.OptionPriceTree(MyModel);
            MyOption.ReplicatingStrategyStockPositions(MyModel);
            MyOption.ReplicatingStrategyBondPositions(MyModel);

            //augmenting joint_xt, joint_yt
            joint_xt += MyOption.GetReplicatingX(m,i);
            joint_yt += MyOption.GetReplicatingY(m,i);

            cout << "At Node (m,i)="<<m<<","<<i<<"):\n";
            cout << "Option No " << num_option << " Price is " << MyOption.GetPrice(m,i) << ", replicating strategy: x ="<< MyOption.GetReplicatingX(m,i) <<", y =" << MyOption.GetReplicatingY(m,i) << ".\n";

            }


        else {
            cout << "Enter either 'call' or 'put'!\n";
            return 1;
        }
    }

        cout << "Enter your position in stocks X and in the money market account Y at node (m,i)="<<m<<","<<i<<"):\n";
        double X,Y;
        cin >> X;
        cin >> Y;

        double pos_value = X * MyModel.S(m,i) + Y * pow(MyModel.GetR(),m);
        cout << "The value of your position (X,Y) is: " << pos_value << "with stock price ="<< MyModel.S(m,i) << " and bond price = "<< pow(MyModel.GetR(),m) << ".\n";

        double current_replicating_value = joint_xt * MyModel.S(m,i) + joint_yt * pow(MyModel.GetR(),m);
        cout << "For replication of all options you need: " << current_replicating_value << ".\n";

        if (pos_value < current_replicating_value){

            cout << "The balance is "<< pos_value - current_replicating_value << ". You are short of funds!\n";
        }
        else {
            cout << "The balance is "<< pos_value - current_replicating_value << ".\n";


            if (joint_xt > X){
                cout << "You need to buy " << joint_xt - X << " stocks";
            }
            else {
                cout << "You need to sell " << X - joint_xt << " stocks";
            }


            if (joint_yt > Y){
                cout << "And you need to buy " << joint_yt - Y << " bonds";
            }
            else{
                cout << "And you need to sell " << Y - joint_yt << " bonds.\n";
            }



        }



    return 0;
}

