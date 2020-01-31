#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, P;
string S;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> N >> P >> S;
        int numb = 0;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            char c = S[i];
            if (c == 'b') {
                numb++;
                v.push_back(i);
            }
        }
        vector<int> cnt(n,0);
        for (int i = n-1; i >= 0; i--) {
            if (S[i] == 'a') cnt[i]++;
            if (i < n-1) cnt[i] += cnt[i+1];
        }
        if (P/2 >= numb) {
            for (int i = 0; i < n; i++) cout << 'a';
            cout << '\n';
            continue;
        }
        int pt = 0;
        pair<int,int> ans;
        for (int t2 = 0; t2 <= P/2; t2++) {
            int t1 = P-2*t2;
            while (pt < N && cnt[pt] < t1) pt++;
        }
    }
}

