#include<bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("inputMatrixTranspose.txt");
    fout.open("outputMatrixTranspose.txt");
    int n, m;
    fin>>n>>m;
    vector<vector<int>> A(n, vector<int>(m)), B(m, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            fin>>A[i][j];
        }
    }
    clock_t time_req;
    time_req = clock();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            B[j][i] = A[i][j];
        }
    }
    fout<<m<<" "<<n<<endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            fout<<B[i][j]<<" ";
        }
        fout<<endl;
    }
    cout<<"Dimension: "<<n<<" "<<m<<endl;
    cout<<"Time taken: "<<(float)time_req/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}