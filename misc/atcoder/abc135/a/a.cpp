#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int A, B; cin >> A >> B;
    if (A > B) swap(A,B);
    if ((abs(B-A) % 2) == 0) {
        cout << (A + (B-A)/2) << '\n';
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
}

