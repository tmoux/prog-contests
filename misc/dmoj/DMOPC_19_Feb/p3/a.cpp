#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int H, V;

int sqr(int x) {return x*x;}
int dist(pair<int,int> a, pair<int,int> b) {
    return sqr(a.first-b.first)+sqr(a.second-b.second);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> V;
    vector<pair<int,int>> v;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < V; j++) {
            v.push_back({i*4,j*4});
        }
    }
    int ans = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i+1; j < v.size(); j++) {
            for (int k = j+1; k < v.size(); k++) {
                for (int l = k+1; l < v.size(); l++) {
                    auto p1 = v[i];
                    auto p2 = v[j];
                    auto p3 = v[k];
                    auto p4 = v[l];
                    pair<int,int> mid = {
                        (p1.first+p2.first+p3.first+p4.first)/4,
                        (p1.second+p2.second+p3.second+p4.second)/4

                    };
                    if (dist(mid,p1) == dist(mid,p2) && dist(mid,p2) == dist(mid,p3) && dist(mid,p3) == dist(mid,p4)) {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
