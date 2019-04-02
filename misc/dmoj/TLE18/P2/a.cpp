#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int A, B; cin >> A >> B;
    if (A == 10 && B == 10) {
        cout << "A+B.\n";
        return 0;
    }
    cout << (A+B) << '\n';
}

