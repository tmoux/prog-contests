#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    uniform_int_distribution<int> dist(1,7);
    int n; cin >> n;
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << dist(gen) << ' ';
    }
    cout << '\n';
}

