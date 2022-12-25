#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}

const int maxn = 2e5+5;
int N, M;

int clique[maxn];
set<int> cliqueMembers[maxn];
multiset<int> adj[maxn]; // crossEdges

ll total = 0;
int merge(int i, int j) {
  if (i == j) {
    // same clique, do nothing
    return i;
  }

  cout << "Merging " << i << ' ' << j << endl;
  clique[j] = i;

  if (cliqueMembers[i].size() < cliqueMembers[j].size()) {
    swap(i, j);
  }

  ll add = 1LL * cliqueMembers[i].size() * cliqueMembers[j].size();

  for (int mem: cliqueMembers[j]) {
    cliqueMembers[i].insert(mem);
    // cliques[mem].insert(i);
    // cliques[mem].erase(j);
  }

  cout << i << ": " << cliqueMembers[i] << endl;
  cout << "adj " << adj[i] << endl;
  DEBUG(add);

  for (int k: adj[j]) {
    if (k == i) {
      add--;
      // erase from adj[i]
      cout << "finding edge, i = " << i << ", j = " << j << endl;
      auto it = adj[i].find(j);
      assert(it != adj[i].end());
      adj[i].erase(it);
    }
    else {
      adj[i].insert(k);

      // replace cross edge k->j with k->i
      cout << "finding edge, k = " << k << ", j = " << j << endl;
      auto it = adj[k].find(j);
      assert(it != adj[k].end());
      adj[k].erase(it);
      adj[k].insert(i);
    }
  }

  total += add;

  return i;
}

void debug() {
  for (int i = 1; i <= N; i++) {
    cout << "Clique " << i << endl;
    cout << cliqueMembers[i] << endl;
    cout << "Adj " << adj[i] << endl;
    cout << "-----\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    clique[i] = i;
    cliqueMembers[i].insert(i);
  }
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    adj[a].insert(b);
    adj[b].insert(a);
  }

  for (int i = 1; i <= N; i++) {
    int cur_clique = clique[i];
    cout << "DELETING " << i << ": " << cur_clique << endl;
    vector<int> cs;
    for (int c: adj[cur_clique]) cs.push_back(c);
    for (int c: cs) {
      // merge the two cliques
      cur_clique = merge(cur_clique, c);
    }
    cliqueMembers[cur_clique].erase(i);
    debug();
    DEBUG(total);
  }


  cout << total << '\n';
}
