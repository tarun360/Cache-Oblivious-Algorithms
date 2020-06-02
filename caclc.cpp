#include<bits/stdc++.h>
#include<iomanip>
using namespace std;

int main(){
    int n = 10;
    ofstream fout;
    fout.open("calcCacheTranspose.txt");
    vector<double> Ir =  {8929665, 9780181, 13160736, 26656450, 80567560, 296257372, 1158485342, 4606894817, 18399437262, 73567586545};
    vector<double> I1m= {6630, 6669, 6625, 6702, 6716, 6690, 6705, 6669, 6660, 6718};
    vector<double> LLim= {3766, 3750, 3766, 3787, 3796, 3785, 4165, 4117, 4115, 4146};
    vector<double> I1mr;
    vector<double> LLimr;
    cout<<fixed<<setprecision(12);
    fout<<fixed<<setprecision(12);
    for(int i=0; i<10; i++){
        double x = Ir[i], y = I1m[i], z = LLim[i];
        I1mr.push_back((y*100.0)/x);
        LLimr.push_back((z*100.0)/x);
    }
    cout<<"I1 miss rate: ";
    for(int i=0; i<10; i++){
        fout<<I1mr[i]<<" ";
        cout<<I1mr[i]<<", ";
    }
    fout<<endl;
    cout<<endl;
    cout<<"LLi miss rate: ";
    for(int i=0; i<10; i++){
        fout<<LLimr[i]<<" ";
        cout<<LLimr[i]<<", ";
    }
    fout<<endl;
    cout<<endl;

    vector<double> Dr= {3312113, 3716314, 5323713, 11739904, 37370521, 139907887, 549813956, 2189189029, 8746228183, 34973384520};
    vector<double> D1m= {29253, 29556, 31161, 36145, 54723, 134283, 543352, 2083402, 8243540, 32941154};
    vector<double> LLdm= {3766, 11468, 11852, 13380, 19550, 44148, 389307, 1585577, 6304329, 25179325};
    vector<double> D1mr;
    vector<double> LLdmr;
    for(int i=0; i<10; i++){
        double x = Dr[i], y = D1m[i], z = LLdm[i];
        D1mr.push_back((y*100.0)/x);
        LLdmr.push_back((z*100.0)/x);
    }
    cout<<"D1 miss rate: ";
    for(int i=0; i<10; i++){
        fout<<D1mr[i]<<" ";
        cout<<D1mr[i]<<", ";
    }
    fout<<endl;
    cout<<endl;
    cout<<"LLd miss rate: ";
    for(int i=0; i<10; i++){
        fout<<LLdmr[i]<<" ";
        cout<<LLdmr[i]<<", ";
    }
    fout<<endl;
    cout<<endl;

    vector<double> LLr= {35883, 36225, 37786, 42847, 61439, 140973, 550057, 2090071, 8250200, 32947872};
    vector<double> LLm= {15118, 15218, 15618, 17167, 23346, 47933, 393472, 1589694, 6308444, 25183471};
    return 0;
}