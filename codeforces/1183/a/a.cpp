#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int s(int x) {
    int res = 0;
    while (x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int a; cin >> a;
    while (s(a) % 4 != 0) a++;
    cout << a << '\n';

}

