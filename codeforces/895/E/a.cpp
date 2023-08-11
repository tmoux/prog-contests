#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

int n, q;

//q1: Let m = r1-l1+1. We scale [l1,r1] by factor (m-1)/m and add
//sum(l2,r2)/((r2-l2+1)*(r1-l1+1)) to [l1,r1]. Simlarly for [l2,r2].
//q2: get sum of [l,r]

const int BLK = 300, SZ = maxn/BLK + 5;
int bucket[maxn];
double a[maxn];
double sum[SZ], lazy_add[SZ], lazy_mult[SZ];
int start[SZ];
int length[SZ];

void UPD(int b) {
    for (int i = start[b]; bucket[i] == b; i++) {
        sum[b] -= a[i];
        a[i] = a[i] * lazy_mult[b] + lazy_add[b];
        sum[b] += a[i];
    }
    lazy_mult[b] = 1;
    lazy_add[b] = 0;
}

double SUM(int l, int r) {
    UPD(bucket[l]);
    UPD(bucket[r]);
    double res = 0;
    while (l != 1 && bucket[l] != bucket[r] && bucket[l] == bucket[l-1]) {
        res += a[l];        
        l++;
    }
    while (bucket[l] < bucket[r]) {
        res += sum[bucket[l]]*lazy_mult[bucket[l]]+lazy_add[bucket[l]]*length[bucket[l]];
        l += BLK;
    }
    while (l <= r) {
        res += a[l];
        l++;
    }
    return res;
}

void ADD(int l, int r, double x) {
    UPD(bucket[l]);
    UPD(bucket[r]);
    while (l != 1 && bucket[l] != bucket[r] && bucket[l] == bucket[l-1]) {
        sum[bucket[l]] -= a[l];
        a[l] += x;
        sum[bucket[l]] += a[l];
        l++;
    }
    while (bucket[l] < bucket[r]) {
        lazy_add[bucket[l]] += x;
        l += BLK;
    }
    assert(l <= r);
    while (l <= r) {
        sum[bucket[l]] -= a[l];
        a[l] += x;
        sum[bucket[l]] += a[l];
        l++;
    }
}

void MULT(int l, int r, double x) {
    UPD(bucket[l]);
    UPD(bucket[r]);
    while (l != 1 && bucket[l] < bucket[r] && bucket[l] == bucket[l-1]) {
        sum[bucket[l]] -= a[l];
        a[l] *= x;
        sum[bucket[l]] += a[l];
        l++;
        //cout << l << ": " << a[l] << '\n';
    }
    while (bucket[l] < bucket[r]) {
        lazy_mult[bucket[l]] *= x;
        lazy_add[bucket[l]] *= x;
        l += BLK;
    }
    assert(l <= r);
    while (l <= r) {
        sum[bucket[l]] -= a[l];
        a[l] *= x;
        sum[bucket[l]] += a[l];
        l++;
        //cout << l << ": " << a[l] << '\n';
    }    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    //SQRT decomp
    memset(bucket,-1,sizeof bucket);
    for (int i = 1; i <= n; i++) {
        bucket[i] = (i-1)/BLK;
        sum[bucket[i]] += a[i];
        length[bucket[i]]++;
        if (i == 1 || bucket[i] != bucket[i-1]) {
            start[bucket[i]] = i;
        }
    }
    int lastBucket = bucket[n];
    for (int b = 0; b <= lastBucket; b++) {
        lazy_add[b] = 0;
        lazy_mult[b] = 1;
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            int len1 = r1-l1+1, len2 = r2-l2+1;
            double s1 = SUM(l1,r1);
            double s2 = SUM(l2,r2);
            MULT(l1,r1,(double)(len1-1)/len1);

            /*
            printf("[%d,%d], [%d,%d]\n",l1,r1,l2,r2);
            for (int i = 1; i <= n; i++) {
                cout << i << ": " << SUM(i,i) << '\n';
            }
            continue;
            */
            ADD(l1,r1,(s2/len1)/len2);

            MULT(l2,r2,(double)(len2-1)/len2);
            ADD(l2,r2,(s1/len1)/len2);

            
        }
        else {
            int l, r; cin >> l >> r;
            double ans = SUM(l,r);
            cout << ans << '\n';
        }
    }
}

