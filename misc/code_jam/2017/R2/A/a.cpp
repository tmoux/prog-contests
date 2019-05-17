#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int getans(const vector<int>& v,int P) {
    int curr = 0;
    int ans = 0;
    for (int i: v) {
        //cout << i << ' ';
        if (curr == 0) ans++;
        curr += i;
        curr %= P;
    }
    //cout << '\n';
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for (int aa = 1; aa <= T; aa++) {
        cout << "Case #" << aa << ": ";
        int N, P; cin >> N >> P;
        vector<int> g(N);
        map<int,int> cnt;
        for (int i = 0; i < N; i++) {
            int gi; cin >> gi;
            gi %= P;
            g[i] = gi;
            cnt[gi]++;
        }
        vector<int> v;
        while (cnt[0]) {
            cnt[0]--;
            v.push_back(0);
        }
        if (P == 2) {
            while (cnt[1]) {
                cnt[1]--;
                v.push_back(1);
            }
        }
        else if (P == 3) {
            while (cnt[1] > 0 && cnt[2] > 0) {
                cnt[1]--;
                cnt[2]--;
                v.push_back(1);
                v.push_back(2);
            }
            while (cnt[1] > 0) {
                cnt[1]--;
                v.push_back(1);
            }
            while (cnt[2] > 0) {
                cnt[2]--;
                v.push_back(2);
            }
        }
        else {
            assert(P == 4);
            while (cnt[1] > 0 && cnt[3] > 0) {
                cnt[1]--;
                cnt[3]--;
                v.push_back(1);
                v.push_back(3);
            }
            while (cnt[2] > 1) {
                cnt[2]--;
                cnt[2]--;
                v.push_back(2);
                v.push_back(2);
            }
            //cout << cnt[1] << ' ' << cnt[3] << '\n';
            assert((cnt[1] == 0) || (cnt[3] == 0));
            assert(cnt[2] <= 1);
            while (cnt[2] > 0) {
                cnt[2]--;
                v.push_back(2);
            }
            while (cnt[1] > 0) {
                cnt[1]--;
                v.push_back(1);
            }
            while (cnt[3] > 0) {
                cnt[3]--;
                v.push_back(3);
            }
             
        }
        cout << getans(v,P) << '\n';
    }
}

