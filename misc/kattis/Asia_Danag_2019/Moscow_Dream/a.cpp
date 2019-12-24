#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int a, b, c, n; cin >> a >> b >> c >> n;
    cout << (n>=3&&a+b+c>=n&&min(a,min(b,c))>0?"YES":"NO") << endl;
}
