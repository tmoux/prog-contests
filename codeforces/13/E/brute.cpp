#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m, pwr[maxn], nxt[maxn], cnt[maxn], bucket[maxn], block;

pair<int,int> query(int a) {
    int res = 0;
    int prev = a;
    while (a <= n) {
        res++;
        prev = a;
        a += pwr[a];
    }
    return {prev,res};
}

void update(int a, int b) { //change power of a to b
    pwr[a] = b;
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
    int counter = 0;
    while (m--) {
        int t; cin >> t;
        if (t == 0) {
            int a, b; cin >> a >> b;
            update(a,b);
        }
        else {
            counter++;
            int a; cin >> a;
            pair<int,int> ans = query(a);
            //cout << ans.first << ' ' << ans.second << '\n';
            if (counter == 15) {
                for (int i = 1; i <= n; i++) {
                    cout << pwr[i] << ' ';
                }
                cout << '\n';
                cout << "query: " << a << '\n'; 
            }
        }
    }
    return 0;
}

