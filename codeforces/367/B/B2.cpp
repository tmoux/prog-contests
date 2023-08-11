#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int A[maxn], B[maxn];
ll n, m, p;
unordered_map<int,int> bfreq;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> B[i];
        bfreq[B[i]]++;
    }

    if (1 + (m-1)*p > n) {
        cout << "0\n";
        return 0;
    }

    int ans = 0;
    vector<int> res;
    for (ll q = 1; q <= p; q++) {
        unordered_map<int,int> freq;
        for (ll i = 0; i < m; i++) {
            ll j = q + i*p;
            if (j > n) break;
            freq[A[j]]++;
        }

        unordered_set<int> diffs;
        for (auto p: bfreq) {
            if (freq[p.first] != p.second) {
                diffs.insert(p.first);
            }
        }
       if (diffs.empty()) {
            ans++;
            res.push_back(q);
        }
        for (ll newq = q+p; newq + (m-1)*p <= n; newq += p) {
            ll prev = A[newq - p];
            ll nxt = A[newq + (m-1)*p];
            freq[prev]--;
            freq[nxt]++;
           
            if (freq[prev] == bfreq[prev]) {
                diffs.erase(prev);
            }
            else {
                diffs.insert(prev);
            }
            if (freq[nxt] == bfreq[nxt]) {
                diffs.erase(nxt);
            }
            else {
                diffs.insert(nxt);
            }
            if (diffs.empty()) {
                ans++;
                res.push_back(newq);
            }
        }
    }
    //output
    cout << ans << '\n';
    sort(res.begin(),res.end());
    for (int i: res) {
        cout << i << ' ';
    }

    return 0;
}
	

