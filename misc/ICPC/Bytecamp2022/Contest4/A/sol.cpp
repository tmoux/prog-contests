#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long double ld;

const int maxn = 310000;
const ld inf = 1234;
const ld eps = 1e-12;
const ld pi = acos(-1.0);

struct point{
    ld x,y;
};

struct invl{
    int l,r;
    int id;
};

int magic;

invl q[maxn];
point p[maxn];
ld ang[maxn];
bool ans[maxn];
int origin_count;

bool comp(const invl & a,const invl & b){
    if (a.l / magic != b.l / magic) return a.l < b.l;
    return a.r < b.r;
}

multiset<ld> angles;

void ins(int i){
    if (fabs(p[i].x) < eps && fabs(p[i].y) < eps){
        origin_count++;
    }
    angles.insert(ang[i]);
}

void del(int i){
    if (fabs(p[i].x) < eps && fabs(p[i].y) < eps){
        origin_count--;
    }
    angles.erase(angles.find(ang[i]));
}

int main(){
    int n,xp,yp;
    cin >> n >> xp >> yp;
    cout << fixed << setprecision(10);
    for (int i = 1;i <= n;i++){
        cin >> p[i].x >> p[i].y;
        p[i].x -= xp;
        p[i].y -= yp;
        ang[i] = atan2l(p[i].y,p[i].x);
    }
    magic = sqrt(n + 0.05);
    int t;
    cin >> t;
    for (int i = 1;i <= t;i++){
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q+1,q+t+1,comp);
    int l = 1,r = 0;
    multiset<ld> angels;


    for (int i = 1;i <= t;i++){
      while (l > q[i].l){
          ins(--l);
      }
      while (r < q[i].r){
          ins(++r);
      }
      while (l < q[i].l){
          del(l++);
      }
      while (r > q[i].r){
          del(r--);
      }
      if (origin_count){
          ans[q[i].id] = true;
          continue;
      }
      //Two points?
      ld start = *angles.begin();
      if (start > eps){
          ans[q[i].id] = false;
          continue;
      }
      //Find the third
      ld cur = start;
      bool tf = false;
      while (true){
          //Find next one, less than or equal to <= pi
          if (cur < 0){
              auto iter = angles.upper_bound(cur + pi + eps);
              if (iter == angles.begin()){
                  tf = false;
                  break;
              }
              iter--;
              if (fabs(cur - (*iter)) < eps){
                  tf = false;
                  break;
              }
              cur = *iter;
          }
          else{
              //Maybe find the next in negative?
              if (start + 2 * pi - cur <= pi + eps){
                  tf = true;
                  break;
              }
              else{
                  auto iter = angles.end();
                  iter--;
                  if (fabs(cur - (*iter)) < eps){
                      tf = false;
                      break;
                  }
                  cur = (*iter);
              }
          }
      }
      ans[q[i].id] = tf;
    }
      for (int i = 1;i <= t;i++){
          if (ans[i]) cout << "Yes\n";
          else cout << "No\n";
      }
}
