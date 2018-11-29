#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
const int oo = 999999999;
int n, c, a[maxn];
int prefc[maxn];
vector<int> nums[maxn];

int maxsum(const vector<int>& vs, int l, int r) { //divide and conquer for max subarray sum
    if (r < l) return 0;
    if (l == r) return vs[l];
    int m = (l+r)/2;
    int r1 = maxsum(vs,l,m);
    int r2 = maxsum(vs,m+1,r);
    int lres = -oo, rres = -oo;
    int lsum = 0, rsum = 0;
    for (int i = m; i >= l; i--) {
        lsum += vs[i];
        lres = max(lres,lsum);
    }
    for (int i = m+1; i <= r; i++) {
        rsum += vs[i];
        rres = max(rres,rsum);
    }
    int ans = max(lres+rres,max(r1,r2));
    //cout << l << ' ' << r << ": " << ans << '\n';
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        nums[a[i]].push_back(i);
        if (a[i] == c) prefc[i]++;
        prefc[i] += prefc[i-1];
    }
    int maxans = prefc[n];
    for (int i = 1; i <= 500000; i++) {
        if (nums[i].empty()) continue;
        if (i == c) continue;
        if (nums[i].size() == 1) maxans = max(maxans,prefc[n]+1);
        else {
            vector<int> vs;
            for (int j = 1; j < nums[i].size(); j++) {
                vs.push_back(1-(prefc[nums[i][j]]-prefc[nums[i][j-1]]));  
            }
            /*
            cout << i << ":\n";
            for (int j = 0; j < nums[i].size()-1; j++) {
                cout << vs[j] << ' ';
            }
            cout << '\n';
            */
            int cnt = maxsum(vs,0,vs.size()-1) + 1 + prefc[n];
            //cout << "cnt = " << maxsum(vs,0,vs.size()-1) << '\n';
            maxans = max(maxans,cnt);
        }
    }
    cout << maxans << '\n';

    return 0;
}

