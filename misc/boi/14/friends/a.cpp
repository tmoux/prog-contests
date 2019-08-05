#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 2e6+6;
const int M = 1e9+7;
const int base = 31;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int madd(int a, int b) {
    return (a+b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int ctoi(char c) {
    return c-'A'+1;
}
 
int N;
string U;
 
int pwr[maxn], ipwr[maxn];
int pre[maxn];
 
int sub(int l, int r) {
    return mult((pre[r]-pre[l-1]+M)%M,ipwr[l-1]);
}
 
int comb(int l1, int r1, int l2, int r2) {
    int h1 = sub(l1,r1);
    int h2 = sub(l2,r2);
    int shift = r1-l1+1;
    return madd(h1,mult(h2,pwr[shift]));
}
 
map<int,pair<int,int>> ans;
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> U;
    if (N % 2 == 0) {
        cout << "NOT POSSIBLE\n";        
        return 0;
    }
    U = '#' + U;
    pwr[0] = ipwr[0] = 1;
    for (int i = 1; i <= N; i++) {
        pwr[i] = mult(pwr[i-1],base);
    }
    ipwr[1] = modexp(base,M-2);
    for (int i = 2; i <= N; i++) {
        ipwr[i] = mult(ipwr[i-1],ipwr[1]);
    }
    for (int i = 1; i <= N; i++) {
        pre[i] = madd(pre[i-1],mult(ctoi(U[i]),pwr[i-1]));
    }
    vector<int> hashes; //hashes of the answers
    int mid = N/2+1;
    for (int i = 1; i <= N; i++) {
        int h1, h2;
        if (i <= mid) {
            h2 = sub(mid+1,N);
            if (i == 1) {
                h1 = sub(2,mid);
            }
            else if (i == mid) {
                h1 = sub(1,mid-1);
            }
            else {
                h1 = comb(1,i-1,i+1,mid);
            }
        }
        else {
            h1 = sub(1,mid-1);
            if (i == N) {
                h2 = sub(mid,N-1);
            }
            else {
                h2 = comb(mid,i-1,i+1,N);
            }
        }
        //cout << i << ": " << h1 << ' ' << h2 << '\n';
        if (h1 == h2) {
            hashes.push_back(h1);
            ans[h1] = (i <= mid) ? make_pair(mid+1,N) : make_pair(1,mid-1);
        }
    }
    sort(hashes.begin(),hashes.end());
    hashes.erase(unique(hashes.begin(),hashes.end()),hashes.end());
    if (hashes.empty()) {
        cout << "NOT POSSIBLE\n";
    }
    if (hashes.size() > 1) {
        cout << "NOT UNIQUE\n";
    }
    else {
        int l = ans[hashes[0]].first;
        int r = ans[hashes[0]].second;
        for (int i = l; i <= r; i++) {
            cout << U[i];
        }
        cout << '\n';
    }
}
