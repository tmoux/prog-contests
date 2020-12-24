#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, S;

struct Statement {
  bool isIf;
  int y;
  ll v;
  Statement *ifblock;
  Statement *next;
};

Statement* makeSet(int y, ll v, Statement* next) {
  Statement* ret = new Statement;
  ret->isIf = false;
  ret->y = y;
  ret->v = v;
  ret->ifblock = NULL;
  ret->next = next;
  return ret;
}

Statement* makeIf(int y, Statement* ifblock, Statement* next) {
  Statement* ret = new Statement;
  ret->isIf = true;
  ret->y = y;
  ret->v = 0;
  ret->ifblock = ifblock;
  ret->next = next;
  return ret;
}

string input[maxn];

int idx = 0;
Statement* read() {
  //cout << idx << ' ' << input[idx] << endl;
  stringstream ss(input[idx]);
  string word; ss >> word;
  if (word == "set") {
    int y; ll v; ss >> y >> v;
    idx++;
    return makeSet(y,v,read());
  }
  else if (word == "if") {
    int y; ss >> y;
    idx++;
    Statement* ifblock = read();
    idx++;
    Statement* next = read();
    return makeIf(y,ifblock,next);
  }
  else if (word == "end") return NULL;
  else {
    //while (true) {}
  }
  assert(false); return NULL;
}

void print(Statement* s) {
  if (!s) return;
  if (!s->isIf) {
    cout << "set " << s->y << ' ' << s->v << endl;
  }
  else {
    cout << "if " << s->y << endl;
    cout << "{\n";
    print(s->ifblock);
    cout << "end" << endl;
    cout << "}\n";
  }
  print(s->next);
}

const ll INF = 1e18;
struct Bag {
  ll aux = 0;  
  multiset<ll> s;
  map<int,ll> mp;
  Bag(int x, ll y) {
    aux = 0;
    mp[x] = y;
    s.insert(y);
  }
  void insert(int x, ll y) {
    if (mp.count(x)) {
      auto it = s.find(mp[x]);
      assert(it != s.end());
      //if (it == s.end()) while (1) {};
      s.erase(it);
    }
    mp[x] = y-aux;
    s.insert(y-aux);
  }
  void insertMin(int x, ll y) {
    if (mp.count(x) && mp[x]+aux <= y) return;
    else insert(x,y);
  }
  ll getmin() {
    assert(!s.empty());
    return *s.begin()+aux;
  }
  ll lookup(int x) {
    if (!mp.count(x)) return INF;
    else return mp[x] + aux;
  }
  void increment(ll x) {
    aux += x;
  }
  vector<pair<int,ll>> getvec() {
    vector<pair<int,ll>> v;
    for (auto p: mp) {
      v.push_back({p.first,p.second+aux});
    }
    return v;
  }
};

void merge(Bag& a, Bag& b, int y) {
  bool swp = false;
  if (a.mp.size() < b.mp.size()) {
    swap(a,b);
    swp = true;
  }
  for (auto p: b.getvec()) {
    if (p.first == y) {
      if (!swp) a.insert(p.first,p.second);
    }
    else 
      a.insertMin(p.first,p.second);
  }
}

void solve(Statement* st, Bag* b) {
  while (st) {
    if (!(st->isIf)) { //set
      ll mn = b->getmin();
      b->increment(st->v);   
      if (st->y != S) {
        b->insert(st->y,mn);
      }
    }
    else { //if
      ll cost = b->lookup(st->y);
      if (cost < INF) {
        Bag ifBag = Bag(st->y,cost);
        solve(st->ifblock,&ifBag);
        merge(*b,ifBag,st->y);
      }
    }
    st = st->next;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> S;
  string nl; getline(cin,nl);
  for (int i = 0; i < n; i++) {
    getline(cin,input[i]);
  }
  input[n] = "end";
  Statement *start = read();
  Bag b = Bag(0,0);
  solve(start,&b);
  cout << b.getmin() << '\n';
}
