#include "combo.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string guess_sequence(int N) {
  string s = "";
  //get first character
  int p = press("AB");
  string s1 = (p > 0 ? "AB" : "XY");
  p = press(s1.substr(0,1));
  s += (p > 0 ? s1[0] : s1[1]);
  vector<char> v = {'A','B','X','Y'};
  auto it = find(v.begin(),v.end(),s[0]); v.erase(it);
  //get other characters
  char c1 = v[0], c2 = v[1], c3 = v[2];
  for (int i = 1; i < N - 1; i++) {
  	string tr = s+c1+s+c2+c1+s+c2+c2+s+c2+c3;
  	p = press(tr);
  	if (p == i) {
  		s += c3;
  	}
  	else if (p == i+1) {
  		s += c1;
  	}
  	else if (p == i+2) {
  		s += c2;
  	}
  }
  //get last char
  if (N != 1) {
    p = press(s+c1+s+c2);
  	if (p == N) {
  	  p = press(s+c1);
  	  s += (p == N ? c1 : c2);
  	}
  	else {
  	  s += c3;
  	}
  }
  return s;
}
