#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 20;
int N, M;
int frames[maxn];

int main()
{
    cin >> N >> M;
    vector<pair<int,int>> pictures;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        pictures.push_back({a,b});
    }
    //coordinate compress values
    
    sort(pictures.begin(),pictures.end(),[](auto a, auto b) {
            return a.second < b.second;
            });
    map<int,int> comp;
    int c = 1;
    for (auto& p: pictures) {
        if (comp.count(p.second)) p.second = comp[p.second];
        else p.second = comp[p.second] = c++;
    }
   
    sort(pictures.begin(),pictures.end(),[](auto a, auto b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
            });
    for (int i = 1; i <= M; i++) cin >> frames[i];
    sort(frames+1,frames+M+1);

    int ans = 0;
    for (int mask = 1; mask < (1<<N); mask++) {
        vector<pair<int,int>> vs;
        bool poss = true;
        for (int i = 0; i < N; i++) {
            if (mask & (1<<i)) {
                vs.push_back(pictures[i]);
            }
        }
        if ((int)vs.size() > M) continue;
        int curr = M;
        for (int i = vs.size() - 1; i >= 0; i--) {
            if (vs[i].first > frames[curr]) {
                poss = false;
                break;
            }
            curr--;
        }
        if (poss) {
            ans = min(max(ans,(int)vs.size()),M);
        }
    }
    cout << ans << '\n';
}

