#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
vector<int> cand[maxn], repl[maxn];
int n, m;

int getsmall(int pos) {
    int ret = pos;
    int dist = 0;
    for (int i: repl[pos]) {
        int d = i > pos ? i-pos : n - (pos-i);
        if (d > dist) {
            dist = d;
            ret = i;
        }
    }
    for (int i = 0; i < repl[pos].size(); i++) {
        if (repl[pos][i] == ret) {
            repl[pos].erase(repl[pos].begin()+i);
            break;
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    //just simulate it lol
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int ai, bi; cin >> ai >> bi;
        cand[ai].push_back(bi);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) repl[j] = cand[j];
        //start at i
        set<int> curr;
        int pos = i;
        int amt = 0;
        int sec = 0;
        while (amt < m || curr.size() > 0) {
            if (curr.count(pos)) curr.erase(pos);
            if (repl[pos].size() > 0) {
                curr.insert(getsmall(pos));
                amt++;
            }
            /*
            cout << pos << '\n';
            for (int a: curr) {
                cout << a << ' ';
            }
            cout << '\n';
            */
            if (pos == n) pos = 1;
            else pos++;
            sec++;
        }
        cout << sec-1 << '\n';
    }
}

