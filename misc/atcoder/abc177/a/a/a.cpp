#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int D, T, S; cin >> D >> T >> S;
    cout << (S*T >= D ? "Yes": "No") << '\n';
}
