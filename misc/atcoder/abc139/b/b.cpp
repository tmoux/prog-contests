#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ceil(int a, int b) {
    return (a % b == 0  ? a/b : a/b+1);    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int A, B; cin >> A >> B;
    //1, 4, 7, 10
    int ans = ceil((B-1),(A-1));
    cout << ans << '\n';

}

