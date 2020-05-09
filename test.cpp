#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<int> a(5,0);
  cout<<&a[0]<<endl;
  cout<<a.data()<<endl;
  return 0;
}
