#include<bits/stdc++.h>
#include<ctime>
using namespace std;

int dim;
vector<vector<int>> A, B, C;

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("inputMatrixMultiplication.txt");
    fout.open("outputMatrixMultiplication.txt");
    fin>>dim;
    A.resize(dim, vector<int>(dim, 0));
    B.resize(dim, vector<int>(dim, 0));
    C.resize(dim, vector<int>(dim, 0));
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            fin>>A[i][j];
        }
    }
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            fin>>B[i][j];
        }
    }
    clock_t time_req;
    time_req = clock();
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            for(int k=0; k<dim; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    time_req = clock()-time_req;
    cout<<"Dimension: "<<dim<<endl;
    cout<<"Time taken: "<<(float)time_req/CLOCKS_PER_SEC<<"s"<<endl;
    fout<<dim<<endl;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            fout<<C[i][j]<<" ";
        }
        fout<<endl;
    }
    fout<<endl;
    return 0;
}