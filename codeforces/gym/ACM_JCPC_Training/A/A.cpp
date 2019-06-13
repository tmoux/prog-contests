#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, K; cin >> N >> K;
    int r = (N % K);
    int num = 0;
    if (r > 0) num++;
    N -= r;
    num += N/K;
    cout << num << ' ' << (r == 0 ? K : r) << '\n';

    return 0;
}

