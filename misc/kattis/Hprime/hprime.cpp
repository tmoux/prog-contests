#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxh = 1e6+5;
bool isH(int x) {
    return ((x-1) % 4) == 0;
}
int cnt[maxh];
vector<int> ans;

void sieve() {
    for (int i = 2; i < maxh; i++) {
        if (!isH(i) || cnt[i] > 0) continue;
        ans.push_back(i);
        for (int j = i; j < maxh; j += i) {
            cnt[j]++;
        }
        if (isH(1LL*i*i) && 1LL*i*i < maxh) cnt[i*i]++;
    }
}

int pfx[maxh];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sieve();
    for (int i = 1; i < maxh; i++) {
        pfx[i] += pfx[i-1];
        if (isH(i) && cnt[i] == 2) pfx[i]++;
    }


    cout << pfx[21] << ' ' << pfx[85] << ' ' << pfx[789] << '\n';
    
    return 0;
}
