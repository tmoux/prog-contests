#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 400005;
int n, d, k; 
vector<pair<int,int>> ans;
int curr = 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> d >> k;
    if (d == 1) {
        if (n == 2) {
            cout << "YES" << '\n';
            cout << "1 2" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
        return 0;
    }

    if (k == 1) {
        if (n == 2 && d == 1) {
            cout << "YES" << '\n';
            cout << "1 2" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
        return 0;
    }

    //make line graph
    if (n < d + 1) {
        cout << "NO" << '\n';
        return 0;
    }
    for (int i = 0; i < d; i++) {
        ans.push_back({curr,curr+1});
        curr++;
        n--;
    }
    curr++;
    n--;
    for (int i = 2; i <= d && n > 0; i++) {
        //add a tree to node i
        int treeDiam = min(d - i + 1, i - 1);
        queue<pair<int,int>> q; //first is number, second is distance from line graph
        q.push({i,0});
        while (!q.empty() && n > 0) {
            pair<int,int> f = q.front();
            if (f.second < treeDiam) {
                int numAdd = (f.first == i ? k - 2 : k - 1);
                for (int b = 0; b < numAdd && n > 0; b++) {
                    q.push({curr,f.second+1});
                    ans.push_back({f.first,curr});
                    curr++;
                    n--;
                }
            }
            q.pop();
        }
        /*
        vector<int> c1 = {i}, c2;
        for (int j = 0; j < treeDiam && n > 0 && c1.size() > 0; j++) {
            for (int a = 0; a < c1.size() && n > 0; a++) {
                int numAdd;
                if (c1[a] == i) numAdd = k - 2;
                else numAdd = k - 1;
                for (int b = 0; b < numAdd && n > 0; b++) {
                    ans.push_back({c1[a],curr});
                    c2.push_back(curr);
                    curr++;
                    n--;
                }
            }
            c1 = c2;
            c2.clear();
        }
        */
    }

    //output
    if (n > 0) {
        cout << "NO" << '\n';
    }
    else {
        cout << "YES" << '\n';
        for (pair<int,int> p: ans) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }



    return 0;
}
	

