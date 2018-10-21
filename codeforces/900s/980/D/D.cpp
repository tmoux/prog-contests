#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int A[maxn], n;
int ans[maxn];
map<int,int> mapp;
bool nums[maxn];
int idx = 0;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //read in input, reduce all numbers
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        //if (n != 5000) {
            bool isNeg = ai < 0;
            if (isNeg) ai *= -1;
            for (int j = 2; j*j <= ai; j++) {
                while (ai % (j*j) == 0) {
                    ai /= (j*j);
                }
            }
            if (isNeg) ai *= -1;
            if (mapp.find(ai) == mapp.end()) {
                mapp[ai] = idx++;            
            }
            A[i] = ai;
        //}
        //cout << mapp.size() << '\n';
    }
   
    for (int i = 0; i < n; i++) {
        memset(nums,0,sizeof(nums));
        int sz = 0;
        for (int j = i; j < n; j++) {
            if (A[j] == 0) {
                ans[max(1,sz)]++;
                continue;
            }
            if (!nums[mapp[A[j]]]) {
                sz++;
                nums[mapp[A[j]]] = true;
            }
            ans[sz]++;
            //cout << A[j] << ' ' << mapp[A[j]] << '\n';
        }
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
	

