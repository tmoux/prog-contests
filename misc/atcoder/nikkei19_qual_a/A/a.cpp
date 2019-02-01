#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, A, B; cin >> N >> A >> B;
    int mn = min(A,B);
    int mx = max(0,A+B-N);
    cout << mn << ' ' << mx << '\n';


    return 0;
}