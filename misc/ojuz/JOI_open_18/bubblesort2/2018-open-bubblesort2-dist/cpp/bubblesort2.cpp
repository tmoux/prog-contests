#include "bubblesort2.h"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5+5;
int N;

void pr(const vector<int>& A) {
    for (int i: A) cout << i << ' ';
    cout << '\n';
}

int solve(const vector<int>& A) {
    //pr(A);
    vector<pair<int,int>> ps;
    for (int i = 0; i < N; i++) ps.push_back({A[i],i});
    sort(ps.begin(),ps.end());
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int ord = i;
        if (ord < ps[i].second) ans = max(ans,ps[i].second-ord);
    }
    return ans;
}

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V){
    N = A.size();
	int Q = X.size();
	vector<int> answer(Q);
    //brute method
    for (int i = 0; i < Q; i++) {
        A[X[i]] = V[i];
        answer[i] = solve(A);
    }
    return answer;
}
