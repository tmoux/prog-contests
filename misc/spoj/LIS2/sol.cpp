#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N;

struct Point
{
    int first, second, id;
    bool operator<(const Point& r) const {
        if (first != r.first) return first < r.first;
        return second < r.second;
    }
};

struct Hull : public vector<pair<int,int>>
{
    //maintains points in sorted x order, y must be nonincreasing
    void insert(int x, int y) { //find the 
        int n = this->size();
        int lo = -1, hi = n;
        while (lo + 1 < hi) {
            int mid = (lo+hi)>>1;
            if (h[mid].x < x) lo = mid;
            hi = mid;    
        }
    }
} lis[maxn];

bool poss(int x, int y, int li) {
    if (lis[li].empty()) return false;
    pair<int,int> p = {x,y};
    //find the point with largest x value s.t.
    //q.x < x. Then check if q.y < y
    Hull& h = lis[li];
    int n = h.size();
    int lo = -1, hi = n;
    
    if (lo == -1) return false;
    return h[lo].y < y;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    vector<Point> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].id = i + 1;
    }
    //Coordinate compress
    sort(a.begin(),a.end());
    map<int,int> mp;
    int pt = 1;
    for (auto& p: a) {
        if (mp.count(p.first)) p.first = mp[p.first];
        else p.first = mp[p.first] = pt++;
    }
    sort(a.begin(),a.end(),[](auto a, auto b) { 
        return a.second < b.second;});
    mp.clear();
    pt = 1;
    for (auto& p: a) {
        if (mp.count(p.second)) p.second = mp[p.second];
        else p.second = mp[p.second] = pt++;
    }
    sort(a.begin(),a.end(),[](auto a, auto b) {
            return a.id < b.id;
            });
    //now its compressed
    for (auto p: a) {
        int x = p.first;
        int y = p.second;
        //binary search for lis
        int lo = 0, hi = N;
        while (lo + 1 < hi) {
             int mid = (lo+hi)>>1;
            if (poss(x,y,mid)) lo = mid;
            else hi = mid;
        }
        //ans is lo + 1;
        int li = lo + 1;
        lis[li].insert(x,y); //insert point into hull           
    }
}

