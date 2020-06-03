#include<bits/stdc++.h>
using namespace std;

//matrix is the original matrix in row major order
//matrixT is the transposition of matrix which we want to obtain. Also in row major order
//x and y is the index of element(when matrix is not written in row major order)
//which we want to transpose such that A[x][y](in matrix) = AT[y][x](in matrixT)
//delx and dely are X and Y dimensions of sub matrix in consideration
//N and M are X and Y dimensions of "matrix"

//now point A[x][y] = matrix[(N*y) + x] and point AT[y][x] = matrixT[(M*x) + y]

//In this method "Transposition", we are dividing matrix into submatrices
//till we get a submatrix with only single element A[x][y]
//then we are putting that element at AT[y][x]
void Transposition(int x, int delx, int y, int dely, int N, int M, vector<int> &matrix, vector<int> &matrixT) {
    if ((delx == 1) && (dely == 1)) {
        matrixT[(M*x) + y] = matrix[(N*y) + x];
        return;
    }

    if (delx >= dely) {
        int xmid = delx / 2;
        Transposition(x, xmid, y, dely, N, M, matrix, matrixT);
        Transposition(x + xmid, delx - xmid, y, dely, N, M, matrix, matrixT);
        return;
    }

    int ymid = dely / 2;
    Transposition(x, delx, y, ymid, N, M, matrix, matrixT);
    Transposition(x, delx, y + ymid, dely - ymid, N, M, matrix, matrixT);
}

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("inputMatTrans.txt");
    fout.open("outputMatTrans.txt");
    int n, m;
    fin>>n>>m;
    vector<int> matrix(n*m, 0), matrixT(n*m, 0);
    for(int i=0; i<n*m; i++) fin>>matrix[i];
    clock_t time_req;
    time_req = clock();
    Transposition(0, n, 0, m, n, m, matrix, matrixT);
    cout<<"Dimension: "<<n<<" "<<m<<endl;
    cout<<"Time taken: "<<(float)time_req/CLOCKS_PER_SEC<<"s"<<endl;
    fout<<m<<" "<<n<<endl<<endl;
    for(int i=0; i<n*m; i++){
        fout<<matrixT[i]<<" ";
        if(i%m == m-1){
            fout<<endl;
        }        
    }
    return 0;
}