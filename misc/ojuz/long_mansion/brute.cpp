#include <bits/stdc++.h>
using namespace std;
using ll = long long;


const int maxn = 5005;
int N, Q;
int C[maxn];
set<int> keys[maxn];

struct Query {
    int st, en, id;
};
vector<Query> queries[maxn]; //queries that start at queries[i]

void expand(int &li, int &ri, set<int> se) {
    while (true) {
        if (li > 1 && se.count(C[li-1])) {
            --li;
            for (int a: keys[li]) se.insert(a);
        }
        else if (ri < N && se.count(C[ri])) {
            ++ri;
            for (int a: keys[ri]) se.insert(a);
        }
        else break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N - 1; i++) {
        cin >> C[i];
    }
    for (int i = 1; i <= N; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int key; cin >> key;
            keys[i].insert(key);
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
        queries[x].push_back({x,y,i});        
    }
    vector<string> ans(Q);
    for (int i = 1; i <= N; i++) {
        int l = i, r = i;
        expand(l,r,keys[i]);    
        for (Query q: queries[i]) {
            ans[q.id] = (l <= q.en && q.en <= r) ? "YES" : "NO"; 
        }
    }
    //output
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

