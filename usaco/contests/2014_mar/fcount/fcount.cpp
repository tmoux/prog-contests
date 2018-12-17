#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int N;

bool havel_hakimi(const vector<int>& v) {
    int sum = 0;
    /*
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
    */
    for (int i: v) {
        if (i < 0) return false;
        sum += i;
    }
    if (sum == 0) return true;        
    vector<int> nv;
    for (int i = 1; i < v.size(); i++) {
        if (i <= v[0]) nv.push_back(v[i]-1);
        else nv.push_back(v[i]);
    }
    sort(nv.begin(),nv.end(),greater<int>());
    return havel_hakimi(nv);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("fcount.in","r",stdin); freopen("fcount.out","w",stdout);
    cin >> N; N++;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];                   
    }
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        vector<int> nv = a;
        nv.erase(nv.begin()+i);
        sort(nv.begin(),nv.end(),greater<int>());
        bool is = havel_hakimi(nv);
        if (is) ans.push_back(i+1);
        //cout << i+1 << ": " << is << '\n';
    }

    //output
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << '\n';

    return 0;
}

