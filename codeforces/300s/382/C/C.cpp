#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, A[maxn];


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    if (n == 1) {
        cout << -1 << '\n';
        return 0;
    }
    map<int,int> gaps;
    sort(A,A+n);
    for (int i = 0; i < n - 1; i++) {
        gaps[A[i+1]-A[i]]++;
    }
    if (gaps.size() == 1) {
        int diff = gaps.begin()->first;
        set<int> ans;
        ans.insert(A[0]-diff);
        ans.insert(A[n-1]+diff);
        if (n == 2 && ((A[1]-A[0]) % 2 == 0)) {
            ans.insert((A[0]+A[1])/2);
        }
        cout << ans.size() << '\n';
        for (int i: ans) {
            cout << i << ' ';
        }
        return 0;
    }
    vector<pair<int,int>> ps;
    for (auto p: gaps) {
        ps.push_back(p);
    }
    if (ps.size() == 2) {
        for (int a = 0; a < 2; a++) {
            if (ps[0].first == ps[1].first * 2 && ps[0].second == 1) {
                int gap = ps[0].first;
                for (int i = 0; i < n-1; i++) {
                    if (A[i+1]-A[i] == gap) {
                        cout << 1 << '\n';
                        cout << (A[i]+A[i+1])/2 << '\n';
                        return 0;
                    }
                }
            }
            swap(ps[0],ps[1]);    
        }
    }
    cout << 0 << '\n';

    return 0;
}
	

