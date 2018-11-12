#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int alsz = 65;
const int maxn = 5e4+100;

struct Suffix
{
    int x, y, id;
    bool operator<(const Suffix& b) const {
        return x != b.x ? x < b.x : y < b.y;
    }
};

void radix_sort(Suffix* sfx, int n) {
    //temporary
    sort(sfx,sfx+n);
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 30; j++) {

        }
    }
    */
}
int counter = 0;

int idx[maxn], ord[maxn];
Suffix sfx[maxn];
void suffix_array(string s, int* ans) {
    s += '#';
    int n = s.size();
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx,idx+n,[&s](int a, int b) { return s[a] < s[b]; });
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0 && s[idx[i]] != s[idx[i-1]]) c++;
        ord[idx[i]] = c;
    }
    //doubling method
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i++) {
            sfx[i] = {ord[i],i+l<n?ord[i+l]:0,i};
        }
        radix_sort(sfx,n);
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (i != 0 && (sfx[i].x != sfx[i-1].x || sfx[i].y != sfx[i-1].y)) c++;         
            ord[sfx[i].id] = c;             
        }
    }

    for (int i = 0; i < n; i++) {
        ans[ord[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        ans[i] = ans[i+1];
    }
    s.pop_back();
}

int inv[maxn];
void kasai(const string& txt, int* suffix_arr, int* lcp) {
    //return lcp array
    int n = txt.size();
    for (int i = 0; i < n; i++) {
        inv[suffix_arr[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (inv[i] == n - 1) {
            k = 0;
        }
        else {
            for (int j = suffix_arr[inv[i]+1]; i+k < n && j+k<n && txt[i+k] == txt[j+k]; k++) {}
            lcp[inv[i]] = k;    
            if (k > 0) k--;
        }
    }
}

int suffixes[maxn];
int lcp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        suffix_array(s,suffixes);
        kasai(s,suffixes,lcp);
        /*
        for (int i = 0; i < n; i++) {
            cout << i << ": " << suffixes[i] << ' ' << s.substr(suffixes[i]) << '\n';
        }
        */
        int res = n - suffixes[0];
        for (int i = 1; i < n; i++) {
            res += (n - suffixes[i]) - lcp[i-1];
        }
        cout << res << '\n';
    }

    return 0;
}
