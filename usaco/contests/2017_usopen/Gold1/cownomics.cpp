/*
ID: silxikys
PROG: cownomics
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <cstdlib>
using namespace std;

int N, M;
string spotty[500], plain[500];
unsigned long long hashes1[500], hashes2[500], R[500];

int main(void)
{
  ifstream fin("cownomics.in");
  ofstream fout("cownomics.out");
  fin >> N >> M;
  for (int i=0; i<N; i++) fin >> spotty[i];
  for (int i=0; i<N; i++) fin >> plain[i];
  for (int i=0; i<M; i++) R[i] = rand() % 1000000000;
  int i=0, j=0;
  int best = M, dups = N;
  while (j < M) {
    // There is (very small) but some false positive risk in 
    // using hashing here, so we could have explicitly verified
    // matches if desired just to be 100% certain of correctness
    if (dups == 0) best = min(best, j-i);
    if (dups>0) {
      set<int> H;
      dups = 0;
      for (int k=0; k<N; k++) H.insert(hashes1[k] += R[j] * spotty[k][j]);
      for (int k=0; k<N; k++) if (H.count(hashes2[k] += R[j] * plain[k][j])>0) dups++;
      j++;
    } else {
      dups = 0;
      set<int> H;
      for (int k=0; k<N; k++) H.insert(hashes1[k] -= R[i] * spotty[k][i]);
      for (int k=0; k<N; k++) if (H.count(hashes2[k] -= R[i] * plain[k][i])>0) dups++;
      i++;
    }
  }
  cout << best << '\n';
  //fout << best << '\n';
}