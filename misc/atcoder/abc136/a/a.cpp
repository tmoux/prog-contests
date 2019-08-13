#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int A, B, C; cin >> A >> B >> C;
    int diff = A-B;
    cout << (max(0,C-diff)) << '\n';
}

