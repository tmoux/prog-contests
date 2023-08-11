#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m, pwr[maxn], nxt[maxn], cnt[maxn], bucket[maxn], block;

pair<int,int> query(int a) {
    int res = 0;
    int prev = a;
    while (a <= n) {
        if (nxt[a] > n) {
            while (a <= n) {
                prev = a;
                a += pwr[a];
                res++;
            }
            break;
        }
        res += cnt[a];
        prev = a;
        a = nxt[a];
    }
    return {prev,res};
}

void u(int a) {
    int nx = a + pwr[a];
    if (nx > n) {
        nxt[a] = nx;
        cnt[a] = 1;
    }
    else if (bucket[nx] != bucket[a]) {
        nxt[a] = nx;
        cnt[a] = 1;
    }
    else {
        //in the same bucket
        nxt[a] = nxt[nx];
        cnt[a] = cnt[nx] + 1;
    }
    /*
    cnt[a] = 0;
    int curr = a;
    while (curr <= n && bucket[curr] == bucket[a]) {
        curr += pwr[curr];
        cnt[a]++;
    }
    nxt[a] = curr;
    */
}

void update(int a, int b) { //change power of a to b
    pwr[a] = b;
    for (int i = a; i >= 1 && bucket[i] == bucket[a]; i--) {
    //for (int i = 1; i <= n; i++) {
        u(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> pwr[i];
    //sqrt decomp
    block = (int)(sqrt(n) + 1);
    for (int i = 1; i <= n; i++) bucket[i] = (i-1)/block;
    for (int i = 1; i <= n; i++) { //calc nxt and count
        int curr = i;
        while (curr <= n && bucket[curr] == bucket[i]) {
            curr += pwr[curr];
            cnt[i]++;
        }
        nxt[i] = curr;
    }
    /*
    cout << "block size: " << block << '\n';
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << nxt[i] << ' ' << cnt[i] << '\n';
    }
    */
    while (m--) {
        int t; cin >> t;
        if (t == 0) {
            int a, b; cin >> a >> b;
            update(a,b);
        }
        else {
            int a; cin >> a;
            pair<int,int> ans = query(a);
            cout << ans.first << ' ' << ans.second << '\n';
        }
    }
    return 0;
}

