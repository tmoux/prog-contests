#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cnt[3];
int check[3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;
    for (char c: s) {
    	cnt[c-'0']++;
    }
    cnt[0] -= a;
    cnt[1] -= b;
    cnt[2] -= n - a - b;
    vector<int> out;
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
    	int f = s[i]-'0';
    	if (cnt[f] <= 0) out.push_back(f);
    	else {
    		for (int j = 0; j < 3; j++) {
    			if (j != f && cnt[j] < 0) {
    				cnt[f]--;
    				cnt[j]++;
    				out.push_back(j);
    				res++;
    				break;
    			}
    		}
    	}
    	check[out.back()]++;
    }
    if (check[0] != a || check[1] != b || check[2] != n-a-b) {
    	cout << -1 << '\n';
    	return 0;
    }

    cout << res << '\n';
    for (int i: out) cout << i;
    cout << '\n';



    return 0;
}