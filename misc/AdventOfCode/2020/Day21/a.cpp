#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  vector<set<string>> words, allergens;
  set<string> allwords, allallergens;
  while (getline(cin,s)) {
    stringstream ss(s);
    set<string> w, al;
    string a;
    while (true) {
      ss >> a;
      if (a == "contains") break;
      w.insert(a);
      allwords.insert(a);
    }
    while (ss >> a) {
      al.insert(a);
      allallergens.insert(a);
    }
    words.push_back(w);
    allergens.push_back(al);
  }
  int n = words.size();

  multiset<string> badwords;
  for (auto s: allwords) {
    bool poss = false;
    for (int i = 0; i < n; i++) {
      for (auto al: allergens[i]) {
        bool flag = true;
        for (int j = 0; j < n; j++) {
          if (allergens[j].count(al) && !words[j].count(s)) {
            flag = false;
            break;
          }
        }
        poss |= flag;
        cout << s << ' ' << al << ": " << flag << endl;
      }
    }

    if (!poss) {
      badwords.insert(s);
    }
  }
  for (auto s: badwords) {
    cout << s << ' ';
  }
  cout << '\n';
  /*
  int ans = 0;
  for (auto s: badwords) {
    for (int i = 0; i < n; i++) {
      if (words[i].count(s)) {
        ans++;
      }
    }
  }
  cout << "sz " << ans << '\n';
  */
  for (auto s: badwords) {
    for (int i = 0; i < n; i++) {
      if (words[i].count(s)) {
        words[i].erase(s);
      }
    }
  }
  map<string,string> mp;
  while (!allallergens.empty()) {
    string found = "";
    string word = "";
    for (auto al: allallergens) {
      bool empty = true;
      set<string> poss;
      for (int i = 0; i < n; i++) {
        if (allergens[i].count(al)) {
          if (empty) {
            poss = words[i];
            empty = false;
          }
          else {
            vector<string> toerase;
            for (auto s: poss) {
              if (!words[i].count(s)) {
                toerase.push_back(s);
              }
            }
            for (auto s: toerase) {
              poss.erase(s);
            }
          }
        }
      }
      if (poss.size() == 1) {
        found = al;
        word = *poss.begin();
        break;
      }
    }
    cout << "found " << found << ' ' << word << endl;
    mp[found] = word;
    for (int i = 0; i < n; i++) {
      if (words[i].count(word)) words[i].erase(word);
    }
    allallergens.erase(found);
  }
  for (auto p: mp) {
    cout << p.second << ",";
  }
  cout << '\n';
  return 0;
  for (int i = 0; i < n; i++) {
    cout << i << ": ";
    for (auto s: words[i]) {
      cout << s << ' ';
    }
    cout << '\n';
    for (auto s: allergens[i]) {
      cout << s << ' ';
    }
    cout << '\n';
  }

}

