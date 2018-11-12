#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ctoi(char c) {
    if (c == '#') return 0;
    return c;
    /*
    else {
        assert('A' <= c <= 'Z');
        return c-'A'+1;
    }
    */
}
vector<int> suffix_array(string s) {
    s += '#';
    const int alsz = 256;
    int n = s.size();
    //0-th iteration
    vector<int> perm(n), equiv(n), cnt(max(alsz,n),0);
    /*
    for (int i = 0; i < n; i++) cnt[ctoi(s[i])]++;
    for (int i = 1; i < alsz; i++) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++) perm[--cnt[ctoi(s[i])]] = i;
    int c = 0;
    for (int i = 0; i < n; i++) {
        equiv[perm[i]] = c;
        if (i < n - 1 && s[perm[i]] != s[perm[i+1]]) c++;
    }
    */
    for (int i = 0; i < n; i++) perm[i] = i;
    sort(perm.begin(),perm.end(),[&s](int a, int b) { return s[a] == s[b] ? a > b : s[a] < s[b];});
    int c = 0;
    for (int i = 0; i < n; i++) {
        equiv[perm[i]] = c;    
        if (i < n - 1 && s[perm[i]] != s[perm[i+1]]) c++;
    }
    /*
    int c = 2;
    perm = {5,4,3,2,1,0};
    equiv = {1,1,1,1,1,0};
    */
    /*
    for (int i = 0; i < n; i++) {
        cout << perm[i] << ' ' << equiv[i] << '\n';
    }
    cout << "c= " << c << '\n';
    */

    vector<int> pn(n), cn(n);
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i++) {
            pn[i] = perm[i] - l;
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(),cnt.end(),0);
        for (int i = 0; i < n; i++) cnt[equiv[pn[i]]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) perm[--cnt[equiv[pn[i]]]] = pn[i];
        cn[perm[0]] = 0;
        c = 1;
        for (int i = 1; i < n; i++) {
            pair<int,int> curr = {equiv[perm[i]],equiv[(perm[i]+l)%n]};
            pair<int,int> prev = {equiv[perm[i-1]], equiv[(perm[i-1]+l)%n]};
            if (curr != prev) c++;
            cn[perm[i]] = c-1;
        }
        equiv.swap(cn);
    }
    perm.erase(perm.begin());
    return perm;
}

vector<int> kasai(const string& txt, vector<int>& suffix_arr) {
    //return lcp array
    int n = txt.size();
    vector<int> inv(n), lcp(n);
    for (int i = 0; i < n; i++) {
        inv[suffix_arr[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (inv[i] == n - 1) {
            k = 0;
        }
        else {
            for (int j = suffix_arr[inv[i]+1]; i+k<n && j+k<n && txt[i+k] == txt[j+k]; k++) {}
            lcp[inv[i]] = k;    
            if (k > 0) k--;
        }
    }
    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        auto p = suffix_array(s);
        /*
        for (int i = 0; i < n; i++) {
            cout << p[i] << ": " << s.substr(p[i]) << '\n';
        }
        */
        auto lcp = kasai(s,p);
        int r = n - p[0];
        for (int i = 1; i < n; i++) {
            r += (n - p[i]) - lcp[i-1];
        }
        cout << r << '\n';
    }

    return 0;
}

