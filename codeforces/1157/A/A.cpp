#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(int x) {
    x++;
    while (x % 10 == 0) x /= 10;
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    set<int> s;
    s.insert(n);
    while (true) {
        n = f(n);
        if (s.count(n)) break;
        s.insert(n);
    }
    cout << s.size() << '\n';

    return 0;
}

