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
    }

    int ans = 0;
    vector<int> res;
    for (int q = 1; q <= p; q++) {
        unordered_map<int,int> freq;
        for (int i = 0; i < m; i++) {
            int j = q + i*p;
            if (j > n) break;
            freq[A[j]]++;
        }
        /*
        if (q == 4) {  
        cout << q << '\n';
        for (auto p: freq) {
            cout << p.first << ": " << p.second << '\n';
        }
        }
        */
       
        unordered_set<int> diffs;
        for (auto p: bfreq) {
            //cout << "Bfreq:\n";
            //cout << p.first << '\n';
            if (!(freq.count(p.first) && freq[p.first] == p.second)) {
                diffs.insert(p.first);
            }
        }
        /*
        if (q == 4) {
            cout << diffs.size() << '\n';
            for (int i: diffs) cout << i << ' ';
        }
        cout << '\n';
        */
        if (diffs.empty()) {
            ans++;
            res.push_back(q);
        }
        for (int newq = q+p; newq + (m-1)*p <= n; newq += p) {
            int prev = A[newq - p];
            int nxt = A[newq + (m-1)*p];
            freq[prev]--;
            freq[nxt]++;

            if (diffs.count(prev) && bfreq.find(prev) != bfreq.end() && freq[prev] == bfreq[prev]) {
                diffs.erase(prev);
            }
            else if (!diffs.count(prev)) {
                diffs.insert(prev);
            }
            if (diffs.count(nxt) && bfreq.find(nxt) != bfreq.end() &&  freq[nxt] == bfreq[nxt]) {
                diffs.erase(nxt);
            }
            else if (!diffs.count(nxt)) {
                diffs.insert(nxt);
            }
            if (newq == 30) { 
            cout << newq << '\n';
            for (auto p: freq) {
                cout << p.first << ": " << p.second << '\n';
            }
            cout << diffs.size() << '\n';
            for (int i: diffs) cout << i << ' ';
            cout << '\n';
            }
            
            if (diffs.empty()) {
                ans++;
                res.push_back(newq);
            }
        }
    }
    cout << ans << '\n';
    sort(res.begin(),res.end());
    for (int i: res) {
        cout << i << ' ';
    }

    return 0;
}
	

