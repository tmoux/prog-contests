// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class GraphReconstruction {
public:
  vector<string> findSolution(int N, double C, int K, vector<string> paths)
  {           
    vector<string> out;

    for (int i=0; i<N; i++)
    {
      string row;
      for (int k=0; k<N; k++) row+="0";
      out.push_back(row);
    }

    return out;
  }
};

int main() {
  GraphReconstruction prog;
  int N;
  double C;
  int K;
  int NumPaths;
  vector<string> paths;
  string path;
  cin >> N;
  cin >> C;
  cin >> K;
  cin >> NumPaths;
  for (int i=0; i<NumPaths; i++)
  {
    cin >> path;
    paths.push_back(path);
  }
  
  vector<string> ret = prog.findSolution(N,C,K,paths);
  cout << ret.size() << endl;
  for (int i = 0; i < (int)ret.size(); ++i)
      cout << ret[i] << endl;
  cout.flush();
}
