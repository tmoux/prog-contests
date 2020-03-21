#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[] = { 1, 1, 1, 2, 1, 2, 1, 5, 2, 2, 1, 5, 1, 2, 1, 14, 1, 5, 1, 5, 2, 2, 1, 15, 2, 2, 5, 4, 1, 4, 1, 51 };

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k; cin >> k;
    cout << a[k-1] << endl;
}

