#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 500005;
int N, Q;
int C[maxn];
set<int> keys[maxn];
int furthest[maxn]; //furthest right index just by going right

struct Query {
    int st, en, id;
};
vector<Query> queries[maxn]; //queries that start at queries[i]

void expand(int &li, int &ri, set<int> &se) {
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

void rexpand(int &ri, set<int> &se) {
    while (true) {
        if (ri < N && se.count(C[ri])) {
            ++ri;
            for (int a: keys[ri]) se.insert(a);
        }
        else break;
    }
}

int li[maxn], ri[maxn];
set<int> *currkeys[maxn], *precalc[maxn];

vector<int> pos[maxn]; //list of posititions for keys

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
            pos[key].push_back(i);
        }
    }
    //precalc
    for (int i = N; i >= 1; i--) {
        if (keys[i].count(C[i])) {
            precalc[i] = precalc[i+1];
            for (int a: keys[i]) precalc[i]->insert(a);
            furthest[i] = furthest[i+1];
            rexpand(furthest[i],*precalc[i]);
        }
        else {
            precalc[i] = new set<int>;
            for (int a: keys[i]) precalc[i]->insert(a);
            furthest[i] = i;
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
        queries[x].push_back({x,y,i});        
    }
    vector<string> ans(Q);
    for (int i = 1; i <= N; i++) {
        li[i] = ri[i] = i;
        if (keys[i].count(C[i-1])) {
            if (ri[i-1] >= i) {
                //same
                li[i] = li[i-1];
                ri[i] = ri[i-1];
                currkeys[i] = currkeys[i-1];
                //copy the pointer over
            }
            else {
                li[i] = li[i-1];
                currkeys[i] = currkeys[i-1];
                for (int a: keys[i]) currkeys[i]->insert(a);
                expand(li[i],ri[i],*currkeys[i]);        
            }
        }
        else {
            /*
            currkeys[i] = new set<int>;
            for (int a: keys[i]) currkeys[i]->insert(a);
            expand(li[i],ri[i],*currkeys[i]);
            */
            ri[i] = furthest[i];
            auto it = lower_bound(pos[C[i-1]].begin(),pos[C[i-1]].end(),i);
            if (it != pos[C[i-1]].end() && *it <= ri[i]) {
                li[i] = min(li[i],li[i-1]);
                ri[i] = max(ri[i],ri[i-1]);
                currkeys[i] = currkeys[i-1];
                for (int j = i; j <= ri[i]; j++) {
                    for (int a: keys[j]) currkeys[i]->insert(a);
                }
                expand(li[i],ri[i],*currkeys[i]);
            }
            else {
                currkeys[i] = new set<int>;
                for (int j = i; j <= ri[i]; j++) {
                    for (int a: keys[j]) currkeys[i]->insert(a);
                }
                //expand(li[i],ri[i],*currkeys[i]);
            }
        }
        for (Query q: queries[i]) {
            ans[q.id] = (li[i] <= q.en && q.en <= ri[i]) ? "YES" : "NO"; 
        }
    }
    //output
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

