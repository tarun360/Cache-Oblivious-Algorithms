#include <bits/stdc++.h>
using namespace std;

int main(){
  int a=5;
  int *ptr=&a;
  cout<<ptr<<endl;
  cout<<&(*ptr)<<endl;
  return 0;
}
