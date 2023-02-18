#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

const int maxn = 45;

int N, M;
ll A[maxn], B[maxn];

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
    ll ans = 0;
	for (int i = 0; i < (1<<N); i++) {
        ll total = 0;
        for (int j = 0; j < N; j++) {
            if (i & (1<<j)) total += A[j];
        }
        if (total <= M) ans++;
    }
    cout << ans << '\n';
}
