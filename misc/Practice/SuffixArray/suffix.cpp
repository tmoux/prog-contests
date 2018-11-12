#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int alsz = 29;

struct Suffix
{
    int x, y, id;
};

void radix_sort(vector<Suffix>& sfx) {
    //temporary
    sort(sfx.begin(),sfx.end(),[](const Suffix& a, const Suffix& b) {
            return a.x != b.x ? a.x < b.x : a.y < b.y; });
}

vector<int> suffix_array(string s) {
    s += '#';
    int n = s.size();
    vector<int> idx(n), ord(n), ans(n);
    vector<Suffix> sfx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(),idx.end(),[&s](int a, int b) { return s[a] < s[b]; });
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
        radix_sort(sfx);
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (i != 0 && (sfx[i].x != sfx[i-1].x || sfx[i].y != sfx[i-1].y)) c++;         
            ord[sfx[i].id] = c;             
        }
    }

    for (int i = 0; i < n; i++) ans[ord[i]] = i;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    vector<int> suffixes = suffix_array(s);
    for (int i = 0; i < suffixes.size(); i++) {
        cout << suffixes[i] << ": " << s.substr(suffixes[i]) << '\n';
    }

    return 0;
}
