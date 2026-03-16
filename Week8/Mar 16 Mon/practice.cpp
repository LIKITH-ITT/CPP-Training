#include <iostream>
using namespace std;

template <class T>
T GetMax (T a, T b) {
  T result;
  result = (a>b)? a : b;
  return (result);
}

template <class T, class U>
U GetMin (T a, U b) {
  return (a<b?a:b);
}

int main () {
  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax(i,j);
  cout << k << endl;
  cout << GetMax<double>(5,5.5) << endl;

  int x,y=6;
  double q=2.6;
  x = GetMin<int,double> (y,q);
    cout << x << endl;

  return 0;
}