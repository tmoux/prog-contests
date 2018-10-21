#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, A[maxn];
char ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<pair<int,int>> vs;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        vs.push_back({A[i],i});
    }
    sort(vs.begin(),vs.end(),[](const pair<int,int>& a, const pair<int,int>& b) {return a.first > b.first;});
    for (auto& p: vs) {
        int ai = p.first;
        int i = p.second;
        bool foundB = false;
        for (int j = i - ai; j >= 1; j -= ai) {
            if (A[j] > ai && ans[j] == 'B') {
                foundB = true;
                break;
            }
        }
        for (int j = i + ai; j <= n; j += ai) {
            if (A[j] > ai && ans[j] == 'B') {
                foundB = true;
                break;
            }
        }
        ans[i] = foundB ? 'A' : 'B';
        //cout << ai << ' ' << i << ": " << ans[i] << '\n';
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i];
    }

    return 0;
}

