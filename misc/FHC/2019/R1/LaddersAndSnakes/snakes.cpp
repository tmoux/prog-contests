#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll maxn = 60;
const ll INF = 987654321; //987 million
ll N, H;

struct Line
{
    ll x, y1, y2, id;
};
vector<Line> lines;

struct FF
{
    ll cap[maxn][maxn];
    bool visited[maxn];
    ll source, sink;
    FF() {
        source = N;
        sink = source + 1;
        //fill with zeros
        memset(cap,0,sizeof(cap));
        memset(visited,false,sizeof(visited));
        //each curr[i] represents covered interval [i,i+1]
        vector<ll> curr(H+1,-1);
        curr[0] = source;
        //cout << N << ' ' << H << '\n';
        //cout << "SZ " << curr.size() << endl;
        curr[H-1] = sink;
        sort(lines.begin(),lines.end(),[](auto a, auto b) {
                return a.x < b.x;
                });
        for (auto l: lines) {
            map<ll,ll> mp;
            for (ll y = l.y1; y < l.y2; y++) {
                if (curr[y] != -1) {
                    ll prev = curr[y];
                    if (y == 0 || y == H-1) {
                        mp[prev] = INF+1;
                    }
                    else {
                        mp[prev]++;
                    }
                }
            }
            for (auto& p: mp) {
                //add the weight, both directions
                cap[l.id][p.first] = p.second;
                cap[p.first][l.id] = p.second;
            }
            for (ll y = l.y1; y < l.y2; y++) {
                curr[y] = l.id;
            }
        }

        /*
        cout << '\n';
        for (ll i = 0; i <= sink; i++) {
            for (ll j = 0; j <= sink; j++) {
                cout << cap[i][j] << ' ';
            }
            cout << '\n';
        }
        */
    }

    ll dfs(ll i, ll bneck) {
        if (i == sink) {
            return bneck;
        }
        if (visited[i]) return 0;
        visited[i] = true;
        for (ll j = 0; j <= sink; j++) {
            if (cap[i][j] > 0) {
                ll f = dfs(j,min(bneck,cap[i][j]));
                if (f > 0) {
                    //update, recurse upwards
                    cap[i][j] -= f;
                    cap[j][i] += f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll getflow() {
        ll flow = 0;
        while (true) {
            memset(visited,false,sizeof(visited));
            ll f = dfs(source,INF);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll T; cin >> T;
    for (ll qq = 1; qq <= T; qq++) {
        if (!lines.empty()) lines.clear();
        cout << "Case #" << qq << ": ";
        cin >> N >> H;
        for (ll i = 0; i < N; i++) {
            Line l;
            cin >> l.x >> l.y1 >> l.y2;
            l.id = i;
            lines.push_back(l);
        }
        //cout << "n = " << N << ", " << "h = " << H << '\n';
        if (H == 1) {
            /*
            cerr << "Hello " << '\n';
            for (auto l: lines) {
                cerr << l.x << ' ' << l.y1 << ' ' << l.y2 << '\n';
            }
            */
            cout << -1 << '\n';
            //always impossible
        }
        else {
            FF g = FF();
            ll ans = g.getflow();
            cout << (ans >= INF ? -1 : ans) << '\n';
        }
    }

}

