#ifndef BinLattice_h
#define BinLattice_h
#include <iostream>
#include <iomanip>
using namespace std;
class BinLattice
{
private:
    int N;
    double* Lattice;
public:
public:
    BinLattice(int N_)
    {
        N=N_;
        Lattice=new double[(N+1)*(N+2)/2];
    }
    virtual ~BinLattice()
    {
        delete[] Lattice;
    }
    void SetNode(int n, int i, double x) const
    {
        Lattice[i+n*(n+1)/2]=x;
    }
    double GetNode(int n, int i) const
    {
        return Lattice[i+n*(n+1)/2];
    }
    void Display() const
    {
        cout << setiosflags(ios::fixed) << setprecision(3);
        for(int n=0; n<=N; n++)
        {
            for(int i=0; i<=n; i++)
                cout << setw(7) << GetNode(n,i);
            cout << endl;
        }
        return;
    }
};
#endif
