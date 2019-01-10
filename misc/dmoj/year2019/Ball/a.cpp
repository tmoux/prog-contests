#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    vector<pair<int,int>> a(N+1);
    bitset<5> b;
    for (int i = 1; i <= N; i++) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < 25; i++) {
    	int curr = 1;
    	while (curr != N + 1) {
    		b.flip(curr);
    		curr = b[curr] ? a[curr].first : a[curr].second;
    	}
    	cout << i << ": " << b.to_string() << '\n';
    }

    return 0;
}