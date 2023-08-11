#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, S; cin >> n >> S;
    cout << (S % n == 0 ? S/n : S/n+1) << '\n';

    return 0;
}

