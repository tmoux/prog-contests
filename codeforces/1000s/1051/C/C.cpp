#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void assign(vector<int>& v, char c, vector<char>& ans) {
    for (int i: v) ans[i] = c;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    map<int,vector<int>> f;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        f[ai].push_back(i);
    }
    vector<char> ans(n);
    vector<vector<int>> ones, twos, threes;
    for (auto& p: f) {
        if (p.second.size() == 1) ones.push_back(p.second);
        else if (p.second.size() == 2) twos.push_back(p.second);
        else threes.push_back(p.second);
    }
    int a = 0, b = 0;
    for (vector<int>& v: ones) {
        if (a < b) { 
            assign(v,'A',ans);
            a++;
        }
        else {
            assign(v,'B',ans);
            b++;
        }   
    }
    for (vector<int>& v: twos) {
        assign(v,'A',ans);
    }
    for (vector<int>& v: threes) {
        if (a < b) {
            ans[v.back()] = 'A';
            v.pop_back();
            assign(v,'B',ans);
            a++;
        }
        else {
            assign(v,'A',ans);
        }
    }
    //output
    if (a == b) {
        cout << "YES\n";
        for (char c: ans) cout << c;
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }


    return 0;
}

