#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector;
using std::cin;
using std::cout;

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  bool dfs(const vector<vector<bool>>& adj_matrix, vector<int>& matching, vector<bool>& seen,int u, int n,int m){
    for(int v=0;v<m;++v){
      if(adj_matrix[u][v]==1 && !seen[v]){
        seen[v] = true;
        if(matching[v]<0 || dfs(adj_matrix,matching,seen,matching[v],n,m)){
          matching[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching(num_right, -1);
    vector<int> ret(num_left,-1);

    for(int u=0;u<num_left;++u){
      vector<bool> seen(num_right, false);
      dfs(adj_matrix,matching,seen,u,num_left,num_right);
    }

    for(int v=0;v<num_right;++v){
      if(matching[v]!=-1)
        ret[matching[v]] = v;
    }

    return ret;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
