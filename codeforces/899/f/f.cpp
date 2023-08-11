#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
int n, m;
string s;
const int blk = 450;
const int sz = maxn/blk + 5;

int bucket[maxn];
int d[maxn];
int a[maxn], cnt[62][sz], sum[sz];
int start[sz];

int ctoi(char c) {
    if ('a' <= c && c <= 'z') return c-'a';
    if ('A' <= c && c <= 'Z') return c-'A'+26;
    if ('0' <= c && c <= '9') return c-'0'+52;
}

int trav(int i) {
    int res = 0;
    int b = 0;
    while (res + sum[b] < i) {
        res += sum[b];
        b++;
    }
    int s = start[b];
    while (res < i) {
        if (cnt[d[s]][b] > 0 && a[s] == 1) res++;
        if (res == i) break;
        s++;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    cin >> s;
    //sqrt
    for (int i = 0; i < n; i++) {
        bucket[i] = i/blk;
        a[i] = 1;
        d[i] = ctoi(s[i]);
        cnt[d[i]][bucket[i]]++;
        sum[bucket[i]]++;
        if (i == 0 || bucket[i] != bucket[i-1]) {
            start[bucket[i]] = i;
        }
    }
    while (m--) {
        int l, r; cin >> l >> r;
        char c; cin >> c;
        int dd = ctoi(c);
        int ll = trav(l), rr = trav(r);
        while (ll != 0 && bucket[ll] == bucket[ll-1] && ll <=  rr) {
            if (d[ll] == dd && cnt[d[ll]][bucket[ll]] > 0 && a[ll] == 1) {
                a[ll] = 0;
                cnt[d[ll]][bucket[ll]]--;
                sum[bucket[ll]]--;
            }
            ll++;
        }
        while (bucket[ll] < bucket[rr] && ll <= rr) {
            sum[bucket[ll]] -= cnt[dd][bucket[ll]];
            cnt[dd][bucket[ll]] = 0;
            ll += blk;
        }
        while (ll <= rr) {
            if (d[ll] == dd && cnt[d[ll]][bucket[ll]] > 0 && a[ll] == 1) {
                a[ll] = 0;
                cnt[d[ll]][bucket[ll]]--;
                sum[bucket[ll]]--;
            }
            ll++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == 1 && cnt[d[i]][bucket[i]] > 0) {
            cout << s[i];
        }
    }
    cout << '\n';
}
