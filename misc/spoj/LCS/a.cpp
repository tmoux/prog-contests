#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> suffix_array(string s) {
    s += '#';
    const int alsz = 256;
    int n = s.size();
    //0-th iteration
    vector<int> perm(n), equiv(n), cnt(max(alsz,n),0);
    for (int i = 0; i < n; i++) perm[i] = i;
    sort(perm.begin(),perm.end(),[&s](int a, int b) { return s[a] == s[b] ? a > b : s[a] < s[b];});
    int c = 0;
    for (int i = 0; i < n; i++) {
        equiv[perm[i]] = c;
        if (i < n - 1 && s[perm[i]] != s[perm[i+1]]) c++;
    }

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
    string s, t; cin >> s >> t;
    string st = s + '$' + t;
    int n = st.size();
    vector<int> suffixes = suffix_array(st), lcp = kasai(st,suffixes);
    /*
    for (int i = 0; i < n; i++) {
        cout << st.substr(suffixes[i]) << '\n';
    }
    for (int i = 0; i < n; i++) {
        cout << suffixes[i] << ' ' << lcp[i] << '\n';
    }
    */
    int delim = s.size();
    multiset<int> curr, minLcp;
    int R = 1;
    int maxans = 0;
    for (int i = 0; i < n-1; i++) {
        if (i > 0) {
            curr.erase(curr.find(suffixes[i-1]));
            if (curr.count(suffixes[i-1])) curr.erase(curr.find(suffixes[i-1]));
            minLcp.erase(minLcp.find(lcp[i-1]));
        }
        while (R < n && (curr.empty() || *curr.begin() > delim || *curr.rbegin() < delim)) {
            curr.insert(suffixes[R-1]);
            curr.insert(suffixes[R]);
            minLcp.insert(lcp[R-1]);
            R++;
        }
        if (*curr.begin() < delim && *curr.rbegin() > delim) {
            maxans = max(maxans,*minLcp.begin());
            //cout << i << ' ' << R << ": " << *minLcp.begin() << '\n';
        }
    }
    cout << maxans << '\n';
}
