#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100, maxx = 3005;
int n;
struct Card
{
    set<int> row[5];
    bool has[maxx];
    int rowcnt[5];
    int mx;
    Card() {
        memset(has,false,sizeof has);
        memset(rowcnt,0,sizeof rowcnt);
        mx = 0;
    }
    void call(int x) {
        if (!has[x]) return;
        for (int i = 0; i < 5; i++) {
            if (row[i].count(x)) {
                rowcnt[i]++;
                mx = max(mx,rowcnt[i]);
                return;
            }
        }
    }
    void reset() {
        memset(rowcnt,0,sizeof rowcnt);
        mx = 0;
    }
} cards[maxn];

bool check(int i, int j) {
    for (int a = 0; a < 5; a++) {
        for (int b: cards[i].row[a]) {
            if (!cards[j].has[b]) continue;
            int r1 = a;
            int r2;
            for (int q = 0; q < 5; q++) {
                if (cards[j].row[q].count(b)) {
                    r2 = q;
                    break;
                }
            }
            set<int> calls;
            for (int q: cards[i].row[r1]) {
                if (q == b) continue;
                calls.insert(q);
            }
            for (int q: cards[j].row[r2]) {
                if (q == b) continue;
                calls.insert(q);
            }
            for (int q: calls) {
                for (int v = 0; v < n; v++) {
                    cards[v].call(q);
                }
            }
            bool poss = true;
            for (int v = 0; v < n; v++) {
                if (cards[v].mx == 5) {
                    poss = false;
                    break;
                }
            }
            for (int v = 0; v < n; v++) {
                cards[v].reset();
            }
            if (poss) return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < 5; a++) {
            for (int b = 0; b < 5; b++) {
                int ai; cin >> ai;
                cards[i].has[ai] = true;
                cards[i].row[a].insert(ai);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (check(i,j)) {
                cout << i+1 << ' ' << j+1 << '\n';
                return 0;
            }
        }
    }
    cout << "no ties\n";
    return 0;
}

