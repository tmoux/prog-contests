#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];

int candidates[maxn]; //# of candidates

int askd(int u) {
    cout << "d " << u << endl;
    int r; cin >> r;
    return r;
}
int asks(int u) {
    cout << "s " << u << endl;
    int r; cin >> r;
    return r;
}

vector<int> poss;
vector<int> childs[maxn];
void fillCandidate(int i, int d, int target) {
    candidates[i] = 0;
    if (d == target) {
        candidates[i] = 1;
        poss.push_back(i);
    }
    else {
        for (int j: childs[i]) {
            fillCandidate(j,d+1,target);
            candidates[i] += candidates[j];
        }
    }
}


void root(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        childs[i].push_back(j);
        root(j,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    root(1,1);
    int curr = 1;
    int d = -1;
    while (true) {
        if (curr == 1) d = askd(curr);
        //cout << "curr = " << curr << ", " << "d = " << d << endl;
        poss.clear();
        fillCandidate(curr,0,d);
        int total = candidates[curr];
        /*
        cout << "total = " << total << endl;
        for (int i: poss) {
            cout << i << ": " << endl;
        }
        */
        if (total == 1) {
            cout << "! " << poss[0] << endl;
            exit(0);
        }
        vector<pair<int,int>> cls;
        for (int j: childs[curr]) {
            if (candidates[j] > 0) cls.push_back({candidates[j],j});
        }
        while (cls.size() == 1) {
            curr = cls[0].second;
            d--;
            cls.clear();
            for (int j: childs[curr]) {
                if (candidates[j] > 0) cls.push_back({candidates[j],j});
            }    
        }
        assert(!cls.empty());
        sort(cls.begin(),cls.end());
        if (cls[0].first*2 > total) {
            int test = cls[0].second;
            int d2 = askd(test);
            if (d2 == d - 1) {
                curr = test;
            }
            else {
                curr = asks(curr);
            }
            d--;
        }
        else {
            curr = asks(curr);
            d--;
        }

        if (candidates[curr] == 1) {
            poss.clear();
            fillCandidate(curr,0,d);
            cout << "! " << poss[0] << endl;
            exit(0);
        }
    }
}

