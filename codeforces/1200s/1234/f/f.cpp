#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
string s;

vector<int> masks[25];

int main() {
    cin >> s;
    n = s.size();
    int res = 0;
    for (int i = 0; i < n; i++) {
        int msk = 0;
        int cnt = 0;
        for (int j = i; j < n; j++) {
            int c = s[j] - 'a';
            if (msk&(1<<c)) break;
            else {
                msk |= (1<<c);
                masks[++cnt].push_back(msk);
                //cout << i << ": " << cnt << ' ' << msk << '\n';
            }
        }
        res = max(res,cnt);
    }
    for (int i = 0; i <= 20; i++) {
        sort(masks[i].begin(),masks[i].end());
        masks[i].erase(unique(masks[i].begin(),masks[i].end()),masks[i].end());
    }
    int r = 0;
    for (int ans = 20; ans >= 1; ans--) {
        for (int i = 1; i <= ans/2; i++) {
            for (int m1: masks[i]) {
                for (int m2: masks[ans-i]) {
                    if ((m1 & m2) == 0) {
                        r = ans;
                        //cout << "OKOK\n";
                        goto end;
                    }
                }
            }
        }
    }
    end:
    r = max(r,res);
    cout << r << '\n';
}

