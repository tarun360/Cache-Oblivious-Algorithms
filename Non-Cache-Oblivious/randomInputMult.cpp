#include<bits/stdc++.h>
using namespace std;

int main(){
    int dim = 27;
    ofstream fout;
    fout.open("inputMatrixMultiplication.txt");
    fout<<dim<<endl<<endl;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            int x = rand()%2;
            fout<<x<<" ";
        }
        fout<<endl;
    }
    fout<<endl;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            int x = rand()%2;
            fout<<x<<" ";
        }
        fout<<endl;
    }
    return 0;
}