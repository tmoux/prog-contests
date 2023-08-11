#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Point
{
    int x, y;

    inline int dist() const {
        return abs(x) + abs(y);
    }

    bool operator<(const Point& rhs) const {
        return dist() < rhs.dist();
    }
};

int idx = 0;

struct Move {
    int t, a;
    char b;

    void print() {
        if (t == 1) {
            printf("%d %d %c\n",t,a,b);
        }
        else {
            printf("%d\n",t);
        }
    }
} ans[1000000];

void getMove(const Point& p, Move ret[]) {
    if (p.x > 0) {
        ret[idx++] = {1,p.x,'R'};
    }
    else if (p.x < 0) {
        ret[idx++] = {1,abs(p.x),'L'};
    }

    if (p.y > 0) {
        ret[idx++] = {1,p.y,'U'};
    }
    else if (p.y < 0) {
        ret[idx++] = {1,abs(p.y),'D'};
    }
}

void getReverse(const Point& p, Move ret[]) {
    if (p.x > 0) {
        ret[idx++] = {1,p.x,'L'};
    }
    else if (p.x < 0) {
        ret[idx++] = {1,abs(p.x),'R'};
    }

    if (p.y > 0) {
        ret[idx++] = {1,p.y,'D'};
    }
    else if (p.y < 0) {
        ret[idx++] = {1,abs(p.y),'U'};
    }
}



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<Point> A(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d\n",&A[i].x,&A[i].y);
    }
    sort(A.begin(),A.end());
    for (Point& p: A) {
        getMove(p,ans);
        ans[idx++] = {2,0,0};
        getReverse(p,ans);
        ans[idx++] = {3,0,0};
    }

    //output
    printf("%d\n",idx);
    for (int i = 0; i < idx; i++) {
        ans[i].print();
    }


    return 0;
}
	

