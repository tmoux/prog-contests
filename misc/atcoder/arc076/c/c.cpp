#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//We only care about lines with both endpoints on the edges.
int R, C;
int N;
const int maxn = 1e5+5;

int gettime(int x, int y) {
    if (x == 0) {
        return y;
    }
    else if (y == R) {
        return R + x;
    }
    else if (x == C) {
        return R + C + (R - y);
    }
    else {
        return R + C + R + (C - x);
    }
}

bool isBorder(int x, int y) {
    return x == 0 || x == C || y == 0 || y == R;
}

struct Event
{
    bool start;
    int t, id;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> C >> N;
    vector<Event> events;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2; cin >> y1 >> x1 >> y2 >> x2;
        if (isBorder(x1,y1) && isBorder(x2,y2)) {
            int t1 = gettime(x1,y1);
            int t2 = gettime(x2,y2);
            if (t1 > t2) swap(t1,t2);
            events.push_back({true,t1,i});    
            events.push_back({false,t2,i});    
        }
    }
    sort(events.begin(),events.end(),[](auto a, auto b) {
            return a.t < b.t;
            });
    stack<int> st;
    bool poss = true;
    for (Event e: events) {
        if (e.start) {
            st.push(e.id);
        }
        else {
            if (st.top() != e.id) {
                //not possible
                cout << "NO\n";
                return 0;
            }
            else {
                st.pop();
            }
        }
    }
    cout << "YES\n";
}

