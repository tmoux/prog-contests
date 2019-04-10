#include "xylophone.h"
using namespace std;
#include <bits/stdc++.h>

static int A[5005];
int n;

int d2[5005], d3[5005];

void pr(const vector<int>& a) {
    cout << "VEC:\n";
    for (int i: a) cout << i << ' ';
    cout << '\n';
}

bool check(const vector<int>& v) {
    //pr(v);
    for (int i = 0; i < n; i++) if (v[i] <= 0 || v[i] > n) return false;
    for (int i = 0; i < n - 1; i++) {
        if (abs(v[i+1]-v[i]) != d2[i+1]) return false;
    }
    for (int i = 0; i < n - 2; i++) {
        int d = max(abs(v[i+2]-v[i+1]),max(abs(v[i+1]-v[i]),abs(v[i+2]-v[i])));
        if (d != d3[i+1]) return false;
    }
    //sanity checks
    int pos1 = -1, posn = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] == 1) pos1 = i;
        else if (v[i] == n) posn = i;
    }
    if (pos1 == -1 || pos1 == -1) return false;
    if (pos1 > posn) return false;
    return true;
}

bool tr(int i) {
    //cout << "starting " << i << endl;
    vector<int> a, b;
    a.push_back(i);
    b.push_back(i);
    if (d3[1] == d2[1] + d2[2]) {
        a.push_back(a.back()+d2[1]);
        a.push_back(a.back()+d2[2]);
        b.push_back(b.back()-d2[1]);
        b.push_back(b.back()-d2[2]);
    }
    else {
        a.push_back(a.back()+d2[1]);
        a.push_back(a.back()-d2[2]);
        b.push_back(b.back()-d2[1]);
        b.push_back(b.back()+d2[2]);
    }

    for (int j = 2; j <= n - 2; j++) {
        vector<int>& aa = a;
        vector<int>& bb = b;
        if (a.back() < a[a.size()-2]) swap(a,b);
        if (d3[j] == d2[j] + d2[j+1]) {
            a.push_back(a.back()+d2[j+1]);
            b.push_back(b.back()-d2[j+1]);
        }
        else {
            a.push_back(a.back()-d2[j+1]);
            b.push_back(b.back()+d2[j+1]);
        }
    }
    if (check(a)) {
        for (int i = 0; i < n; i++) {
            answer(i+1,a[i]);
            //cout << (i+1) << ": " << a[i] << endl;
        }
        return true;
    }
    else if (check(b)) {
        for (int i = 0; i < n; i++) {
            answer(i+1,b[i]);
            //cout << (i+1) << ": " << b[i] << endl;
        }
        return true;
    }
    return false;
}

void solve(int N) {
    n = N;
    for (int i = 1; i <= N - 1; i++) {
        d2[i] = query(i,i+1);
        //cout << i << ' ' << i+1 << ": " << d2[i] << '\n';
    }
    for (int i = 1; i <= N - 2; i++) {
        d3[i] = query(i,i+2);
        //cout << i << ' ' << i+2 << ": " << d3[i] << '\n';
    }
    for (int i = 1; i <= N; i++) {
        if (tr(i)) break;
    }
}
