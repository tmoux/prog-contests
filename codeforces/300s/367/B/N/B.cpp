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
int A[maxn], B[maxn], n, m, p;
unordered_map<int,int> bfreq;
vector<int> subseq[maxn];
vector<int> bs;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> B[i];
        bfreq[B[i]]++;
        bs.push_back(B[i]);
    }
    //build subsequences
    for (int i = 1; i <= p; i++) {
        for (int q = i; q + (m-1)*p <= n; q += p) {
            subseq[i].push_back(q);
        }
    }

    int ans = 0;
    vector<int> res;
    for (int q = 1; q <= p; q++) {
        unordered_map<int,int> freq;
        for (int i = q; i < q+p; i++) {
            freq[subseq[q][i]]++;
        }
        unordered_set<int> diffs;
        for (int i: bs) {
            if (bfreq[i] != freq[i]) {
                diffs.insert(i);
            }
        }
        if (!diffs.empty()) {
            ans++;
            res.push_back(q);
        }
        for (int newq = q+1; newq <= subseq[q].size()-m; newq++) {
            int prev = A[subseq[q][newq-1]];
            int nxt = A[subseq[q][newq+m-1]];
            freq[prev]--;
            freq[nxt]++;
            if (freq[prev] != bfreq[prev]) {
                diffs.insert(prev);
            }
            else {
                diffs.erase(prev);
            }
            if (freq[nxt] != bfreq[nxt]) {
                diffs.insert(nxt);
            }
            else {
                diffs.erase(nxt);
            }

            if (!diffs.empty()) {
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
	

