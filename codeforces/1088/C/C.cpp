#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int n, a[maxn];

void op1(int i, int x) {
    for (int j = 0; j <= i; j++) a[j] += x;
}
void op2(int i, int x) {
    for (int j = 0; j <= i; j++) a[j] %= x;
}

void print() {
    cout << "Arr: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';    
    }
    cout << '\n';
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    printf("%d\n",n+1);
    for (int i = n-1; i >= 0; i--) {
        int diff = (i - (a[i]%n) + n) % n;
        printf("%d %d %d\n",1,i+1,diff);
        op1(i,diff);
        //print();
    }
    printf("%d %d %d\n",2,n,n);
    return 0;
    op2(n-1,n);
    cout << "Arr\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';

    return 0;
}
