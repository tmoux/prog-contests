#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M, A[maxn], B[maxn];
vector<int> times[maxn];

int main()
{
	cin >> N >> M;
	multiset<int> curr;
	for (int i = 1; i <= N; i++) {
		cin >> A[i] >> B[i];
        if (A[i] <= M) times[A[i]].push_back(B[i]);
	}
    ll ans = 0;
    for (int i = 1; i <= M; i++) {
        for (int j: times[i]) {
            curr.insert(j);
        }
        if (!curr.empty()) {
            ans += *curr.rbegin();
            curr.erase(prev(curr.end()));
        }
    }
    cout << ans << '\n';
}
