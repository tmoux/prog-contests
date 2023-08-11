#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 300005;
struct Segment
{
    int first, second, orig;
    bool operator<(const Segment& rhs) const {
        if (first != rhs.first) {
            return first < rhs.first;
        }
        return second > rhs.second;
    }
} segs[maxn];


int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int li, ri; cin >> li >> ri;
        segs[i] = {li,ri,i+1};
    }
    sort(segs,segs+n);
    int maxR = segs[0].second;
    Segment lastPair = segs[0];
    for (int i = 1; i < n; i++) {
        //check if is valid
        if (segs[i].second <= maxR) {
            cout << segs[i].orig << ' ' << lastPair.orig << '\n';
            return 0;
        }
        else {
            maxR = segs[i].second;
            lastPair = segs[i];
        }
    }
    cout << "-1 -1\n";
    return 0;
}
	

