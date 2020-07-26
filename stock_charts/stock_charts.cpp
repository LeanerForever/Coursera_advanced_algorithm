#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector;
using std::cin;
using std::cout;

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  vector<vector<bool>> converter(const vector<vector<int>>& stock_data,int n,int k){
    vector<vector<bool>> adj_matrix(n,vector<bool>(n,true));
    for(int i=0;i<n;++i){
      for(int j=0;j<n;++j){
        for(int t=0;t<k;++t){
          if(stock_data[i][t]>=stock_data[j][t]){
            adj_matrix[i][j] = false;
            break;
          }
        }
      }
    }
    return adj_matrix;
  }

  bool dfs(const vector<vector<bool>>& adj_matrix,vector<int>& matching, vector<bool>& seen,int u,int n){
    for(int v=0;v<n;++v){
      if(adj_matrix[u][v] && !seen[v]){
        seen[v] = true;
        if(matching[v]<0 || dfs(adj_matrix,matching,seen,matching[v],n)){
          matching[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.

    int n = stock_data.size();
    int k = stock_data[0].size();
    // Vector of charts; each chart is a vector of indices of individual stocks.
    vector<vector<bool>> adj_matrix = converter(stock_data,n,k);
    vector<int> matching(n,-1);
    int ans=0;
    for(int u=0;u<n;++u){
      vector<bool> seen(n,false);
      if(dfs(adj_matrix,matching,seen,u,n))
        ans++;
    }
    
    return n-ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
