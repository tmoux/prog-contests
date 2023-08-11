#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
const int maxn = 1e6+6;
int dist[maxn];

int tleft[maxn], tright[maxn];

bool isBad(int i) {
    assert(i != 0);
    return (tleft[i] != 0 && s[i] != s[tleft[i]]) ||
           (tright[i] != 0 && s[i] != s[tright[i]]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    int n = s.size();
    s = '#' + s; //1-indexed
    vector<int> bad;
    for (int i = 1; i <= n-1; i++) {
        tright[i] = i+1;
    }
    for (int i = 2; i <= n; i++) {
        tleft[i] = i-1;
    }
    for (int i = 1; i <= n; i++) {
        if (isBad(i)) {
            bad.push_back(i);
        }
    }
    int cnt = 1;
    while (!bad.empty()) {
        vector<int> newbad;
        for (int i: bad) {
            if (dist[i] != 0) continue;
            //cout << cnt << ": " << i << endl;
            dist[i] = cnt;
            tright[tleft[i]] = tright[i];
            tleft[tright[i]] = tleft[i];
            if (tleft[i] != 0 && dist[tleft[i]] == 0) {
                newbad.push_back(tleft[i]);
            }
            if (tright[i] != 0 && dist[tright[i]] == 0) {
                newbad.push_back(tright[i]);
            }
        }
        bad.clear();
        for (int i: newbad) {
            if (dist[i] == 0 && isBad(i)) bad.push_back(i);
        }
        cnt++;
    }
    cout << (cnt-1) << '\n';
}

