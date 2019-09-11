#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 20;
int N, S[1<<maxn];
map<int,int> cnt;
int gen[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    multiset<int> ms;
    int mx = 0;
    for (int i = 0; i < (1<<N); i++) {
        cin >> S[i];
        cnt[S[i]]++;
        mx = max(mx,S[i]);
        ms.insert(S[i]);
    }
    priority_queue<pair<int,int>> pq;        
    pq.push({N,mx});
    auto it = ms.find(mx);
    ms.erase(it);
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        //cout << p.first << ' ' << p.second << '\n';
        if (p.first == 0) continue;
        pq.push({p.first-1,p.second});
        assert(p.first >= 1);
        auto it = ms.lower_bound(p.second);
        if (it != ms.begin()) {
            --it;
            assert(*it < p.second);
            pq.push({p.first-1,*it});
            ms.erase(it);
        }
        else {
            cout << "No\n";
            return 0;
        }
    }
    assert(ms.empty());
    cout << "Yes\n";
}

