#include<bits/stdc++.h>
using namespace std;

#define pb push_back

void Peano(vector<vector<int>> &Mat, vector<int> &d, int dim, char type){
    if(dim == 1){
        d.push_back(Mat[0][0]);
    }
    else{
        vector<vector<vector<int>>> B(9, vector<vector<int>>(dim/3, vector<int>(dim/3, 0)));
        for(int i=0; i<dim; i++){
            for(int j=0; j<dim; j++){
                int p = (dim/3);
                int t = 3*(i/p) + (j/p);
                int x = i%p, y = j%p;
                B[t][x][y] = Mat[i][j]; 
            }
        }
        if(type == 'P'){
            Peano(B[0], d, dim/3, 'P');
            Peano(B[3], d, dim/3, 'Q');
            Peano(B[6], d, dim/3, 'P');
            Peano(B[7], d, dim/3, 'R');
            Peano(B[4], d, dim/3, 'S');
            Peano(B[1], d, dim/3, 'R');
            Peano(B[2], d, dim/3, 'P');
            Peano(B[5], d, dim/3, 'Q');
            Peano(B[8], d, dim/3, 'P');
        }
        else if(type == 'Q'){
            Peano(B[2], d, dim/3, 'Q');
            Peano(B[5], d, dim/3, 'P');
            Peano(B[8], d, dim/3, 'Q');
            Peano(B[7], d, dim/3, 'S');
            Peano(B[4], d, dim/3, 'R');
            Peano(B[1], d, dim/3, 'S');
            Peano(B[0], d, dim/3, 'Q');
            Peano(B[3], d, dim/3, 'P');
            Peano(B[6], d, dim/3, 'Q');
        }
        else if(type == 'R'){
            Peano(B[6], d, dim/3, 'R');
            Peano(B[3], d, dim/3, 'S');
            Peano(B[0], d, dim/3, 'R');
            Peano(B[1], d, dim/3, 'P');
            Peano(B[4], d, dim/3, 'Q');
            Peano(B[7], d, dim/3, 'P');
            Peano(B[8], d, dim/3, 'R');
            Peano(B[5], d, dim/3, 'S');
            Peano(B[2], d, dim/3, 'R');
        }
        else{
            Peano(B[8], d, dim/3, 'S');
            Peano(B[5], d, dim/3, 'R');
            Peano(B[2], d, dim/3, 'S');
            Peano(B[1], d, dim/3, 'Q');
            Peano(B[4], d, dim/3, 'P');
            Peano(B[7], d, dim/3, 'Q');
            Peano(B[6], d, dim/3, 'S');
            Peano(B[3], d, dim/3, 'R');
            Peano(B[0], d, dim/3, 'S');
        }
    }
}

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("Rawinput.txt");
    fout.open("input.txt");
    int dim;
    fin>>dim;
    vector<vector<int> > Mat1(dim, vector<int>(dim)), Mat2(dim, vector<int>(dim));
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            fin>>Mat1[i][j];
        }
    }
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            fin>>Mat2[i][j];
        }
    }
    vector<int> Peano1, Peano2;
    Peano(Mat1, Peano1, dim, 'P');
    Peano(Mat2, Peano2, dim, 'P');
    fout<<dim<<endl;
    for(int i=0; i<Peano1.size(); i++){
        fout<<Peano1[i]<<" ";
    }
    fout<<endl;
    for(int i=0; i<Peano2.size(); i++){
        fout<<Peano2[i]<<" ";
    }
    return 0;
}

/*
3
0 1 2
3 4 5
6 7 8
*/