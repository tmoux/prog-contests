#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Student {int id, score;
    bool operator<(const Student& rhs) {
        if (score != rhs.score) {
            return score > rhs.score;
        }
        else return id < rhs.id;
    }
}
;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<Student> vec;
    for (int i = 1; i <= n; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        vec.push_back({i,a+b+c+d});
    }
    sort(vec.begin(),vec.end());
    for (int i = 0; i < n; i++) {
        if (vec[i].id == 1) {
            cout << (i+1) << '\n';
            return 0;
        }
    }

    return 0;
}
	

