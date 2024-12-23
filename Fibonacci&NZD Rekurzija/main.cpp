#include <iostream>
#include <stdexcept>
#include <memory>
using namespace std;
int fib_petlja (int n) {
if (n<=1) return n; // 0 i 1
int pretprosli(0), prosli(1), rezultat;
for (int i(2); i<=n; i++) {
rezultat = pretprosli+prosli;
pretprosli = prosli;
prosli = rezultat;
}
return rezultat;
}

int fib2_0(int n, int a = 0 , int b=1) {
 if ( n == 0 ) return a;
 else if ( n == 1 ) return b;
 else return fib2_0(n - 1,b,b+a);
}

int nzd(int x, int y){
    if(y==0) return x;
    else return nzd(y,x%y);
}

int main(){
cout << fib2_0(20);
cout << nzd(101,12);
cout << nzd(6, 561);
    return 0;
}