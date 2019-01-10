#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    cout << N << ' ' << 100000 << '\n';
    for (int i = 1; i <= N; i++) {
        int r = rand() % 100001;
        cout << r << ' ';
    }
    cout << '\n';

    return 0;
}

