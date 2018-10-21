#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e4+5;
int n, A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        set<int> s;
        for (int j = l; j <= r; j++) s.insert(A[j]);
        cout << s.size() << '\n';
    }

    return 0;
}
	

