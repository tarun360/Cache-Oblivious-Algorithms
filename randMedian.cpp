#include<bits/stdc++.h>
using namespace std;

int main(){
    ofstream fout;
    fout.open("inputMedian.txt");
    int n = 1024;
    fout<<n<<endl;
    for(int i=0; i<n; i++){
        int x = rand();
        fout<<x<<" ";
    }
    fout<<endl;
    return 0;
}