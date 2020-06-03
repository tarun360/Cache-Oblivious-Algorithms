//Only for square matrices
//Of dimensions of power of 3
#include<bits/stdc++.h>
#include<ctime>
using namespace std;

int dim;
int a = 0, b = 0, c = 0;
vector<int> A, B, C;

void peanomult(int phsA, int phsB, int phsC, int dim){
    if(dim == 1){
        C[c] += A[a]*B[b];
    }
    else{
        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA, -phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; b += phsB;

        peanomult( phsA,  phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult( phsA, -phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult( phsA,  phsB, -phsC, dim/3); a += phsA; b += phsB;

        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA, -phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA,  phsB,  phsC, dim/3); b += phsB; c += phsC;

        peanomult(-phsA,  phsB,  phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, -phsB,  phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA,  phsB,  phsC, dim/3); a -= phsA; b += phsB;

        peanomult(-phsA,  phsB, -phsC, dim/3); a -= phsA; c -= phsC;
        peanomult(-phsA, -phsB, -phsC, dim/3); a -= phsA; c -= phsC;
        peanomult(-phsA,  phsB, -phsC, dim/3); a -= phsA; b += phsB;

        peanomult(-phsA,  phsB,  phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA, -phsB,  phsC, dim/3); a -= phsA; c += phsC;
        peanomult(-phsA,  phsB,  phsC, dim/3); b += phsB; c += phsC;

        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA, -phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; b += phsB;

        peanomult( phsA,  phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult( phsA, -phsB, -phsC, dim/3); a += phsA; c -= phsC;
        peanomult( phsA,  phsB, -phsC, dim/3); a += phsA; b += phsB;

        peanomult( phsA,  phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA, -phsB,  phsC, dim/3); a += phsA; c += phsC;
        peanomult( phsA,  phsB,  phsC, dim/3);
    }
}

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    fin>>dim;
    A.resize(dim*dim, 0);
    B.resize(dim*dim, 0);
    C.resize(dim*dim, 0);
    for(int i=0; i<dim*dim; i++){
        fin>>A[i];
    }
    for(int i=0; i<dim*dim; i++){
        fin>>B[i];
    }
    cout<<"Dimension: "<<dim<<endl;
    clock_t time_req;
    time_req = clock();
    peanomult(1, 1, 1, dim);
    time_req = clock()-time_req;
    cout<<"Time taken: "<<(float)time_req/CLOCKS_PER_SEC<<"s"<<endl;
    fout<<C.size()<<endl;
    for(int i=0; i<C.size(); i++){
        fout<<C[i]<<" ";
    }
    fout<<endl;
    return 0;
}