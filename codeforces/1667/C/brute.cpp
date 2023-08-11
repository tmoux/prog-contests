#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    cout << n/3+(n+2)/3 << "\n";
    if (n==1) {
        cout << 1 << " " << 1 << "\n";
        return 0;
    }
    while (n%3!=2) {
        cout << n << " " << n << "\n";
        n--;
    }
    int a=(n+1)/3;
    for (int i=1; i<=a; i++) {
        cout << i << " " << a+1-i << "\n";
    }
    for (int i=1; i<a; i++) {
        cout << n-a+i+1 << " " << n-i+1 << "\n";
    }
    return 0;
}
