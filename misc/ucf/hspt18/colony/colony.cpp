#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int parent[maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}
void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

struct Query {
    int t, c, d;
};

struct Answer {
    int t, c, d;
    bool s;
};

int main()
{
    int m; cin >> m;
    for (int qq = 1; qq <= m; qq++) {
        int n; cin >> n;
        vector<pair<int,int>> edges;
        vector<bool> deleted(n-1,false);
        map<pair<int,int>,int> edgeToIdx;
        for (int i = 0; i < n - 1; i++) {
            int a, b; cin >> a >> b;
            edges.push_back({min(a,b),max(a,b)});
            edgeToIdx[{min(a,b),max(a,b)}] = i;
        }
        int q; cin >> q;
        vector<Query> queries(q);
        for (int i = 0; i < q; i++) {
            int t, c, d; cin >> t >> c >> d;
            queries[i] = {t,c,d};
            if (t == 1) deleted[edgeToIdx[{min(c,d),max(c,d)}]] = true;
        }
        reverse(queries.begin(),queries.end());
        memset(parent,-1,sizeof parent);
        for (int i = 0; i < n - 1; i++) {
            //cout << i << ": " << deleted[i] << '\n';
            if (!deleted[i]) {
                int a = edges[i].first;
                int b = edges[i].second;
                Union(a,b);    
            }
        }
        vector<Answer> answers;
        for (Query& q: queries) {
            /*
            if (q.t == 2 && q.c == 5 && q.d == 3) {
                cout << "SSS:\n";
                for (int i = 1; i <= n; i++) {
                    cout << i << ": " << Find(i) << '\n';
                }
            }
            */
            if (q.t == 1) {
                Union(q.c,q.d);
                answers.push_back({q.t,q.c,q.d,0});
            }
            else {
                bool poss = Find(q.c) == Find(q.d);
                answers.push_back({q.t,q.c,q.d,poss});
            }
        }
        //output
        printf("Colony #%d:\n",qq);
        reverse(answers.begin(),answers.end());
        for (Answer& a: answers) {
            if (a.t == 1) {
                printf("Tunnel from %d to %d collapsed!\n",a.c,a.d);
            }
            else {
                if (a.s) {
                    printf("Room %d can reach %d\n",a.c,a.d);
                }
                else {
                    printf("Room %d cannot reach %d\n",a.c,a.d);
                }
            }
        }
        printf("\n");
    }

    return 0;
}

