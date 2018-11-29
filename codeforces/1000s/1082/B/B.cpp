#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int Gcnt = 0, Scnt = 0;
    for (char c: s) {
        if (c == 'G') Gcnt++;
        else Scnt++;
    }
    if (Gcnt == 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (Gcnt == n) {
        cout << n << '\n';
        return 0;
    }
    vector<pair<int,char>> segs;
    char curr = 'X';
    int curlen = 0;
    for (char c: s) {
        if (c == curr) {
            curlen++;
        }
        else {
            if (curr != 'X') {
                segs.push_back({curlen,curr});
            }
            curlen = 1;
            curr = c;
        }
    }
    segs.push_back({curlen,curr});
    int bsegs = 0;
    int longest = 0;
    for (auto p: segs) {
        //cout << p.first << ": " << p.second << '\n';
        if (p.second == 'G') {
            bsegs++;
            longest = max(longest,p.first);
        }
    }
    if (bsegs == 1) {
        cout << longest << '\n';
        return 0;
    }
    //find greatest sum of two seperated by size 1 S segment
    int greatestSum = 0;
    for (int i = 0; i < segs.size(); i++) {
        if (segs[i].second == 'G' && i-2 >= 0 && segs[i-1].first == 1) {
            greatestSum = max(greatestSum,segs[i].first+segs[i-2].first);    
        }
    }
    //cout << greatestSum << '\n';
    if (bsegs == 2) {
        if (greatestSum == 0) {
            cout << longest+1 << '\n';
        }
        else {
            cout << greatestSum << '\n';
        }
        return 0;
    }
    if (greatestSum == 0) {
        cout << longest+1 << '\n';
    }
    else {
        cout << max(greatestSum+1,longest+1) << '\n';
    }


    return 0;
}

