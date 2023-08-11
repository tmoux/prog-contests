#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MaxQueue
{
    deque<pair<ll,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    int maximum() {
        assert(!q.empty()); 
        return q.front().first; 
    }
    void push(ll new_element) { //add new element 
        while (!q.empty() && q.back().first < new_element) {
            q.pop_back();
        }
        q.push_back({new_element,cnt_added});
        cnt_added++; 
    }
    void pop() {
        if (!q.empty() && q.front().second == cnt_removed) {
            q.pop_front(); 
        }
        cnt_removed++; 
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    MaxQueue q;
    q.push(5);
    q.push(3);
    q.push(-1);
    q.push(4);
    cout << q.maximum() << '\n';
    q.pop();
    cout << q.maximum() << '\n';

}



