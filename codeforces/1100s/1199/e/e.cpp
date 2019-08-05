#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m;
vector<int> adj[maxn];
bool seen[500005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    random_device rd;
    mt19937 g(rd());
    while (T--) {
        cin >> n >> m;
        vector<int> v;
        vector<pair<pair<int,int>,int>> edges;
        for (int i = 1; i <= 3*n; i++) {
            adj[i].clear();
            v.push_back(i);
        }
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
            edges.push_back({{a,b},i+1});
        }
        //try to find max independent set
        bool found = false;
        for (int qq = 0; qq < 90; qq++) {
            shuffle(v.begin(),v.end(),g);
            vector<int> ans;
            for (int i: v) seen[i] = false;
            for (int i: v) {
                //cout << i << ' ';
                if (seen[i]) continue;
                ans.push_back(i);
                seen[i] = true;
                for (int j: adj[i]) seen[j] = true;
                if (ans.size() == n) {
                    found = true;
                    cout << "IndSet" << '\n';
                    for (int i: ans) {
                        cout << i << ' ';
                    }
                    cout << '\n';
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            //try to find matching of size n
            if (m >= n) {
                for (int qq = 0; qq < 90; qq++) {
                    shuffle(edges.begin(),edges.end(),g);
                    vector<int> ans;
                    for (int i = 1; i <= 3*n; i++) {
                        seen[i] = false;
                    }
                    for (auto& p: edges) {
                        if (seen[p.first.first] || seen[p.first.second]) continue;
                        seen[p.first.first] = true;
                        seen[p.first.second] = true;
                        ans.push_back(p.second);    

                        if (ans.size() == n) {
                            found = true;
                            cout << "Matching\n";
                            for (int i: ans) {
                                cout << i << ' ';
                            }
                            cout << '\n';
                            break;
                        }
                    }
                    if (found) break;
                }
            }
            if (!found) {
                cout << "Impossible\n";
            }
        }
    }
}

